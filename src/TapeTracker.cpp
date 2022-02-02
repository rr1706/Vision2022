#include "frc1706/TapeTracker.hpp"
#include "frc1706/RoboRIOClient.hpp"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"

#include "spdlog/spdlog.h"

#include <exception>
#include <thread>
#include <mutex>

namespace frc1706 {

    TapeTracker::TapeTracker(const cv::VideoCapture &cap, RoboRIOClient &client) :
        _capture_device(cap), _net_client(&client) {}
 
    TapeTracker::~TapeTracker() {
        this->_enabled = false;
        this->_capture_device.release();
    }
    
//----------------------------------------------------------------------------------------------

    cv::Mat TapeTracker::process() {
        if(this->getCurrentFrame().empty()) {
            throw std::runtime_error("Current frame is empty, unable to process");
        }
        
        cv::Mat threshed, gray;

        // Used hsv color space as it's better for color tracking 
        cv::cvtColor(this->getCurrentFrame(), gray, cv::COLOR_BGR2GRAY);

        // Thresh the image with the range provided 
        //cv::inRange(gray, range.first, range.second, threshed);
        
        // "Open" the threshed image(erode followed by dilate)
        cv::morphologyEx(threshed, threshed, cv::MORPH_OPEN, this->_kernel);
        cv::morphologyEx(threshed, threshed, cv::MORPH_OPEN, this->_kernel); // Is there a point to doing this twice

        return threshed;
    }

//----------------------------------------------------------------------------------------------

    std::map<std::string, double> TapeTracker::track(const cv::Mat &threshed) {
        std::vector<std::vector<cv::Point>> cnts;

        // Find all external contours
        cv::findContours(threshed, cnts, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        if(!cnts.empty()) {
            //https://github.com/rr1706/vision2013/blob/master/source/extrinsic.cpp
            //cv::solvePnPRansac(obj_pnts, img_pnts, cam_mtx, dist_coeff, r_vec, t_vec);

            double distance;
            double angle;

            return {
                {"color", 3},
                {"distance", distance},
                {"angle", angle}
            };
        }

        return {};
    }

//----------------------------------------------------------------------------------------------

    void TapeTracker::run() {
        /**
         * The value of _task isn't used anywhere but it is required to store
         * the output of std::async to keep it from destroying itself
         */
        this->_task = std::async(std::launch::async, TapeTracker::_run, this);
    }

//----------------------------------------------------------------------------------------------

    void TapeTracker::show(const std::string &win_name, bool show_tracking) {
        // If frame not empty display it
        if(!this->getCurrentFrame().empty()) {
            cv::imshow(win_name, this->getCurrentFrame());
        }
    }

//----------------------------------------------------------------------------------------------
    
    cv::Mat TapeTracker::getCurrentFrame(bool show_tracking) {
        // Lock resources on current thread
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        if(show_tracking && !this->_current_frame_tracked.empty()) {
            return this->_current_frame_tracked;
        }
        return this->_current_frame;
    }

//----------------------------------------------------------------------------------------------
    
    void TapeTracker::_setCurrentFrame(const cv::Mat &new_frame, bool tracked_frame) {
        // Lock resources on current thread
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        if(tracked_frame) {
            this->_current_frame_tracked = new_frame;
            return;
        }
        this->_current_frame = new_frame;
    }

//----------------------------------------------------------------------------------------------

    void TapeTracker::_broadcast(std::map<std::string, double> pose) {
        try {
            this->_net_client->sendMessage(this->_net_client->createMessage(pose));
        } catch(std::exception err) {
            spdlog::warn(err.what());
        }
    }

//----------------------------------------------------------------------------------------------

    void TapeTracker::_run(TapeTracker* self) {
        while(true) {
            if(self->_enabled) { 
                cv::Mat next_frame;
                if(self->_capture_device.read(next_frame)) {
                    spdlog::info("Reading next frame from tape tracker");
                    self->_setCurrentFrame(next_frame);
                } else {
                    spdlog::critical("Unable to read next frame");
                }
            } else { 
                break; 
            }

            cv::Mat processed(self->process());

#ifdef DISPLAY 
            cv::imshow("threshed tape", processed);
#endif // DISPLAY 

            std::map<std::string, double> final(self->track(processed));

            spdlog::debug("Blue angle: {}", final["angle"]);
            spdlog::debug("Blue distance: {}", final["distance"]);

            self->_broadcast(final);
        }
    }
};

#include "frc1706/BallTracker.hpp"
#include "frc1706/RoboRIOClient.hpp"

#include "opencv2/calib3d.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"

#include "spdlog/spdlog.h"

#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>
#include <utility>
#include <vector>

namespace frc1706 {
    // https://docs.opencv.org/3.4/d9/d61/tutorial_py_morphological_ops.html
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));

    // Safely end _task by changing this once the object goes out of scope 
    bool enabled = true;

    BallTracker::BallTracker(const cv::VideoCapture &cap, RoboRIOClient &client) :
        _capture_device(cap), _net_client(&client) {}
 
    BallTracker::~BallTracker() {
        enabled = false;
        this->_capture_device.release();
    }
    
//----------------------------------------------------------------------------------------------

    cv::Mat BallTracker::process(const std::pair<cv::Scalar, cv::Scalar> &range) {
        if(this->getCurrentFrame().empty()) {
            throw std::runtime_error("Current frame is empty, unable to process");
        }
        
        cv::Mat threshed, hsv;
        
        // gaussian blur is broken for some reason
        //cv::GaussianBlur(this->getCurrentFrame(), blurred, cv::Size(10, 10), 0);

        // Used hsv color space as it's better for color tracking 
        cv::cvtColor(this->getCurrentFrame(), hsv, cv::COLOR_BGR2HSV);

        // Thresh the image with the range provided 
        cv::inRange(hsv, range.first, range.second, threshed);
        
        // "Open" the threshed image(erode followed by dilate)
        cv::morphologyEx(threshed, threshed, cv::MORPH_OPEN, kernel);
        cv::morphologyEx(threshed, threshed, cv::MORPH_OPEN, kernel); // Is there a point to doing this twice

        return threshed;
    }

//----------------------------------------------------------------------------------------------

    std::map<std::string, double> BallTracker::track(const cv::Mat &threshed, const Color &color) {
        std::vector<std::vector<cv::Point>> cnts;
        cv::Point2f ball_center;
        float radius;

        // Find all external contours
        cv::findContours(threshed, cnts, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        if(!cnts.empty()) {
            // Find the largest contour
            std::vector<cv::Point2i> largest_cnt;
            for(std::vector<cv::Point> cnt : cnts) {
                if(cnt.size() > largest_cnt.size()) {
                    largest_cnt = cnt;
                }
            }

            // Focus the largets contour
            cv::minEnclosingCircle(largest_cnt, ball_center, radius);

            //cv::solvePnPRansac(obj_pnts, img_pnts, cam_mtx, dist_coeff, r_vec, t_vec);

            double distance;
            double angle;

            return {
                {"color", color},
                {"distance", distance},
                {"angle", angle}
            };
        }

        return {};
    }

//----------------------------------------------------------------------------------------------

    void BallTracker::run() {
        /**
         * The value of _task isn't used anywhere but it is required to store
         * the output of std::async to keep it from destroying itself
         */
        this->_task = std::async(std::launch::async, BallTracker::_run, this);
    }

//----------------------------------------------------------------------------------------------

    void BallTracker::show(const std::string &win_name, bool show_tracking) {
        // If frame not empty display it
        if(!this->getCurrentFrame().empty()) {
            cv::Mat hsv;
            cv::cvtColor(this->getCurrentFrame(show_tracking), hsv, cv::COLOR_BGR2HSV);
            cv::imshow(win_name, hsv);
        }
    }

//----------------------------------------------------------------------------------------------
    
    cv::Mat BallTracker::getCurrentFrame(bool show_tracking) {
        // Lock resources on current thread
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        if(show_tracking && !this->_current_frame_tracked.empty()) {
            return this->_current_frame_tracked;
        }
        return this->_current_frame;
    }

//----------------------------------------------------------------------------------------------
    
    void BallTracker::_setCurrentFrame(const cv::Mat &new_frame, bool tracked_frame) {
        // Lock resources on current thread
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        if(tracked_frame) {
            this->_current_frame_tracked = new_frame;
            return;
        }
        this->_current_frame = new_frame;
    }

//----------------------------------------------------------------------------------------------

    void BallTracker::_broadcast(std::map<std::string, double> pose) {
        try {
            this->_net_client->sendMessage(this->_net_client->createMessage(pose));
        } catch(std::exception err) {
            spdlog::warn(err.what());
        }
    }

//----------------------------------------------------------------------------------------------

    void BallTracker::_run(BallTracker* self) {
        // OpenCV defaults to BGR not RGB
        // min/max color values for each ball color
        std::pair<cv::Scalar, cv::Scalar> blue = {
            cv::Scalar(92, 139, 76),  
            cv::Scalar(115, 210, 175) 
        };
        std::pair<cv::Scalar, cv::Scalar> red = {
            cv::Scalar(165, 92, 52), 
            cv::Scalar(175, 218, 213)
        };
        while(true) {
            if(enabled) { 
                cv::Mat next_frame;
                if(self->_capture_device.read(next_frame)) {
                    spdlog::info("Reading next frame from ball tracker");
                    self->_setCurrentFrame(next_frame);
                } else {
                    spdlog::critical("Unable to read next frame");
                }
            } else { 
                break; 
            }

            // TODO: Make these run in parallel
            // TODO: maybe use a lambda
            cv::Mat processed_blue(self->process(blue));
            cv::Mat processed_red(self->process(red));

#ifdef DISPLAY 
            cv::imshow("threshed blue", processed_blue);
            cv::imshow("threshed red", processed_blue);
#endif // DISPLAY 

            std::map<std::string, double> final_blue(self->track(processed_blue, Color::blue));
            std::map<std::string, double> final_red(self->track(processed_red, Color::red));

            spdlog::debug("Blue angle: {}", final_blue["angle"]);
            spdlog::debug("Blue distance: {}", final_blue["distance"]);
            spdlog::debug("Red angle: {}", final_red["angle"]);
            spdlog::debug("Red distance: {}", final_red["distance"]);

            self->_broadcast(final_blue);
            self->_broadcast(final_red);
        }
    }
};

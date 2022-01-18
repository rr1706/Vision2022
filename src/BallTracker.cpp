#include "frc1706/BallTracker.hpp"

#include "opencv2/core.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdexcept>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>

namespace frc1706 {
    BallTracker::BallTracker(const cv::VideoCapture &cap, bool broadcast) :
        _capture_device(cap), _enable_broadcast(broadcast) {}
    
    BallTracker::~BallTracker() {
        this->enabled = false;
        this->_capture_device.release();
    }
    
    cv::Mat BallTracker::process() {
        if(this->getCurrentFrame().empty()) {
            throw std::runtime_error("Current frame is empty, unable to process");
        }

        cv::Mat threshed, hsv, blurred;

        cv::GaussianBlur(this->getCurrentFrame(), blurred, cv::Size(10, 10), 0);
        // hsv is in question because we need to give the pose of the closest(largest) red and blue ball
        //cv::cvtColor(blurred, hsv, cv::COLOR_BGR2HSV);
        blurred.copyTo(threshed);

        return threshed;
    }

    void BallTracker::run() {
        /**
         * The value of _task isn't used anywhere but it is required to store
         * the output of std::async to keep it from destroying itself
         */
        this->_task = std::async(std::launch::async, BallTracker::_run, this);
    }

    void BallTracker::show(const std::string &win_name, bool show_tracking) {
        // If frame not empty display it
        if(!this->getCurrentFrame().empty())
            cv::imshow(win_name, this->getCurrentFrame(show_tracking));
    
    }
    
    cv::Mat BallTracker::getCurrentFrame(bool show_tracking) {
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        if(show_tracking && !this->_current_frame_tracked.empty()) {
            return this->_current_frame_tracked;
        }
        return this->_current_frame;
    }
    
    void BallTracker::_setCurrentFrame(const cv::Mat &new_frame, bool tracked_frame) {
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        if(tracked_frame) {
            this->_current_frame_tracked = new_frame;
            return;
        }
        this->_current_frame = new_frame;
    }

    void BallTracker::_broadcast(const cv::Mat &frame) {
        return;
    }

    void BallTracker::_run(BallTracker* self) {
        while(true) {
            if(self->enabled) { 
                cv::Mat next_frame;
                if(self->_capture_device.read(next_frame)) {
                    std::cout << "Reading next frame for Ball Tracker: " << self << std::endl;
                    self->_setCurrentFrame(next_frame);
                } else {
                    std::cerr << "Unable to read next frame\n"; 
                }
            } else { 
                break; 
            }

            cv::Mat processed = self->process();
 
            if (!processed.empty())
                self->_setCurrentFrame(processed, true);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};
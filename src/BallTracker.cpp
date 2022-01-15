#include "frc1706/BallTracker.hpp"

#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>

namespace frc1706 {
    BallTracker::BallTracker(const cv::VideoCapture &cap, bool broadcast) :
        _capture_device(cap), _enable_broadcast(broadcast) {}
    BallTracker::~BallTracker() {
        this->_capture_device.release();
    }
    
    cv::Mat BallTracker::process() {
        if(this->_current_frame.empty()) {
            throw("Current frame is empty, unable to process");
        }


        return cv::Mat();
    }

    void BallTracker::run() {
        //this->_task =
        std::async(std::launch::async, BallTracker::_run, this);
    }

    cv::Mat BallTracker::getCurrentFrame() {
        return this->_current_frame;
    }
    
    void BallTracker::_broadcast(const cv::Mat &frame) {
        return;
    }

    void BallTracker::_run(BallTracker* self) {
        while(true) {
            { // Forces lock to go out of scope once it's done
                std::lock_guard<std::mutex> lock(self->_current_frame_mutex);
                self->_capture_device >> self->_current_frame;
            }
            //self->process();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
};
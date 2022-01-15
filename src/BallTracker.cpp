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
        void(std::async(std::launch::async, BallTracker::_run, this));
    }

    cv::Mat BallTracker::getCurrentFrame() {
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        return this->_current_frame;
    }
    
    void BallTracker::_setCurrentFrame(const cv::Mat &new_frame) {
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        this->_current_frame = new_frame;
    }

    void BallTracker::_broadcast(const cv::Mat &frame) {
        return;
    }

    void BallTracker::_run(BallTracker* self) {
        while(true) {
            { // Destroy tmp_frame after it's not needed 
                cv::Mat tmp_frame;
                self->_capture_device.read(tmp_frame);
                self->_setCurrentFrame(tmp_frame);
                std::cout << "Ball tracker read new frame\n";
            }
            //self->process();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};
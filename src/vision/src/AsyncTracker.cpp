#include "RobotClient.hpp"
#include "async/AsyncPipeline.hpp"
#include "async/AsyncTracker.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

namespace async {
    AsyncTracker::AsyncTracker(
        const cv::VideoCapture &cam, 
        RobotClient &client,
        const frc::vision::ConnectRequest::Type &type, 
        const frc::vision::ConnectRequest::Location &location
    ): AsyncPipeline(client, type, location), video_device(cam) {}

    AsyncTracker::~AsyncTracker() {
        this->video_device.release();
    }

    cv::Mat AsyncTracker::getCurrentFrame() {
        // Lock resources on current thread
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        return this->_current_frame;
    }

    void AsyncTracker::setCurrentFrame(const cv::Mat &new_frame) {
        // Lock resources on current thread
        std::lock_guard<std::mutex> lock(this->_current_frame_mutex);
        this->_current_frame = new_frame;
    }
};
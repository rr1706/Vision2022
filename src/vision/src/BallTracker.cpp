#include "frc1706/trackers/BallTracker.hpp"
#include "frc1706/async/AsyncTracker.hpp"

#include "spdlog/spdlog.h"

#include "opencv2/imgproc.hpp"

namespace frc1706::trackers {
    // https://docs.opencv.org/3.4/d9/d61/tutorial_py_morphological_ops.html
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    // Safely end _task by changing this once the object goes out of scope 
    bool enabled = true;

    BallTracker::BallTracker(const cv::VideoCapture &cap, RoboRIOClient &client): 
        async::AsyncTracker(cap, client) {}
 
    BallTracker::~BallTracker() {
        enabled = false;
    }
    
//----------------------------------------------------------------------------------------------

    cv::Mat BallTracker::processCurrentFrame() {
        if(this->getCurrentFrame().empty()) {
            throw std::runtime_error("Current frame is empty, unable to process");
        }
        cv::Mat threshed, hsv;
        // Used hsv color space as it's better for color tracking 
        cv::cvtColor(this->getCurrentFrame(), hsv, cv::COLOR_BGR2HSV);
        // Thresh the image with the range provided 
        cv::inRange(hsv, range.first, range.second, threshed);
        // "Open" the threshed image(erode followed by dilate)
        cv::morphologyEx(threshed, threshed, cv::MORPH_OPEN, kernel);
        return threshed;
    }

//----------------------------------------------------------------------------------------------

    std::map<std::string, double> BallTracker::trackCurrentFrame() {
        std::vector<std::vector<cv::Point>> cnts;
        cv::Point2f ball_center;
        float radius;

        cv::findContours(threshed, cnts, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        if(!cnts.empty()) {
            // Find the largest contour
            std::vector<cv::Point2i> largest_cnt;
            for(std::vector<cv::Point> cnt : cnts) {
                if(cnt.size() > largest_cnt.size()) {
                    largest_cnt = cnt;
                } // TODO: Add else to prioritize lower contour if they are equal
            }
            // Track the largets contour
            cv::minEnclosingCircle(largest_cnt, ball_center, radius);
            // Calculate distance and angle
            double distance;
            double angle;
            return {
                {"distance", distance},
                {"angle", angle}
            };
        }
        return {};
    }

//----------------------------------------------------------------------------------------------

    void BallTracker::task() {
        while(!client.reciveShutdown() && this->video_device.isOpened()) {
            cv::Mat next_frame;
            if(this->video_device.read(next_frame)) {
                spdlog::info("Reading next frame from ball tracker");
                this->setCurrentFrame(next_frame);
            } else {
                spdlog::critical("Unable to read next frame");
            }

            std::map<std::string, double> data(this->trackCurrentFrame());

            spdlog::debug("Blue angle: {}", data["angle"]);
            spdlog::debug("Blue distance: {}", data["distance"]);
        }
    }
};

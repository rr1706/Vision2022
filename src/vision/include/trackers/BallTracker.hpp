#pragma once
#include "Robot.pb.h"
#include "RobotClient.hpp"
#include "async/AsyncTracker.hpp"

#include "opencv2/videoio.hpp"
#include <opencv2/core/types.hpp>
#include <utility>

// Constants in mm
#define BALL_DIAMETER_MM 241.3
#define FOCAL_LENGTH_MM 1 // Find this

namespace trackers {
    class BallTracker : public async::AsyncTracker {
        public:
            BallTracker(const cv::VideoCapture &cap, RobotClient &client); 
            virtual ~BallTracker();

            cv::Mat processCurrentFrame() override;
           
            std::map<std::string, double> trackCurrentFrame() override;       
 
        protected:
            void task() override;

            const frc::vision::BallReply buildReply(const std::map<std::string, double> &data);
            void sendReply(const frc::vision::BallReply &resp);

        private:
            // OpenCV defaults to BGR not RGB
            // min/max color values for each ball color        
            const static inline std::pair<cv::Scalar, cv::Scalar> _blue_range = {
                cv::Scalar(92, 139, 76),  
                cv::Scalar(115, 210, 175)
            };
            const static inline std::pair<cv::Scalar, cv::Scalar> _red_range = {
                cv::Scalar(165, 92, 52), 
                cv::Scalar(175, 218, 213)
            };
    };
};

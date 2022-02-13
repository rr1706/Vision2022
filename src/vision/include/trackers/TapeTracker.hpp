#pragma once
#include "RobotClient.hpp"
#include "async/AsyncTracker.hpp"

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"

// Constants in mm
#define FOCAL_LENGTH_MM 1 // Find this

namespace trackers {
    class TapeTracker: public async::AsyncTracker {
        public:
           TapeTracker(const cv::VideoCapture &cap, RobotClient &client); 
            virtual ~TapeTracker();
 
            cv::Mat processCurrentFrame() override;
           
            std::map<std::string, double> trackCurrentFrame() override;

            //const frc::vision::RingReply buildReply(const std::map<std::string, double> &data);
            //void sendReply(const frc::vision::RingReply &resp);
        
        protected:
            void task() override;
   };
};


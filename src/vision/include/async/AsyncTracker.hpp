#pragma once
#include "async/AsyncPipeline.hpp"
#include "RobotClient.hpp"
#include <opencv2/videoio.hpp>
#include "opencv2/core.hpp"
#include <future>

namespace async {
    class AsyncTracker: public AsyncPipeline {
        public:
            AsyncTracker(
                const cv::VideoCapture &cam, 
                RobotClient &client,
                const frc::vision::ConnectRequest::Type &type, 
                const frc::vision::ConnectRequest::Location &location
            );
            virtual ~AsyncTracker();
             
            virtual cv::Mat processCurrentFrame() = 0;
           
            virtual std::map<std::string, double> trackCurrentFrame() = 0;
            
            cv::Mat getCurrentFrame();
        
        protected:
            void setCurrentFrame(const cv::Mat &new_frame);
            
            // The capture device
            cv::VideoCapture video_device;

        private:
            // Current frame
            cv::Mat _current_frame;
            // Mutex for above
            std::mutex _current_frame_mutex;
    };
};

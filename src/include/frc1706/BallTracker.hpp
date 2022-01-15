#include "opencv2/core/mat.hpp"
#include "opencv2/videoio.hpp"

#include <Poco/Types.h>

namespace frc1706 {
    class BallTracker {
        public:
            BallTracker(const cv::VideoCapture &cap, bool broadcast = true);
            virtual ~BallTracker();

            /**
             * @brief process camera feed and return the cv::Mat 
             * @return a cv::Mat that is the final processed image/cv::Mat 
             */
            cv::Mat process();
            
            /**
             * @brief runs process() then uses the resulting cv::Mat to pull data,
             *        broadcast image aswell if it is enabled.
             * @return an int that is the return code of that frame
             */
            int run();
            
            /**
             * TODO
             */
            cv::Mat getCurrentFrame();

        private:
            /**
             * TODO 
             */
            void _broadcast(const cv::Mat &frame);

            bool _enable_broadcast;
            cv::Mat _current_frame;
            cv::VideoCapture _capture_device;
    };
};
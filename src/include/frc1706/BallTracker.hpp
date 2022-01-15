#include "opencv2/core/mat.hpp"
#include "opencv2/videoio.hpp"

#include <future>

namespace frc1706 {
    class BallTracker {
        public:
            BallTracker(const cv::VideoCapture &cap, bool broadcast = true);
            virtual ~BallTracker();

            /**
             * @brief process the current frame then return it as a cv::Mat 
             * @return a cv::Mat that is the final processed image/cv::Mat 
             */
            cv::Mat process();
            
            /**
             * @brief runs process() then uses the resulting cv::Mat to pull data,
             *        broadcast image aswell if it is enabled.
             */
            void run();
            
            /**
             * @brief getter method for _current_frame, locks with std::mutex
             * @return The current cv::Mat that is being processed
             */
            cv::Mat getCurrentFrame();
        
        private:
            /**
             * TODO 
             */
            void _broadcast(const cv::Mat &frame);
            
            /**
             * @brief internal static method for run(), allows it to be run async
             */
            static void _run(BallTracker* self);
        
            /**
             * @brief setter method for _current_frame, locks it with an std::mutex
             */
            void _setCurrentFrame(const cv::Mat &new_frame);
        
            // Initalize async task in class so it won't go out of scope later
            //std::future<void> _task;
            // Current process frame
            cv::Mat _current_frame;
            // mutex for above
            std::mutex _current_frame_mutex;
            // Capture device 
            cv::VideoCapture _capture_device;
            // Should data be sent over the network
            bool _enable_broadcast;
    };
};
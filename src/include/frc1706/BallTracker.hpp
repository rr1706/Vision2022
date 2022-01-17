#include "opencv2/core/mat.hpp"
#include "opencv2/videoio.hpp"

#include <future>

namespace frc1706 {
    /**
     * @brief takes a cv::VideoCapture then runs a ball tracking algo on it async 
     */
    class BallTracker {
        public:
            /**
             * @param cap the cv::VideoCapture device to use
             * @param broadcast should this tracker broadcast it's data/video stream
             */
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
            cv::Mat getCurrentFrame(bool show_tracking = false);
            
            // safely _task by changing this once the object goes out of scope 
            bool enabled = true;

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
            void _setCurrentFrame(const cv::Mat &new_frame, bool tracked_frame = false);

            // Initalize async task in class so it won't go out of scope later
            std::future<void> _task;
            // Current frame
            cv::Mat _current_frame;
            // Current frame but with tracking shown
            cv::Mat _current_frame_tracked;
            // mutex for above
            std::mutex _current_frame_mutex;
            // Capture device 
            cv::VideoCapture _capture_device;
            // Should data be sent over the network
            bool _enable_broadcast;
    };
};
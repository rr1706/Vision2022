#pragma once
#include "frc1706/RoboRIOClient.hpp"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"

#include <map>
#include <future>

// Constants in mm
#define BALL_DIAMETER 241.3
#define FOCAL_LENGTH 1 // Find this

namespace frc1706 {
    /**
     * @brief  
     */
    class TapeTracker {
        public:
            /**
             * @param cap the cv::VideoCapture device to use
             * @param client UDP client connection to use
             */
            TapeTracker(const cv::VideoCapture &cap, RoboRIOClient &client); 
            virtual ~TapeTracker();
            
            /**
             * @brief process the current frame then return it as a cv::Mat 
             * @return a cv::Mat that is the final processed image/cv::Mat 
             */
            cv::Mat process();

            /**
             * @brief
             * @param 
             * @return 
             */
            std::map<std::string, double> track(const cv::Mat &threshed);

            /**
             * @brief Launches TapeTracker::_run() as an async task
             */
            void run();
            
            /**
             * @brief Getter method for _current_frame, locks with std::mutex
             * @param show_tracking Pull the current frame with tracking ui
             * @return The current cv::Mat that is being processed
             */
            cv::Mat getCurrentFrame(bool show_tracking = false);

            /**
             * @brief 
             * @param win_name
             * @param show_tracking
             */
            void show(const std::string &win_name, bool show_tracking = false);

        
        private:
            /**
             * @brief
             */
            void _broadcast(std::map<std::string, double> pose);
            
            /**
             * @brief Internal static method for run(), allows it to be run async
             * @param self
             */
            static void _run(TapeTracker* self);
        
            /**
             * @brief Setter method for _current_frame, locks it with an std::mutex
             * @param new_frame
             * @param tracked_frame
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
            // Networking client to use
            std::shared_ptr<RoboRIOClient> _net_client;
            // https://docs.opencv.org/3.4/d9/d61/tutorial_py_morphological_ops.html
            const inline static cv::Mat _kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
            // Safely end _task by changing this once the object goes out of scope 
            inline static bool _enabled = true;
    };
};


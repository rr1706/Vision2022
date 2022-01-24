#pragma once
#include "frc1706/RoboRIOClient.hpp"

#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/videoio.hpp"

#include <future>
#include <map>
#include <utility>

namespace frc1706 {
    /**
     * @brief takes a cv::VideoCapture then runs a ball tracking algo on it async 
     */
    class BallTracker {
        public:
            /**
             * @param cap the cv::VideoCapture device to use
             * @param client UDP client to connect to the RoboRIO with
             */
            BallTracker(const cv::VideoCapture &cap, RoboRIOClient &client);
            virtual ~BallTracker();

            /**
             * @brief process the current frame then return it as a cv::Mat 
             * @return a cv::Mat that is the final processed image/cv::Mat 
             */
            cv::Mat process(const std::pair<cv::Scalar, cv::Scalar> &range);

            /**
             * TODO
             */
            cv::Mat track(const cv::Mat &threshed, const cv::Mat &clean, const cv::Scalar &color = cv::Scalar(255, 0, 0));

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

            /**
             * TODO
             */
            void show(const std::string &win_name, bool show_tracking = false);

            // safely _task by changing this once the object goes out of scope 
            bool enabled = true;
            
            /**
             * message to be serialized by msgpack then sent to RoboRIO
             */ 
            static struct Message {
                // Current frame encoded to jpg
                std::vector<uchar> jpg;
                
                typedef ball std::pair<bool, std::map<std::string, double>>;
                
                std::pair<ball, ball> tracker_data = {
                    {
                        false,
                        {
                            {"temp", 0}
                        }
                    },
                    {
                        false,
                        {
                            {"temp", 0}
                        }
                    }
                };
                
                // Is this needed?
                MSGPACK_DEFINE(jpg, ball);
            };
        
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
    };
};

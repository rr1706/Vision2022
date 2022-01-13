#include "opencv2/core/mat.hpp"
#include "opencv2/videoio.hpp"
#include <Poco/Types.h>

namespace frc1706 {
    class BallTracker {
        public:
            // which to use...
            BallTracker(cv::Mat input);
            BallTracker(cv::VideoCapture input);
            virtual ~BallTracker();

            /**
             * @return a cv::Mat that is the final processed image/cv::Mat 
             */
            cv::Mat process();
            
            /**
             * @return an int that is the return code
             */
            int run();

            

        private:
            cv::Mat _base;
    };
};
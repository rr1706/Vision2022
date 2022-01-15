#include "frc1706/BallTracker.hpp"

#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"

#include <cstdlib>
#include <iostream>

using namespace frc1706;

int main() {
    /**
     * Create a cv::VideoCaptureProperties list to store the parameters of
     * the cameras used
     */ 
    //std::vector<cv::VideoCaptureProperties> ball_cam_props;
    //ball_cam_props.set(cv::CAP_PROP_FRAME_WIDTH, 480);
    //ball_cam_props.set(cv::CAP_PROP_FRAME_HEIGHT, 640);

    // Create tracker objects
    // TODO: how can these be more easily changed on the fly?
    BallTracker ball_cam(cv::VideoCapture(0, cv::CAP_V4L2));
    //TapeTracker tape_cam(cv::VideoCapture(1, cv::CAP_V4L2));

    // Run the tracking algorithms, these run async
    ball_cam.run();
    //tape_cam.run();

#define DISPLAY 1 // Make this a compile option     
    // Loop until esc key is pressed 
    while(true) {
#ifdef DISPLAY
        try {
            // If frame not empty display it
            if(!ball_cam.getCurrentFrame().empty()) {
                cv::imshow("Ball Camera", ball_cam.getCurrentFrame());
            }
            //cv::imshow("Tape Camera", tape_cam.getCurrentFrame());
        } catch(const cv::Exception &err) {
            std::cerr << err.what();
            std::exit(EXIT_FAILURE);
        }
#endif
        char esc = cv::waitKey(33);
        if(esc == 27) { break; }
    }

    std::cout << "Exiting\n";
    return EXIT_SUCCESS; 
}
//auto ballcam_jpeg = cv::imencode(".jpg", ballcam_base, quality);
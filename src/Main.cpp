#include "frc1706/BallTracker.hpp"

#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>

using namespace frc1706;

int main() {
    // Set camera parameters
    //std::vector<cv::VideoCaptureProperties> ball_cam_props;
    //ball_cam_props.set(cv::CAP_PROP_FRAME_WIDTH, 480);
    //ball_cam_props.set(cv::CAP_PROP_FRAME_HEIGHT, 640);

    BallTracker ball_cam(cv::VideoCapture(0, cv::CAP_V4L2));
    //TapeTracker tape_cam(cv::VideoCapture(1, cv::CAP_V4L2));
    
    ball_cam.run();
    //tape_cam.run();
    
    // Loop until esc key is pressed 
    while(true) {
        cv::imshow("Ball Camera", ball_cam.getCurrentFrame());
        //cv::imshow("Tape Camera", tape_cam.getCurrentFrame());
        std::cout << "Showing next frame\n";

        char esc = cv::waitKey(33);
        if(esc == 27) { break; }
    }

    std::cout << "Exiting\n";
    return EXIT_SUCCESS; 
}
//auto ballcam_jpeg = cv::imencode(".jpg", ballcam_base, quality);
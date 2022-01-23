#include "frc1706/RoboRIOClient.hpp"
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
    // Connect to robot first
    RoboRIOClient client; // TODO: Find IP
    
    /**
     * Create a cv::VideoCaptureProperties list to store the parameters of
     * the cameras used
     */ 
    //std::vector<cv::VideoCaptureProperties> ball_cam_props;
    //ball_cam_props.set(cv::CAP_PROP_FRAME_WIDTH, 480);
    //ball_cam_props.set(cv::CAP_PROP_FRAME_HEIGHT, 640);

    // Create tracker objects
    // TODO: how can these be more easily changed on the fly?
    //BallTracker ball_cam(cv::VideoCapture(0, cv::CAP_V4L2), client);
    //TapeTracker tape_cam(cv::VideoCapture(1, cv::CAP_V4L2), client);

    // Run the tracking algorithms, these run async, they also send the data
    //ball_cam.run();
    //tape_cam.run();


#undef DISPLAY // Make this a compile option     
    // Loop until esc key is pressed 
    while(true) {
#ifdef DISPLAY
        try {
            ball_cam.show("Ball Camera", true);
            //cv::imshow("Tape Camera", tape_cam.getCurrentFrame());
        } catch(const cv::Exception &err) {
            std::cerr << err.what();
            std::exit(EXIT_FAILURE);
        }
#endif
        client.send(); 
        char esc = cv::waitKey(33);
        if(esc == 27) { break; }
    }

    std::cout << "Exiting\n";
    return EXIT_SUCCESS; 
}
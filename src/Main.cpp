#include "frc1706/RoboRIOClient.hpp"
#include "frc1706/BallTracker.hpp"
#include "frc1706/TapeTracker.hpp"

#include "spdlog/common.h"
#include "spdlog/spdlog.h"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <vector>

using namespace frc1706;

int main() {
    // Change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    spdlog::set_level(spdlog::level::debug);

    spdlog::info("Attempting a connection to the robot");
    RoboRIOClient client("127.0.0.1", 1706);
    
    /**
     * Create a cv::VideoCaptureProperties list to store the parameters of
     * the cameras used
     */ 
    const std::vector<int> ball_cam_props = {
        cv::CAP_PROP_FRAME_WIDTH, 480,
        cv::CAP_PROP_FRAME_HEIGHT, 640
    };
    const std::vector<int> tape_cam_props = {
        cv::CAP_PROP_FRAME_WIDTH, 480,
        cv::CAP_PROP_FRAME_HEIGHT, 640
    };
 
    spdlog::info("Creating trackers");
    BallTracker ball_cam(cv::VideoCapture(0, cv::CAP_V4L2, ball_cam_props), client);
    TapeTracker tape_cam(cv::VideoCapture(1, cv::CAP_V4L2, tape_cam_props), client);

    spdlog::info("Running trackers");
    ball_cam.run();
    //tape_cam.run();

    // Loop until esc key is pressed 
    while(true) {
#ifdef DISPLAY
        try {
            ball_cam.show("Ball Camera", true);
            cv::imshow("Tape Camera", tape_cam.getCurrentFrame());
        } catch(const cv::Exception &err) {
            std::cerr << err.what();
            std::exit(EXIT_FAILURE);
        }
#endif
        char esc = cv::waitKey(33);
        if(esc == 27) { break; }
    }
    spdlog::info("Exiting");
    return EXIT_SUCCESS; 
}
#include "RobotClient.hpp"
#include "trackers/BallTracker.hpp"
#include "trackers/TapeTracker.hpp"
#include "sensors/ColorSensor.hpp"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include <vector>

int main() {
    // Change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    spdlog::set_level(spdlog::level::debug);

    spdlog::info("Attempting a connection to the robot");
    RobotClient client("");
    
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

    spdlog::info("Creating sensors");
    //sensors::ColorSensor color_one();

    spdlog::info("Creating trackers");
    trackers::BallTracker ball_cam(cv::VideoCapture(0, cv::CAP_FFMPEG, ball_cam_props), client);
    //trackers::TapeTracker tape_cam(cv::VideoCapture(1, cv::CAP_FFMPEG, tape_cam_props), client);

    spdlog::info("Running sensors and trackers");
    //color_one.run()
    ball_cam.run();
    //tape_cam.run();

    // Loop until esc key is pressed 
    spdlog::info("Starting stream");
    while(true) {
        client.imstream("cam1", ball_cam.getCurrentFrame());
        //imstream(tape_cam.getCurrentFrame());
    }
    
    spdlog::info("Exiting");
    return EXIT_SUCCESS; 
}
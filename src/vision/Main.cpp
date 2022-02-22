#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTable.h"
#include "cameraserver/CameraServer.h"
#include "opencv2/opencv.hpp"
#include "spdlog/spdlog.h"
#include <iostream>

const static inline int port = 1706;
const static inline cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

int main() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Starting vision code");
    
    spdlog::info("Binding mjpeg server to port: " + std::to_string(port));
    cs::CvSource cv_src("cv", cs::VideoMode::kBGR, 480, 640, 30);
    cs::MjpegServer srv("serve_cv", 1706);
    srv.SetSource(cv_src);

    spdlog::info("Connecting to network tables");
    nt::NetworkTableInstance inst = nt::NetworkTableInstance::GetDefault();
    std::shared_ptr<nt::NetworkTable> table = inst.GetTable("Vision");
    nt::NetworkTableEntry distance_entry = table->GetEntry("Ring Distance");
    nt::NetworkTableEntry xrot_entry = table->GetEntry("Ring X Rotation");
 
    cv::VideoCapture cap(0);
    cv::Mat threshed, gray, frame;
   
    while(true) {
        spdlog::info("Updating current frame");
        cap >> frame; // Update current frame

        if(frame.empty()) {
            throw std::runtime_error("Current frame is empty, unable to process");
        }

        // Stream frame to the driver station using wpilib's mjpeg server  
        cv_src.PutFrame(frame);
        
        spdlog::info("Processing current frame"); 
        // The image is going to be ir so may as well use gray
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); 
        // Find important elements in the image
        cv::threshold(gray, threshed, 0, 255, cv::THRESH_BINARY);
        // "Open" the threshed image(erode followed by dilate)
        cv::morphologyEx(threshed, threshed, cv::MORPH_OPEN, kernel);

        spdlog::info("Tracking current frame");
        // Find all external contours
        std::vector<std::vector<cv::Point>> cnts;
        cv::findContours(threshed, cnts, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        if(!cnts.empty()) {
            //https://github.com/rr1706/vision2013/blob/master/source/extrinsic.cpp
            //cv::solvePnPRansac(obj_pnts, img_pnts, cam_mtx, dist_coeff, r_vec, t_vec);

            double distance = 0;
            double xrot = 0;

            distance_entry.SetDouble(distance);
            xrot_entry.SetDouble(xrot);
        }
    } 
    
    return 0;
}
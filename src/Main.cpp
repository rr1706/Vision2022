#include "frc1706/DriverClient.hpp"

#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>

using namespace frc1706;

int main() {
    //std::vector<uchar> quality; // 1-100, default 20 
    //cv::VideoCapture ballcam(0);
    //cv::Mat ballcam_base;
    //cv::VideoCapture tapecam(1);
    //cv::Mat tapecam_base;

    DriverClient client_socket;

    // Adjust camera parameters
    // FIXME: Why does this error?
    //ballcam.set(cv::CAP_PROP_FRAME_WIDTH, 480);
    //ballcam.set(cv::CAP_PROP_FRAME_HEIGHT, 640);

    while(true) {
    //while(ballcam.isOpened()) {
        //ballcam >> ballcam_base;
        
        client_socket.sendTest();
        
        //cv::imshow("Ball Camera", ballcam_base);

        //auto ballcam_jpeg = cv::imencode(".jpg", ballcam_base, quality);
        
        // send jpegs

        char esc = cv::waitKey(33);
        if(esc == 27) {
            //ballcam.release();
            break;
        }
    }

    std::cout << "Exiting video stream\n";
    return 0; 
}
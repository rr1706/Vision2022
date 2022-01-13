#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Types.h"

#include <bits/stdint-uintn.h>
#include <iostream>
#include <string>
#include <vector>


namespace frc1706 {
    class CameraServer {
        public:
            CameraServer(const std::string ip = "localhost", Poco::UInt16 port = 1706) :
                _address(ip, port), _socket(_address), _data_stream(_socket) {

            }
            virtual ~CameraServer() {
                std::cout << "Closing server broadcasting on %s\n",  _address.host().toString();
            }

            void sendTest() {
                this->_data_stream << 
                    "HTTP/1.0 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "<html><head><title>Simple test</title></head>"
                    "<body><h1>Hello, world!</h1></body></html>"
                << std::flush;
            }

        private:
            Poco::Net::SocketAddress _address; // does bind + listen
            Poco::Net::StreamSocket _socket;
            Poco::Net::SocketStream _data_stream;
    };
};

int main() {

    std::vector<uchar> quality; // 1-100, default 20 
    cv::VideoCapture ballcam(0);
    cv::Mat ballcam_base;
    //cv::VideoCapture tapecam(1);
    //cv::Mat tapecam_base;

    // Adjust camera parameters
    ballcam.set(cv::CAP_PROP_FRAME_WIDTH, 480);
    ballcam.set(cv::CAP_PROP_FRAME_HEIGHT, 640);

    while(ballcam.isOpened()) {
        ballcam >> ballcam_base;

        cv::imshow("Ball Camera", ballcam_base);

        auto ballcam_jpeg = cv::imencode(".jpg", ballcam_base, quality);
        
        // send jpegs

        char esc = cv::waitKey(33);
        if(esc == 27) {
            ballcam.release();
            break;
        }
    }

    std::cout << "Exiting video stream\n";
    return 0; 
}
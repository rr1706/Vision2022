#include "frc1706/RoboRIOClient.hpp"
/* 
using namespace Poco::Net;

namespace frc1706 {
    RoboRIOClient::RoboRIOClient(const std::string ip, Poco::UInt16 port) try {
        this->_connect(ip, port);
    } catch (Poco::Exception err) {
        std::cerr << err.displayText() << std::endl;
        std::exit(EXIT_FAILURE);
    };

    RoboRIOClient::~RoboRIOClient() {} // Setup safe disconnect
    
    int RoboRIOClient::send() try {
        cv::Mat image = cv::imread("/home/will/Pictures/pepe-nintendo.jpeg");
        std::stringstream buffer;
        std::vector<uchar> jpg_src;

        if(cv::imencode(".jpg", image, jpg_src)) {
            msgpack::pack(buffer, jpg_src);
            //buffer.seekg(0);
            this->_dg_socket.sendBytes(buffer.rdbuf(), sizeof(buffer));
        } else {
            return EXIT_FAILURE;
        } 
        
        return EXIT_SUCCESS;
    } catch(const Poco::Exception &err) {
        std::cerr << err.displayText() << std::endl;
        return EXIT_FAILURE;
    } catch(const cv::Exception & err) {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    };

    int RoboRIOClient::_connect(const std::string &ip, const Poco::UInt16 &port) try {
        std::cout << "Connecting to " << ip << ":" << port << std::endl;
        this->_dg_socket.connect(Poco::Net::SocketAddress(ip, port)); // Connect to client (this should be the other way around)
        return EXIT_SUCCESS;
    } catch(const Poco::Exception &err) {
        std::cerr << err.displayText() << std::endl;
        return EXIT_FAILURE;
    }
}; */
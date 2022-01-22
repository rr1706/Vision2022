#include "frc1706/RoboRIOClient.hpp"

#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"

#include "Poco/Net/SocketAddress.h"
#include <Poco/Net/IPAddress.h>
#include <Poco/Exception.h>
#include "Poco/Types.h"

#include "msgpack.hpp"
#include "opencv2/imgcodecs.hpp"

#include <cstdlib>
#include <iostream>
#include <msgpack/v3/adaptor/array_ref_decl.hpp>
#include <sstream>
#include <string>
#include <vector>

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
        //msgpack::type::tuple<std::vector<uchar>> msg(jpg);

        if(cv::imencode(".jpg", image, jpg_src)) {
            msgpack::pack(buffer, jpg_src);
            buffer.seekg(0);
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
};
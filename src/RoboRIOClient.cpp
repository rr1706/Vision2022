#include "frc1706/RoboRIOClient.hpp"

#include "Poco/Net/SocketAddress.h"
#include <Poco/Net/IPAddress.h>
#include <Poco/Exception.h>
#include "Poco/Types.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace Poco::Net;

namespace frc1706 {
    RoboRIOClient::RoboRIOClient(const std::string ip, Poco::UInt16 port) try {
        this->_connect(ip, port);
    } catch (Poco::Exception err) {
        std::cerr << err.displayText() << std::endl;
        std::exit(EXIT_FAILURE);
    };

    RoboRIOClient::~RoboRIOClient() {} // Setup safe disconnect

    
    void RoboRIOClient::sendTest() try {
        std::string data = "Hello!";
        this->_dg_socket.sendBytes(data.data(), data.size());
    } catch (const Poco::Exception &err) {
        std::cerr << err.displayText() << std::endl;
        std::exit(EXIT_FAILURE);
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
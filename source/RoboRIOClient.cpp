#include "frc1706/RoboRIOClient.hpp"

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"

#include "nlohmann/json.hpp"

#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>

#include <sys/socket.h>

using namespace nlohmann;

namespace frc1706 {
    RoboRIOClient::RoboRIOClient(const std::string ip, uint16_t port) {
        this->_connect(ip, port);
    }

    RoboRIOClient::~RoboRIOClient() {} // Setup safe disconnect

// -------------------------------------------------------------------------------------------- 

    int RoboRIOClient::sendMessage() {
        cv::Mat img = cv::imread("/home/will/Pictures/trees.png");
        std::vector<uchar> jpg_src;
        
        json obj;

        if(cv::imencode(".jpg", img, jpg_src)) {
            obj["img"] = jpg_src;
            
            int offset = 0; // Total bytes sent
            int bytes_sent;
            while (offset <= obj.size()) {
                bytes_sent = send(this->_sock, obj.dump().c_str(), this->_buf.size(), 0);
                offset += bytes_sent;
                std::cout << "Sent " << offset << " of " << sizeof(this->_buf.size()) << " bytes\n";
            }
        } else {
            return EXIT_FAILURE;
        }
        
        return EXIT_SUCCESS;
    }

// -------------------------------------------------------------------------------------------- 

    int RoboRIOClient::_connect(const std::string &ip, const uint16_t &port) {
        std::cout << "Connecting to " << ip << ":" << port << std::endl;
        // Datagram(UDP)
	    if ((this->_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		    std::cerr << "Socket creation error\n";
		    return EXIT_FAILURE;
	    }

	    this->_addr.sin_family = AF_INET; // ipv4
	    this->_addr.sin_port = htons(PORT); // Bind to port
	
	    // Convert IPv4 and IPv6 addresses from text to binary form
	    if(inet_pton(AF_INET, "127.0.0.1", &(this->_addr).sin_addr)<=0) {
		    std::cerr << "Invalid address/Address not supported\n";
		    return EXIT_FAILURE;
    	}

    	if (connect(this->_sock, (struct sockaddr *)&(this->_addr), sizeof(this->_addr)) < 0) {
		    std::cerr << "Connection Failed\n";
		    return EXIT_FAILURE;
	    }
        return EXIT_SUCCESS;
    }
};
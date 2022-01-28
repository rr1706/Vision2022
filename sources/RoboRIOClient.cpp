#include "frc1706/RoboRIOClient.hpp"

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"

#include "nlohmann/json.hpp"

#include <cstddef>
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
        cv::Mat img = cv::imread("/home/will/Pictures/Webcam/2022-01-24-170422.jpg");
        std::vector<uchar> jpg_src;
        json obj;

        if(cv::imencode(".jpg", img, jpg_src)) {
            obj["img"] = jpg_src;

            std::cout << obj.dump() << std::endl;

            // Total bytes sent
            size_t bytes_sent = 0;
            // While the offset is less then size of obj send the obj in kb sized packets 
            for(size_t offset = 0; offset < obj.dump().size();) {
                bytes_sent = send(
                    this->_sock, 
                    obj.dump().substr(offset, offset+this->_buf.size()).c_str(), 
                    this->_buf.size(), 
                    0
                ); 
                offset += bytes_sent;

                std::cout << "Sent " << offset << " of " << obj.dump().size() << " bytes\n";
            }
            // Send a message footer to indecate that the message is over
            std::cout << (char)'e' << std::endl;
            send(this->_sock, 0x00, 1, 0);
            std::cout << "Finished sending message\n"; 
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
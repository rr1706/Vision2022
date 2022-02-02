#include "frc1706/RoboRIOClient.hpp"

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"

#include "msgpack.hpp"

#include "spdlog/spdlog.h"

#include <sys/socket.h>

#include <exception>
#include <stdexcept>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

namespace frc1706 {
    RoboRIOClient::RoboRIOClient(const std::string ip, uint16_t port) {
        this->_connect(ip, port);
    }

    RoboRIOClient::~RoboRIOClient() {} // Setup safe disconnect

// -------------------------------------------------------------------------------------------- 

    void RoboRIOClient::sendMessage(const std::stringstream &msg) {        
        std::lock_guard<std::mutex> lock(this->_client_mutex);
        // Total bytes sent
        size_t bytes_sent = 0;

        // While the offset is less then size of obj send the obj in kb sized packets 
        for(size_t offset = 0; offset < msg.str().size();) {
            bytes_sent = send(
                this->_sock, 
                msg.str().substr(offset, offset+this->_buf.size()).c_str(),
                this->_buf.size(), 
                0
            ); 
            offset += bytes_sent;
            spdlog::debug("Sent {} of {} bytes", offset, msg.str().size());
        }

        spdlog::info("Sent message to server");
    }

// -------------------------------------------------------------------------------------------- 

    std::stringstream RoboRIOClient::createMessage(const std::map<std::string, double> &data) {
        std::lock_guard<std::mutex> lock(this->_client_mutex);
        // Create the buffer that stores the message to be sent
        std::stringstream ret; 
        msgpack::packer<std::stringstream> packer(ret); 
        
        // Pack the data 
        msgpack::pack(ret, data);

        // Ensure stream starts from the beginning 
        ret.seekg(0);

        return ret;
    }

// -------------------------------------------------------------------------------------------- 

    void RoboRIOClient::_connect(const std::string &ip, const uint16_t &port) {
        std::lock_guard<std::mutex> lock(this->_client_mutex);
        spdlog::info("Connecting to {}:{}", ip, port);

        // Datagram(UDP)
	    if ((this->_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		    spdlog::critical("Failed to create socket!!");
            throw std::runtime_error("Failed to create socket!!");
	    }

	    this->_addr.sin_family = AF_INET; // ipv4
	    this->_addr.sin_port = htons(port); // Bind to port
	
	    // Convert IPv4 and IPv6 addresses from text to binary form
	    if(inet_pton(AF_INET, ip.c_str(), &(this->_addr).sin_addr) <= 0) {
		    spdlog::critical("Invalid/Unsupported address!!");
            throw std::runtime_error("Invalid/Unsupported address!!");
    	}

    	if (connect(this->_sock, (struct sockaddr *)&(this->_addr), sizeof(this->_addr)) < 0) {
		    spdlog::critical("Failed to connect socket!!");
            throw std::runtime_error("Failed to connect socket!!");
	    }

        _sendGreeting();
    }

// -------------------------------------------------------------------------------------------- 

    void RoboRIOClient::_sendGreeting() {
        // Total bytes sent
        size_t bytes_sent = 0;
        // Greeting message to tell the server we are connected
        std::string greeting = "Hello There!";

        // While the offset is less then size of obj send the obj in kb sized packets 
        bytes_sent = send(this->_sock, greeting.c_str(), this->_buf.size(), 0); 

        if(bytes_sent <= 0) {
            spdlog::warn("Unable to send greeting");
            throw "Unable to send greeting";
        }

        spdlog::info("Sent message to server");
    }
};
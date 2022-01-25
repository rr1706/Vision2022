#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 1706
 
namespace frc1706 {
    class RoboRIOClient {
        public:
            RoboRIOClient(const std::string ip = "127.0.0.1", uint16_t port = 1706);
            virtual ~RoboRIOClient();

            int sendMessage();
            
        private:
            int _connect(const std::string &ip, const uint16_t &port);
            int _sock = 0, valread; // What's valread?????        
	        struct sockaddr_in _addr;
	        char buffer[1024] = {0};
    };
}; // namespace frc1706
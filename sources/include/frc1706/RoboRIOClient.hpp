#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <array>

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
            int _sock = 0;        
	        struct sockaddr_in _addr;
            std::array<char, 1024> _buf;
    };
}; // namespace frc1706
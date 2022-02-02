#pragma once

#include "msgpack.hpp"

#include <arpa/inet.h>

#include <sstream>
#include <mutex>
#include <array>
#include <map>

namespace frc1706 {
    class RoboRIOClient {
        public:
            RoboRIOClient(const std::string ip = "127.0.0.1", uint16_t port = 1706);
            virtual ~RoboRIOClient();

            void sendMessage(const std::stringstream &msg);
            
            std::stringstream createMessage(const std::map<std::string, double> &data); 
        
        private:
            void _connect(const std::string &ip, const uint16_t &port);
            void _sendGreeting();

            int _sock = 0;        
	        struct sockaddr_in _addr;
            std::array<char, 1024> _buf;
            std::mutex _client_mutex;
    };
}; // namespace frc1706
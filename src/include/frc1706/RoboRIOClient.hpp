#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Types.h"

#include "msgpack.hpp"

#include <iostream>
#include <string>
#include <list>

namespace frc1706 {
    class RoboRIOClient {
        public:
            RoboRIOClient(const std::string ip = "127.0.0.1", Poco::UInt16 port = 1706);
            virtual ~RoboRIOClient();

            /**
             * TODO
             */
            int send();
            
        private:
            int _connect(const std::string &ip, const Poco::UInt16 &port);
            
            Poco::Net::DatagramSocket _dg_socket;
    };
}; // namespace frc1706
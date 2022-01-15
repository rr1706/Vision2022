#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Types.h"

#include <iostream>
#include <string>

namespace frc1706 {
    class DriverClient {
        public:
            DriverClient(const std::string ip = "127.0.0.1", Poco::UInt16 port = 1706);
            virtual ~DriverClient();

            void sendTest();

        private:
            int _connect(const std::string &ip, const Poco::UInt16 &port);
            
            Poco::Net::DatagramSocket _dg_socket;
    };
}; // namespace frc1706
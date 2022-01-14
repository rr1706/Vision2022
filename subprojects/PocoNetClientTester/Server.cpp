#include "Poco/Net/UDPClient.h"
#include "Poco/Net/SocketAddress.h"
#include <Poco/Exception.h>

#include <iostream>

using namespace Poco::Net;

int main() try {
    SocketAddress address{"127.0.0.1", 1706};
    DatagramSocket dg_socket{address};
    char buf[512];
   
    while(true) {
        Poco::Net::SocketAddress sender;//("127.0.0.1", 1706);
        int data = dg_socket.receiveFrom(buf, sizeof(buf) - 1, sender);
        buf[data] = '\0';
        std::cout << sender.toString() << ": " << buf << std::endl << std::endl;
    }
    
    return EXIT_SUCCESS;

} catch(Poco::Exception &err) {
    std::cerr << err.displayText() << std::endl;
    return EXIT_FAILURE;
}

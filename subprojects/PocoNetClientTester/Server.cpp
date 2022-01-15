#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/UDPClient.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Exception.h"

#include <iostream>
#include <chrono>

using namespace Poco::Net;

int main() try {
    SocketAddress address{"127.0.0.1", 1706};
    DatagramSocket dg_socket{address};
    char buf[512];
    
    int msgs = 0;
    std::chrono::time_point<std::chrono::system_clock> start; 
    std::cout << "Listening on " << address.toString() << std::endl; 

    while(true) {
        SocketAddress sender;
        int data = dg_socket.receiveFrom(buf, sizeof(buf) - 1, sender);
        buf[data] = '\0';
        msgs++;
        if (msgs == 1) {
            start = std::chrono::system_clock::now();
        }
        std::cout << "Message number " << msgs << ": " << buf << std::endl << std::endl;
        if(msgs == 10) {
            break;
        }
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Got 10 messages in " << elapsed.count() << "ms" << '\n';
    
    return EXIT_SUCCESS;

} catch(Poco::Exception &err) {
    std::cerr << err.displayText() << std::endl;
    return EXIT_FAILURE;
}

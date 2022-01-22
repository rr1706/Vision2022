#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/UDPClient.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Exception.h"

#include "msgpack.hpp"

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

#include <iostream>
#include <msgpack/v3/adaptor/detail/cpp11_msgpack_tuple_decl.hpp>
#include <sstream>
#include <chrono>
#include <vector>

using namespace Poco::Net;

int main() try {
    SocketAddress address{"127.0.0.1", 1706};
    DatagramSocket dg_socket{address};
    char buf[512];
    
    std::cout << "Listening on " << address.toString() << std::endl; 

    while(true) {
        SocketAddress sender;
        int data = dg_socket.receiveFrom(buf, sizeof(buf) - 1, sender);
        buf[data] = '\0';
        //std::vector<uchar> jpg;
        std::string msg_data(buf); // Do I need to cast this to a string here?
        msgpack::object msg = msgpack::unpack(msg_data.data(), msg_data.size()).get();
        
        //msg.convert(jpg); 
        
        cv::Mat image = cv::imdecode(cv::Mat(msg.as<std::vector<uchar>>()), 1);
        
        cv::imshow(sender.toString(), image);
    }

    return EXIT_SUCCESS;

} catch(Poco::Exception &err) {
    std::cerr << err.displayText() << std::endl;
    return EXIT_FAILURE;
}

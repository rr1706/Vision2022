#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

#include <linux/i2c.h>

#include "nlohmann/json.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <array>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 1706

using namespace nlohmann;

int main() {
	int sock;
	struct sockaddr_in srv_addr, cli_addr;
	std::array<uint8_t, 1024> buffer;

    // Create socket file descriptor
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
		std::cerr << "socket failed\n";
		return EXIT_FAILURE;
	}
	
	memset(&srv_addr, 0, sizeof(srv_addr));
	memset(&cli_addr, 0, sizeof(cli_addr));
   
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = INADDR_ANY;
	srv_addr.sin_port = htons(PORT);

	// Forcefully attaching socket to the port
	if (bind(sock, reinterpret_cast<sockaddr*>(&srv_addr), sizeof(srv_addr)) < 0) {
		std::cerr << "bind failed\n";
		return EXIT_FAILURE;
	}
	
	std::vector<uint8_t> msg;
	size_t bytes_recv = 0;
	while(true) {
		// Recive data from socket, add it to the buffer, then add the buffer to the final message
		bytes_recv += recvfrom(
			sock, 
			buffer.data(), 
			buffer.size(), 
			MSG_WAITALL, 
			reinterpret_cast<sockaddr*>(&cli_addr), 
			reinterpret_cast<socklen_t*>(sizeof(cli_addr))
		);
		std::cout << "Recived message" << std::endl;
		std::cout << buffer.data() << std::endl;
		//msg.push_back(buffer.data());
			
		// Test if the message is finished then display
		if(buffer.data()[buffer.size() - 1] == NULL) try {
			std::cout << "Message complete\n";
			
			//std::ifstream file(buffer);
			//json obj = json::parse(msg);
			//file >> obj;		
			//std::cout << obj.dump() << std::endl;

			//cv::Mat img = cv::imdecode(, 0); 
    		//cv::imshow("image", img);
		} catch(const cv::Exception &err) {
			std::cerr << err.what() << std::endl;
			return EXIT_FAILURE;
		} catch(const json::parse_error &err) {
			std::cerr << err.what() << std::endl;
			return EXIT_FAILURE;
		}
	}
    return EXIT_SUCCESS;
}

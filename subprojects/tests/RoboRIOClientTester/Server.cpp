#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

#include "nlohmann/json.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 1706
#define MAX_MSG_SIZE 1024 // half kb

using namespace nlohmann;

int main() {
	int sock;
	struct sockaddr_in srv_addr, cli_addr;
	char buffer[MAX_MSG_SIZE];

    // Creating socket file descriptor
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
		std::cerr << "socket failed\n";
		return EXIT_FAILURE;
	}
	
	memset(&srv_addr, 0, sizeof(srv_addr));
	memset(&cli_addr, 0, sizeof(cli_addr));
   
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = INADDR_ANY;
	srv_addr.sin_port = htons( PORT );

	// Forcefully attaching socket to the port
	if (bind(sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr))<0) {
		std::cerr << "bind failed\n";
		return EXIT_FAILURE;
	}

	socklen_t len;
	int n = 0;

	len = sizeof(cli_addr);
	while(true) {
		while(n < MAX_MSG_SIZE) {
			n += recvfrom(
				sock, 
				(char *)buffer, 
				MAX_MSG_SIZE, 
				MSG_WAITALL, 
				(struct sockaddr *) &cli_addr, 
				&len
			);
		
			buffer[n] = '\0';

			std::cout << buffer << std::endl;
			//std::cout << n << " of " << MAX_MSG_SIZE << std::endl;
			if(n >= MAX_MSG_SIZE) try {
				std::cout << "Recived message\n";
				
				//std::ifstream file(buffer);
				json obj = json::parse(buffer);
				//file >> obj;		

				std::cout << obj.dump() << std::endl;
	
				//cv::Mat img = cv::imdecode(, 0); 
    			//cv::imshow("image", img);
			} catch(const cv::Exception &err) {
				std::cerr << err.what() << std::endl;
				return EXIT_FAILURE;
			}
		} 
		
	}
    return EXIT_SUCCESS;
}

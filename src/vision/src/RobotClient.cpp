#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include "spdlog/spdlog.h"
#include "RobotClient.hpp"
#include "httplib.h"

RobotClient::RobotClient(const std::string &address) {}

RobotClient::~RobotClient() {} // Setup safe disconnect

// -------------------------------------------------------------------------------------------- 

void RobotClient::connect(const std::string &address) {
    this->_sendGreeting();
}

// -------------------------------------------------------------------------------------------- 

void RobotClient::_sendGreeting() {}

// --------------------------------------------------------------------------------------------

void RobotClient::imstream(std::string route, cv::Mat img) {
    std::vector<uint8_t> jpg;
    cv::imencode(".jpg", img, jpg);

    // HTTP
    httplib::Server svr;
    std::string content(jpg.begin(), jpg.end());

    svr.Get("/"+route+"/video", [jpg, content](const httplib::Request &, httplib::Response &res) {
       res.set_content(content, "image/jpeg");
    });
    svr.Get("/"+route, [jpg, content](const httplib::Request &, httplib::Response &res) {
        res.set_content("<html><body><img src=http://"+this->_host+"/video></body></html>", "text/html");
    });

    svr.listen(this->_host, this->_port);
}
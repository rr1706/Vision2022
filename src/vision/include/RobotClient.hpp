#pragma once
#include <grpcpp/support/client_interceptor.h>
#include "opencv2/core.hpp"
#include "Robot.grpc.pb.h"
#include "Robot.pb.h"
#include <memory>
#include <string>
#include <map>

class RobotClient: public frc::vision::Robot::Service {
    public:
        RobotClient(const std::string &address);
        virtual ~RobotClient();

        void imstream(std::string route, cv::Mat img);   
        
    protected: 
        void connect(const std::string &address);
    
    private:
        void _sendGreeting();

        std::shared_ptr<grpc::Channel> _channel;
        frc::vision::ConnectReply::TeamColor _team_color;
};
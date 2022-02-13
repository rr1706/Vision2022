#pragma once
#include "Robot.pb.h"
#include "RobotClient.hpp"
#include <future>

namespace async {
    class AsyncPipeline {
        public:
            AsyncPipeline(
                RobotClient &client, 
                const frc::vision::ConnectRequest::Type &type, 
                const frc::vision::ConnectRequest::Location &location
            );
            virtual ~AsyncPipeline();

            void run();
            
        protected:
            virtual void task() = 0;
            
            // Networking client to use
            const std::shared_ptr<RobotClient> client;

        private:
            // Initalize async task in class so it won't go out of scope later
            std::future<void> _task;
            // Info from GRPC
            frc::vision::ConnectRequest::Type _pipeline_type;
            frc::vision::ConnectRequest::Location _location;
    };
};

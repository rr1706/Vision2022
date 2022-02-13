#include "async/AsyncPipeline.hpp"
#include "RobotClient.hpp"
#include <memory>

namespace async {
    AsyncPipeline::AsyncPipeline(
        RobotClient &client,
        const frc::vision::ConnectRequest::Type &type, 
        const frc::vision::ConnectRequest::Location &location
    ): client(&client), _location(location), _pipeline_type(type) {}

    void AsyncPipeline::run() {
        /**
         * The value of _task isn't used anywhere but it is required to store
         * the output of std::async to keep it from destroying itself
         */
        this->_task = std::async(std::launch::async, &AsyncPipeline::task, this);
    }
}
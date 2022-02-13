# Create the executable to be deployed
add_executable(vision 
    src/Main.cpp
    src/RingTracker.cpp
    src/BallTracker.cpp
    src/ColorSensor.cpp
    src/RobotClient.cpp
    src/AsyncPipline.cpp
    src/AsyncTracker.cpp
)
target_include_directories(vision PRIVATE 
    include
    ${messages_INCLUDES}
    ${gRPC_INCLUDES} 
    ${opencv_INCLUDE}
    ${spdlog_INCLUDES}
    ${httplib_INCLUDES}
)
target_link_libraries(vision 
    messages 
    gRPC::gRPC 
    spdlog::spdlog 
    opencv::opencv
    httplib::httplib
)
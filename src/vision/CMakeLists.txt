# Create the executable to be deployed
add_executable(vision 
    src/Main.cpp
)
target_include_directories(vision PRIVATE 
    include
    ${opencv_INCLUDE}
    ${spdlog_INCLUDES}
)
target_link_libraries(vision 
    cscore
    cameraserver
    ntcore
    wpimath
    opencv::opencv
    spdlog::spdlog 
)
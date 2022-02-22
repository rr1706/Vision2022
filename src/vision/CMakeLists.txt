# Create the executable to be deployed
file(GLOB SRCS ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB HDRS ${CMAKE_CURRENT_LIST_DIR}/*.hpp)
add_executable(vision 
    ${SRCS} ${HDRS}
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
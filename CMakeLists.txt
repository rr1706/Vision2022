# Custom variables/options
set(frc_year "Current FRC season" CACHE STRING "2022")
set(team_number "Given FRC team number" CACHE STRING "1706")
set(user "Username of deploy target" CACHE STRING "frc")
set(host "Hostname of deploy target" CACHE STRING "jetson")
set(conan_profile "Conan profile to use" CACHE FILEPATH "resources/conan/default.jinja")

# Set internal CMake variables
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

# Define meta data from CMake project
cmake_minimum_required(VERSION 3.18)
project(Vision VERSION 0.2.0)

# Source dependencies from Conan 
add_custom_target(conan 
    comment "Installs packages from conanfile.txt"
    command conan install ${CMAKE_SOURCE_DIR} -if ${CMAKE_BINARY_DIR}/conan -pr:b=${conan_profile} --build missing -s build_type=${CMAKE_BUILD_TYPE}
)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/conan)

# Add dependencies to project
find_package(grpc REQUIRED)
find_package(spdlog REQUIRED)
find_package(ffmpeg REQUIRED)
find_package(opencv REQUIRED)

# Create the executable to be deployed
add_executable(vision 
    src/Main.cpp
    src/TapeTracker.cpp
    src/BallTracker.cpp
    src/ColorSensor.cpp
    src/RoboRIOClient.cpp
)
target_include_directories(vision PRIVATE src/include)
target_link_libraries(vision grpc::grpc spdlog::spdlog ffmpeg::ffmpeg opencv::opencv)

# Custom task
add_custom_command(deploy,
    comment "Deploys build artifacts and deploy folder to board"
    command python scripts/deploy.py ${team_number} ${user} ${host}
)
add_custom_command(run,
    comment "Runs the primary vision application"
    command ${CMAKE_BINARY_DIR}/bin/vision
)
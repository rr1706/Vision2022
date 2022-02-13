# Custom variables/options
set(frc_year "2022")
set(team_number "1706")
set(user "frc")
set(host "jetson")
set(conan_profile "resources/conan/default.jinja")

# Set internal CMake variables
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/lib)

# Define meta data from CMake project
cmake_minimum_required(VERSION 3.18)
project(Vision VERSION 0.2.0)

# Source dependencies from Conan
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/conan)
execute_process(
    COMMAND conan install ${CMAKE_SOURCE_DIR} 
    -if ${CMAKE_BINARY_DIR}/conan 
    -pr:b=${conan_profile} 
    --build missing
    -s build_type=Release
)

# Add dependencies to project
find_package(gRPC REQUIRED)
find_package(spdlog REQUIRED)
find_package(OpenCV REQUIRED)
find_package(httplib REQUIRED)
find_package(Protobuf REQUIRED)

# Include projects
add_subdirectory(src/messages)
add_subdirectory(src/vision)

# Custom task
add_custom_target(deploy
    COMMENT "Deploys build artifacts and deploy folder to board"
    COMMAND python scripts/deploy.py ${team_number} ${user} ${host}
)
add_custom_target(run
    COMMENT "Runs the primary vision application"
    COMMAND ${CMAKE_BINARY_DIR}/bin/vision
)

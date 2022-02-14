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

# For WPILIB
set(BUILD_SHARED_LIBS OFF)
set(BUILD_GMOCK OFF)
set(INSTALL_GTEST OFF)
set(WITH_CSCORE ON)
set(WITH_EXAMPLES OFF)
set(WITH_GUI OFF)
set(WITH_JAVA OFF)
set(WITH_OLD_COMMANDS OFF)
set(WITH_SIMULATION_MODULES OFF)
set(WITH_TESTS OFF)
set(WITH_WPILIB ON)
set(WITH_WPIMATH ON)

# Define meta data from CMake project
cmake_minimum_required(VERSION 3.18)
project(Vision VERSION ${frc_year}.2.0)

include(FetchContent)
FetchContent_Declare(allwpilib
    GIT_REPOSITORY https://github.com/wpilibsuite/allwpilib/
    GIT_TAG main #v${frc_year}.3.1
)
FetchContent_MakeAvailable(allwpilib)

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
find_package(spdlog REQUIRED)
find_package(OpenCV REQUIRED)

# Include projects
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

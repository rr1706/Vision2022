# Project info
project(
    'Vision',
    'cpp',
    version: '2022.2.0',
    default_options: ['cpp_std=c++17', 'warning_level=3', 'layout=flat', 'unity=on']
)

# Variables
team_number = '1706'
user = 'frc'
host = 'jetson'

# Pull dependencies from conanfile
run_command('conan', 'install', meson.source_root(), '-if', meson.build_root(), '--build missing')

# Dependancies
spdlog = dependency('spdlog')
opencv = dependency('opencv4')
threads = dependency('threads')
msgpack = dependency('msgpack')

# Create the executable to be deployed
vision = executable(
    'vision',
    [
        'src/Main.cpp', 
        'src/TapeTracker.cpp',
        'src/BallTracker.cpp', 
        'src/ColorSensor.cpp', 
        'src/RoboRIOClient.cpp' 
    ],
    dependencies: [opencv, msgpack, spdlog, threads],
    include_directories: include_directories('src/include')
)

# Add test targets
test('basic', vision)

# Custom task
run_target('deploy',
    command: [
        'python', 
        'resources/tasks/deploy.py', 
        team_number, 
        user, host
    ]
)
run_target('runTest', 
    command: [
        'python', 
        'resources/tasks/deploy.py', 
        team_number, 
    ]
)
project(
    'Vision2022',
    'cpp',
    version: '0.2.0',
    default_options: ['cpp_std=c++17', 'warning_level=3', 'layout=flat']
)

team_number = '1706'
frc_year = '2022'
user = 'frc'
host = 'jetson'

# Dependancies
opencv = dependency('opencv4')
msgpack = dependency('msgpack')
threads = dependency('threads')
spdlog = subproject('spdlog').get_variable('spdlog_dep')

# Create the main executable to be deployed
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
        'resources/meson/scripts/deploy.py', 
        team_number, 
        frc_year, 
        user, 
        host
    ]
)
run_target('runTest', 
    command: [
        'python', 
        'resources/meson/scripts/test.py', 
        team_number, 
        frc_year
    ]
)
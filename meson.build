project(
    'Vision2022',
    'cpp',
    version: '0.2.0',
    default_options: ['cpp_std=c++11', 'warning_level=3', 'layout=flat']
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
        'sources/Main.cpp', 
        'sources/TapeTracker.cpp',
        'sources/BallTracker.cpp', 
        'sources/ColorSensor.cpp', 
        'sources/RoboRIOClient.cpp' 
    ],
    dependencies: [opencv, msgpack, spdlog, threads],
    include_directories: include_directories('sources/include')
)

# Add test targets
test('basic', vision)

# Custom task
run_target('deploy', command: ['python', 'scripts/deploy.py', team_number, frc_year, user, host])
run_target('setup', command: ['python', 'scripts/setup.py', team_number, frc_year])
run_target('runTest', command: ['python', 'scripts/test.py', team_number, frc_year])


project(
    'Vision2022',
    'cpp',
    version: '0.2.0',
    default_options: ['cpp_std=c++11']
)

team_number = '1706'
frc_year = '2022'
jetson_user = 'frc'
jetson_ip = 'jetson'

# Dependancies
opencv = dependency('opencv4')
threads = dependency('threads')
spdlog = subproject('spdlog').get_variable('spdlog_dep')
lws = subproject('libwebsockets').get_variable('libwebsockets_dep')
json = subproject('nlohmann_json').get_variable('nlohmann_json_dep')

# Create the main executable to be deployed
vision = executable(
    'vision',
    [
        'source/Main.cpp', 
        'source/TapeTracker.cpp',
        'source/BallTracker.cpp', 
        'source/RoboRIOClient.cpp' 
    ],
    dependencies: [opencv, json, lws, spdlog, threads],
    include_directories: include_directories('source/include')
)

# Add test apps as subprojects
subproject('tests')

# Add test targets
test('basic', vision)

# Custom task
run_target('deploy', command: ['sh', 'scripts/deploy.sh', team_number, frc_year])
run_target('setup', command: ['sh', 'scripts/setup.sh', team_number, frc_year])
run_target('runTest', command: ['sh', 'scripts/test.sh', team_number, frc_year])


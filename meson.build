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

# System dependancies
threads = dependency('threads')
# See if this ever becomes available as a wrap
opencv = dependency('opencv4')

# Dependancies added via wrap
spdlog = subproject('spdlog')
json = subproject('nlohmann_json')
#glib = subproject('glib')

# Create the main executable to be deployed
vision = executable(
    'vision',
    [
        'src/Main.cpp', 
        'src/BallTracker.cpp', 
        'src/RoboRIOClient.cpp', 
        'src/MathUtils.cpp', 
        'src/TapeTracker.cpp'
    ],
    dependencies: [opencv, threads],
    include_directories: include_directories('src/include')
)

# Add test apps as subprojects
#subproject('tests/RoboRIOClientTester')

# Add test targets
test('basic', vision)

# Custom task
run_target('deploy', command: ['sh', 'scripts/deploy.sh', team_number, frc_year])
run_target('setup', command: ['sh', 'scripts/setup.sh', team_number, frc_year])
run_target('runTest', command: ['sh', 'scripts/test.sh', team_number, frc_year])


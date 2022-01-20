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

# Used to manually find libraries(the -l flag) 
cpp = meson.get_compiler('cpp')

# Find dependancies
opencv = dependency('opencv4')
threads = dependency('threads')
poconet = [cpp.find_library('PocoNet'), cpp.find_library('PocoFoundation')]

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
    dependencies: [opencv, poconet, threads],
    include_directories: include_directories('src/include')
)

# Add test apps as subprojects
subproject('PocoNetClientTester')

# Add test targets
test('basic', vision)

# Custom task
run_target('deploy', command: ['sh', 'scripts/deploy.sh', team_number, frc_year])
run_target('setup', command: ['sh', 'scripts/setup.sh', team_number, frc_year])
run_target('unittest', command: ['sh', 'scripts/test.sh', team_number, frc_year])


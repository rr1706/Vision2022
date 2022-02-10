# Project info
project(
    'Vision',
    'cpp',
    version: '2022.2.0',
    default_options: ['cpp_std=c++17', 'warning_level=3']
)

# Variables
team_number = '1706'
host = 'jetson'
user = 'frc'
conan_dir = meson.build_root()/'conan'
#'resources/conan/jetson_nano.jinja'
conan_profile=meson.source_root()/'resources/conan/default.jinja' 

#PKG_CONFIG_PATH=builddir/conan meson builddir/ 
run_command(
    [
        'conan', 'install', meson.source_root(), 
        '-if', conan_dir, 
        '-pr:b='+conan_profile, 
        '--build', 'missing',
        '-s', 'build_type=Release'
    ], 
    check: true
)

# Dependancies
grpc = dependency('grpc')
spdlog = dependency('spdlog')
ffmpeg = dependency('ffmpeg')
opencv = dependency('opencv')
threads = dependency('threads')

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
    dependencies: [grpc, spdlog, ffmpeg, opencv, threads],
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
run_target('run_test', 
    command: [
        'python', 
        'resources/tasks/run_test.py', 
        team_number, 
    ]
)
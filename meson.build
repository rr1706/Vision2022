project(
    'Vision2022',
    'cpp',
    version: '0.0.2',
    default_options: ['cpp_std=c++11']
)

# Used to manually find libraries(the -l flag) 
cpp = meson.get_compiler('cpp')

# Find dependancies
opencv = dependency('opencv4')
poconet = [cpp.find_library('PocoNet'), cpp.find_library('PocoFoundation')]

# Create the main executable to be deployed
program = executable(
    'vision',
    [
        'src/Main.cpp', 
        'src/BallTracker.cpp', 
        'src/DriverClient.cpp', 
        'src/MathUtils.cpp', 
        'src/TapeTracker.cpp'
    ],
    dependencies: [opencv, poconet],
    include_directories: include_directories('src/include')
)

# Add test apps as subprojects
subproject('PocoNetClientTester')

# Add test targets
test('basic', program, suite: 'jetson')

# Custom task
run_target(
    'deploy',
    command: [
        'python3',
        'scripts/deploy.py',
        '| tee -a builddir/deploy.log'
    ]
)
run_target(
    'pip',
    command: ['pip', 'install', '-r', 'requirements.txt']
)

# Running test
#meson test -C builddir --wrap=valgrind
#meson test -C builddir --gdb # Interactive

#Benchmark: 2200ms transfer
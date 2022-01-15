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
        '${MESON_SOURCE_ROOT}/scripts/deploy.py',
        '| tee -a ${MESON_BUILD_ROOT}/meson-logs/deploy.log'
    ]
)
run_target( # Conan is used to cross compile deps for a co-processer
    'conan (release)',
    command: [
        'conan',
        'install .',
        '-if buildir/conan',
        '-pr:b=default',
        '-pr:h=${MESON_SOURCE_ROOT}/resources/conan/jetson-nano',
        '-s build_type=Release',
        '| tee -a ${MESON_BUILD_ROOT}/meson-logs/conan.log'
    ]
)
run_target(
    'pip',
    command: ['pip', 'install', '-r', '${MESON_SOURCE_ROOT}/requirements.txt']
)

# Running test
#meson test -C builddir --wrap=valgrind
#meson test -C builddir --gdb # Interactive

#Benchmark: 2200ms transfer
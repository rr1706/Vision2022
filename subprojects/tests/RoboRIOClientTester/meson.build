project(
    'RoboRIOClientTester',
    'cpp',
    default_options: ['cpp_std=c++11']
)

opencv = dependency('opencv4')

program = executable(
    'RoboRIOClientTester',
    ['Server.cpp'],
    dependencies: [opencv]
)

test('basic', program, suite: 'network')
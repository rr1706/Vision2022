opencv = dependency('opencv4')
json = subproject('nlohmann_json').get_variable('nlohmann_json_dep')

program = executable(
    'RoboRIOClientTester',
    ['Server.cpp'],
    dependencies: [opencv, json]
)

test('basic', program, suite: 'network')
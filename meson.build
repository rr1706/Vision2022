project(
    'Vision2022',
    'cpp'
)

opencv = dependency('opencv4')
# Can't find a way to include poco or plain asio using cmake/pkg-config
poconet = dependency('Poco', method: 'cmake', modules: ['Poco::Net'])

program = executable(
    'vision',
    ['src/Main.cpp'],
    dependencies: opencv
)

test('basic', program)
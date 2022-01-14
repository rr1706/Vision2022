project(
    'Vision2022',
    'cpp',
    version: '0.0.2',
    default_options: ['cpp_std=c++11']
)

cpp = meson.get_compiler('cpp')

opencv = dependency('opencv4')
#poco = dependency('Poco', method: 'cmake', modules: ['Poco::Net', 'Poco::Foundation'])
poco = cpp.find_library('PocoNet')

program = executable(
    'vision',
    ['src/Main.cpp'],
    dependencies: [opencv, poco]
)

test('basic', program)

#/usr/share/cmake_modules/cmake/Modules/FindPoco.cmake
#export CMAKE_MODULE_PATH="$CMAKE_MODULE_PATH:/usr/share/cmake_modules/cmake/Modules/FindPoco.cmake
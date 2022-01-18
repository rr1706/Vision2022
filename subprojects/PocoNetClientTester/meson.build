project(
    'PocoNetClientTester',
    'cpp',
    default_options: ['cpp_std=c++17']
)

cpp = meson.get_compiler('cpp')

poconet = [cpp.find_library('PocoNet'), cpp.find_library('PocoFoundation')]
# Currently a bug in meson exists that doesn't allow for using cmake module
#poconet = dependency('Poco', method: 'cmake', modules: ['Poco::Net', 'Poco::Foundation'])

program = executable(
    'PoconetClientTester',
    ['Server.cpp'],
    dependencies: [poconet]
)
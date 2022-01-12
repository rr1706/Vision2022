project(
    'Vision2022',
    'cpp'
)

opencv = dependency('opencv4')
poconet_linker_flags = '-lPocoNet -lPocoFoundation' # TODO: consider asio

program = executable(
    'vision',
    ['src/Main.cpp'],
    dependencies: opencv,
    link_args: poconet_linker_flags
)

test('basic', program)

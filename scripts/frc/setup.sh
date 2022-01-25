#!/bin/sh

conan',
        'install', '.',
        '-if', 'builddir/conan',
        '-pr:b=default',
        '-pr:h=resources/conan/jetson-nano',
        '-s', 'build_type=Release'
    ]
)
run_target(
    'pip',
    command: ['pip', 'install', 'opencv-python paramiko meson conan scp']
)

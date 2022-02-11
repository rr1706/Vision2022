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

import paramiko
from scp import SCPClient

# Create a release build

ssh = paramiko.SSHClient()
ssh.load_system_host_keys()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect(hostname="192.17.06.1", username="frc")

scp = SCPClient(ssh.get_transport())

ssh.exec_command("mkdir ~/frc/")

#scp.put("resources/deploy/", "~/frc/", recursive=True)
#scp.put("builddir/vision", "~/frc", recursive=True)

scp.close()
ssh.close()
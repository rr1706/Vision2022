#!/bin/python3

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
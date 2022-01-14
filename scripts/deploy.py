#!/bin/python3

import paramiko
from scp import SCPClient

ssh = paramiko.SSHClient()
ssh.load_system_host_keys()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect(hostname="jetson", username="frc")

scp = SCPClient(ssh.get_transport())

ssh.exec_command("mkdir ~/frc/")

#scp.put("scripts/install.sh", "~/frc/", recursive=True)
#scp.put("resources/deploy/", "~/frc/", recursive=True)
#scp.put("builddir/vision", "~/frc", recursive=True)

scp.close()
ssh.close()
#!/bin/sh

export JETSON_NANO_REVISION=200 # 300 = B01, 200 = A02
export JETSON_NANO_BOARD=jetson-nano
export JETSON_ROOTFS_DIR=/path/to/rootfs
export JETSON_BUILD_DIR=/path/to/build_dir
export TEAM_NUMBER=1706

# sudo access without password
cp /etc/sudoers /etc/sudoers.old
echo "frc ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# why does it ship with docker?
apt update && apt upgrade

# Disable desktop
systemctl set-default multi-user.target 
# Enable desktop
# systemctl set-default graphical.target

# Static ip
sed 's/#CONFIGURE_INTERFACES=yes/CONFIGURE_INTERFACES=no/g' /etc/default/networking > /etc/default/networking
cat <<EOF >> /etc/network/interfaces
auto eth0
iface eth0 inet static
  address 192.${TEAM_NUMBER:0:2}.${TEAM_NUMBER:3:4}.80
  netmask 255.255.255.0
  gateway 192.${TEAM_NUMBER:0:2}.${TEAM_NUMBER:3:4}.1
EOF

# Enable autologin for frc user and delete the password
sed 's/ExecStart=-/sbin/agetty --autologin frc --noclear tty1' /etc/systemd/systems/getty-wants.target/getty@tty1.service > /etc/systemd/systems/getty-wants.target/getty@tty1.service 
systemctl enable getty@tty1.service
passwd -d frc

# Add jetson_clocks service
# or this https://github.com/team401/2018-Robot-Code/blob/master/vision/scripts/overclock.sh
cat << EOF > /etc/systemd/user/default.target.wants/overclock.service
[Unit]
Description=Enable jetson_clocks

[Service]
Type=simple
User=frc
Group=admin
ExecStart=/bin/jetson_clocks --fan
TimeoutStartSec=0
RemainAfterExit=yes

[Install]
WantedBy=default.target
EOF
systemctl enable overclock.service

echo "Finish setup"

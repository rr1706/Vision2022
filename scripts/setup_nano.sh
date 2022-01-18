#!/bin/sh

# sudo access without password
cp /etc/sudoers /etc/sudoers.old
echo "frc ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# why does it ship with docker?
apt remove docker
apt update && apt upgrade
sudo apt install libopencv-dev libpoco-dev

# Enable fan
jetson_clocks --fan

# Disable desktop
systemctl set-default multi-user.target 
# sudo systemctl set-default graphical.target # to enable again

# Static ip
sed 's/#CONFIGURE_INTERFACES=yes/CONFIGURE_INTERFACES=no/g' /etc/default/networking > /etc/default/networking

cat <<EOF >> /etc/network/interfaces
auto eth0
iface eth0 inet static
  address 192.17.06.80
  netmask 255.255.255.0
  gateway 192.17.06.1
EOF

# Enable autologin for frc user and delete the password
# TODO: Verify this works
sed 's/ExecStart=-/sbin/agetty --autologin frc --noclear tty1' /etc/systemd/systems/getty-wants.target/getty@tty1.service > /etc/systemd/systems/getty-wants.target/getty@tty1.service 
systemctl enable getty@tty1.service
passwd -d frc

# Auto load jetson_clocks config
# FIXME: Make this into a service file
#echo "sudo jetson_clocks -- ~/frc/clocks.conf & disown" >> /home/frc/.bashrc

echo "Finish setup"
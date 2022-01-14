#!/bin/sh

# sudo access without password
cp /etc/sudoers /etc/sudoers.old
echo "frc ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# why does it ship with docker?
apt remove docker

# Enable fan
jetson_clock

# Disable desktop
systemctl set-default multi-user.target 
# sudo systemctl set-default graphical.target # to enable again

# Static ip
sed 's/#CONFIGURE_INTERFACES=yes/CONFIGURE_INTERFACES=no/g' /etc/default/networking

cat <<EOF >> /etc/network/interfaces
auto eth0
iface eth0 inet static
  address 192.17.06.80
  netmask 255.255.255.0
  gateway 192.17.06.1
EOF

echo "Finish setup"
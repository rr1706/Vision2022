#!/bin/sh

sudo cp ~/frc/vision.service /etc/systemd/system/
sudo systemctl enable vision.service
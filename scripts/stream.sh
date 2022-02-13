#!/bin/bash
#sudo apt install nginx

FPS="30"
QUAL="medium"
SOURCE="/dev/video0"
DEST="rtp://127.0.0.1:8000"

ffmpeg -re \
    -i "$SOURCE" \
    -an \
    -f rtp -sdp_file video.sdp "$DEST"
    #-codec:v libx264 -r $FPS -preset $QUAL -s 640x480 \


#!/usr/bin/env python

import numpy
import cv2
from glob import glob

# The number of squares on the chess board
CHESSBOARD = (8, 7)

# Images location
images = glob('../resources/img/chessboard/*.jpg')

# Termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# Prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = numpy.zeros((6*7,3), numpy.float32)
objp[:,:2] = numpy.mgrid[0:7,0:6].T.reshape(-1,2) * 30 # Millimeters!

# Arrays to store object points and image points from all the images.
threedpoints = [] # 3d point in real world space
twodpoints = [] # 2d points in image plane.

for file in images:
    img = cv2.imread(file)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #print(gray)
    # Find the chess board corners
    ret, corners = cv2.findChessboardCorners(gray, CHESSBOARD, None)
    
    # If found, add object points, image points (after refining them)
    if ret == True:
        threedpoints.append(objp)
        corners2 = cv2.cornerSubPix(gray,corners, (11,11), (-1,-1), criteria)
        twodpoints.append(corners)
        # Draw and display the corners
        cv2.drawChessboardCorners(img, (7,6), corners2, ret)
        cv2.imshow('img', img)
        cv2.waitKey(500)

cv2.destroyAllWindows()

ret, cameraMatrix, distCoeffs, rvecs, tvecs = cv2.calibrateCamera(threedpoints, twodpoints, gray.shape[::-1], None, None)

print("Camera Matrix: " + cameraMatrix)
print("Distortion Coeffs: " + distCoeffs)
print("Image Points: " + twodpoints)
print("Object Points: " + threedpoints)
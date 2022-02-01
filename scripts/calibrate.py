#!/bin/python
import os
import cv2
import numpy as np
from glob import glob

# Parameters
IMAGES_DIR = os.path.join("..", "resources", "img", "chessboard")
IMAGES_FORMAT = ".jpg"
SQUARE_SIZE = 2.9  # cm
# Count lines not boxes
WIDTH = 6
HEIGHT = 7


def calibrate_chessboard(dir_path, image_format, square_size, width, height):
    """Calibrate a camera using chessboard images."""
    images = glob(f"{dir_path}/*.{image_format}")

    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

    objp = np.zeros((height * width, 3), np.float32)
    objp[:, :2] = np.mgrid[0:width, 0:height].T.reshape(-1, 2)
    objp = objp * square_size

    objpoints = []  # 3d point in real world space
    imgpoints = []  # 2d points in image plane.

    # Iterate through all images
    for file in images:
        img = cv2.imread(str(file))
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # Find the chess board corners
        ret, corners = cv2.findChessboardCorners(gray, (width, height), None)

        # If found, add object points, image points (after refining them)
        if ret:
            objpoints.append(objp)

            corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
            imgpoints.append(corners2)

    # Calibrate camera
    ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(
        objpoints, imgpoints, gray.shape[::-1], None, None
    )

    return [ret, mtx, dist, rvecs, tvecs]


def save_coefficients(mtx, dist, path):
    """Save the camera matrix and the distortion coefficients to given path/file."""
    cv_file = cv2.FileStorage(path, cv2.FILE_STORAGE_WRITE)
    cv_file.write("K", mtx)
    cv_file.write("D", dist)
    # note you *release* you don't close() a FileStorage object
    cv_file.release()


# Calibrate
ret, mtx, dist, rvecs, tvecs = calibrate_chessboard(
    IMAGES_DIR, IMAGES_FORMAT, SQUARE_SIZE, WIDTH, HEIGHT
)

# Save coefficients into a file
save_coefficients(mtx, dist, "../resources/deploy/calibration.yml")

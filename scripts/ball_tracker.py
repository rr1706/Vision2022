#!/bin/python
import sys
import cv2 as cv

cap = cv.VideoCapture(0)
win_name = "Ball Calibration"

if not cap.isOpened():
    print("unable to open camera")
    sys.exit(-1)

cv.namedWindow(win_name)


def onTrackBarUpdate(x):
    pass


cv.createTrackbar("Red Min", win_name, 0, 255, onTrackBarUpdate)
cv.createTrackbar("Green Min", win_name, 0, 255, onTrackBarUpdate)
cv.createTrackbar("Blue Min", win_name, 0, 255, onTrackBarUpdate)

cv.createTrackbar("Red Max", win_name, 0, 255, onTrackBarUpdate)
cv.createTrackbar("Green Max", win_name, 0, 255, onTrackBarUpdate)
cv.createTrackbar("Blue Max", win_name, 0, 255, onTrackBarUpdate)

while cap.isOpened():
    ret_code, base_frame = cap.read()
    trackbars = {
        "r_min": cv.getTrackbarPos("Red Min", win_name),
        "g_min": cv.getTrackbarPos("Green Min", win_name),
        "b_min": cv.getTrackbarPos("Blue Min", win_name),
        "r_max": cv.getTrackbarPos("Red Max", win_name),
        "g_max": cv.getTrackbarPos("Green Max", win_name),
        "b_max": cv.getTrackbarPos("Blue Max", win_name),
    }

    if ret_code:
        hsv = cv.cvtColor(base_frame, cv.COLOR_BGR2HSV)
        threshed = cv.inRange(
            hsv,
            (trackbars["b_min"], trackbars["g_min"], trackbars["r_min"]),
            (trackbars["b_max"], trackbars["g_max"], trackbars["r_max"]),
        )

        # status, stitched = cv.Stitcher_create().stitch([hsv, threshed])

        try:
            cv.imshow(win_name, hsv)
            cv.imshow(win_name, threshed)
        except Exception as err:
            print("[ERROR] failed to stitch images")
            print("[ERROR] {}".format(err))
            break

    # Press Q on keyboard to  exit
    if cv.waitKey(27) & 0xFF == ord("q"):
        break

cap.release()
cv.destroyAllWindows()

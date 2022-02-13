from cv2 import VideoCapture, imshow

capture = VideoCapture(0)

while capture.isOpened():
    ret, frame = capture.read()
    if ret:
        imshow("window", frame)
    else:
        print("Unable to read from camera")

print("Exiting")

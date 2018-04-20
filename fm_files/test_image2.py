# import the necessary packages
from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2

# initialise the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))

# allow the camera to warm up
time.sleep(0.1)

#grab an image from the camera
#camera.capture(rawCapture, format="bgr")
#image = rawCapture.array

#display the image on screen and wait for a keypress
#cv2.imshow("Image", image)
#cv2.waitKey(0)

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):

	image = frame.array
	cv2.line(image, (320,200),(320,280),(0,255,0),10)
	cv2.line(image, (280,240), (360,240), (0,255,0),10)
	cv2.imshow("Frame", image)
	key = cv2.waitKey(1) & 0xFF

	rawCapture.truncate(0)

	if key == ord("q"):
		break



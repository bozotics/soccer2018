import time
import picamera
import picamera.array
import cv2

with picamera.PiCamera() as camera:
	camera.sensor_mode=2
	camera.resolution = (3280, 2464)
	camera.start_preview()
	time.delay(2)
	camera.stop_preview()
	with picamera.array.PiRGBArray(camera) as stream:
		camera.capture(stream, format='bgr')
		image = stream.array
		(x,y,w,h) = cv2.selectROI(image)
		cropped = image[y:y+h, x:x+w]
		hsv = cv2.cvtColor(cropped, cv2.COLOR_BGR2HSV)
		print (cropped)
		print (hsv)
	#camera.stop_preview()

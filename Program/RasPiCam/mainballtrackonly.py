from __future__ import print_function
from picamera.array import PiRGBArray
from picamera import PiCamera
from threading import Thread
#from imutils.video import FPS
import cv2
import numpy as np
import imutils
import time
import math
import serial

ser = serial.Serial(
    port='/dev/serial0',
    baudrate = 230400,
)
x=800
y=608
class PiVideoStream:
	def __init__(self):
		# initialize the camera and stream
		self.camera = PiCamera(sensor_mode=4)
		self.camera.resolution = (x, y)
		self.camera.shutter_speed = 26700
		# self.camera.framerate = 60
		self.rawCapture = PiRGBArray(self.camera)
		self.stream = self.camera.capture_continuous(self.rawCapture,
			format="bgr", use_video_port=True)

		# initialize the frame and the variable used to indicate
		# if the thread should be stopped
		self.frame = None
		self.stopped = False

	def adjustExp(self, speed):
		self.camera.shutter_speed = speed

	def start(self):
		# start the thread to read frames from the video stream
		Thread(target=self.update, args=()).start()
		return self

	def update(self):
		# keep looping infinitely until the thread is stopped
		for f in self.stream:
			# grab the frame from the stream and clear the stream in
			# preparation for the next frame
			self.frame = f.array
			self.rawCapture.truncate(0)

			# if the thread indicator variable is set, stop the thread
			# and resource camera resources
			if self.stopped:
				self.stream.close()
				self.rawCapture.close()
				self.camera.close()
				return
	def read(self):
		# return the frame most recently read
		return self.frame

	def stop(self):
		# indicate that the thread should be stopped
		self.stopped = True

orangeLowL = 140
orangeHighL = 255
orangeLowA = 145
orangeHighA = 190
orangeLowB = 130
orangeHighB = 255

orangeLower =  np.array([orangeLowL, orangeLowA, orangeLowB])
orangeUpper =  np.array([orangeHighL, orangeHighA, orangeHighB])

robotMask = np.full((y,x), 255, dtype=np.uint8)
robotMask=cv2.circle(robotMask,(400,304),120,(0),-1)

bgr = np.empty((y * x * 3,), dtype=np.uint8)

vs = PiVideoStream().start()
def nothing(x):
    pass
timeout = time.time() + 0.5
while True:
	bgr = vs.read()
	if time.time() > timeout:
		break

while True:
	bgr = vs.read()
	Lab = cv2.cvtColor(bgr, cv2.COLOR_BGR2Lab)
	mask = cv2.inRange(Lab, orangeLower, orangeUpper)
	mask = cv2.dilate(mask, None, iterations=1)
	mask = cv2.erode(mask, None, iterations=1)
	cnts = cv2.findContours(maskYellow.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
	if len(cnts) > 0:
		c = max(cnts, key=cv2.contourArea)
		((x, y), radius) = cv2.minEnclosingCircle(c)
		x1 = x - 400
		y1 = y - 304
		if x1 == 0:
			x1 = 0.01
		polarDist = math.sqrt(abs(x1)+abs(y1))
		polarAngle = math.atan(y1/x1)
		polarAngle = polarAngle*180/3.14159265
		#if (x1<0):
		#	polarAngle = - (90 + polarAngle)
		#else:
		#	polarAngle = 90 - polarAngle
		if (x1<0):
			if polarAngle == 0:
				polarAngle = 0.001
			polarAngle = (polarAngle/abs(polarAngle))*(180-abs(polarAngle))
		else:
			polarAngle = -polarAngle
		send = str(polarAngle) + ((119-len(str(polarAngle)))*"a") + ("b")
		ser.write(bytes(str(send), 'utf-8'))
		#print(str(float(polarDist))+"   "+str(float(polarAngle))+"   "+str(float(radius)))
	else:
		ser.write(bytes(((119*"r")+("b")), 'utf-8'))

cv2.destroyAllWindows()
vs.stop()


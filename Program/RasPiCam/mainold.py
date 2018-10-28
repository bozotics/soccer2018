from __future__ import print_function
from picamera.array import PiRGBArray
from picamera import PiCamera
from threading import Thread
from decimal import Decimal
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
	write_timeout=0,
	timeout=0
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



blueLowL = 5
blueHighL = 55
blueLowA = 110
blueHighA = 150
blueLowB = 100
blueHighB = 120

blueLower =  np.array([blueLowL, blueLowA, blueLowB])
blueUpper =  np.array([blueHighL, blueHighA, blueHighB])



yellowLowL = 75
yellowHighL = 135
yellowLowA = 105
yellowHighA = 135
yellowLowB = 155
yellowHighB = 180

yellowLower =  np.array([yellowLowL, yellowLowA, yellowLowB])
yellowUpper =  np.array([yellowHighL, yellowHighA, yellowHighB])



orangeCloseLowL = 140
orangeCloseHighL = 255
orangeCloseLowA = 145
orangeCloseHighA = 190
orangeCloseLowB = 130
orangeCloseHighB = 255

orangeCloseLower =  np.array([orangeCloseLowL, orangeCloseLowA, orangeCloseLowB])
orangeCloseUpper =  np.array([orangeCloseHighL, orangeCloseHighA, orangeCloseHighB])



robotMask = np.full((y,x), 255, dtype=np.uint8)
robotMask = cv2.circle(robotMask, (x/2, y/2), 130, 0, -1)
closeOrangeMask = np.full((y,x), 0, dtype=np.uint8)
closeOrangeMask = cv2.circle(closeOrangeMask, (x/2, y/2), 170, 255, -1)

frame = np.empty((y * x * 3,), dtype=np.uint8)

vs = PiVideoStream().start()
def nothing(x):
    pass
timeout = time.time() + 0.5
while True:
	frame = vs.read()
	if time.time() > timeout:
		break
#cv2.startWindowThread()
#cv2.namedWindow("Frame")
cv2.namedWindow("adjust")
#fps = FPS().start()
cv2.createTrackbar('exp','Frame',0,25000,nothing)
cv2.createTrackbar('L-lo','adjust',blueLowL,255,nothing)
cv2.createTrackbar('L-hi','adjust',blueHighL,255,nothing)
cv2.createTrackbar('A-lo','adjust',blueLowA,255,nothing)
cv2.createTrackbar('A-hi','adjust',blueHighA,255,nothing)
cv2.createTrackbar('B-lo','adjust',blueLowB,255,nothing)
cv2.createTrackbar('B-hi','adjust',blueHighB,255,nothing)

#while fps._numFrames < 500:
while True:
	#vs.adjustExp((cv2.getTrackbarPos('exp','Frame')+10000))
	frame = vs.read()
	#eLn: euler number, Ln function, Musk=mask hur dur dur
	Lab = cv2.cvtColor(frame, cv2.COLOR_BGR2Lab)
	maskOrange = cv2.inRange(Lab, orangeLower, orangeUpper)
	maskOrange = cv2.bitwise_and(maskOrange, robotMask)
	maskOrangeClose = cv2.inRange(Lab, orangeCloseLower, orangeCloseUpper)
	maskOrangeClose = cv2.bitwise_and(maskOrangeClose, closeOrangeMask)
	maskOrangeAll = cv2.bitwise_or(maskOrange, maskOrangeClose)
	#blueLowL = cv2.getTrackbarPos('L-lo','adjust')
	#blueHighL = cv2.getTrackbarPos('L-hi','adjust')
	#blueLowA = cv2.getTrackbarPos('A-lo','adjust')
	#blueHighA = cv2.getTrackbarPos('A-hi','adjust')
	#blueLowB = cv2.getTrackbarPos('B-lo','adjust')
	#blueHighB = cv2.getTrackbarPos('B-hi','adjust')
	#blueLower =  np.array([blueLowL, blueLowA, blueLowB])
	#blueUpper =  np.array([blueHighL, blueHighA, blueHighB])
	maskYellow = cv2.inRange(Lab, yellowLower, yellowUpper)
	maskYellow = cv2.bitwise_and(maskYellow, robotMask)
	maskBlue = cv2.inRange(Lab, blueLower, blueUpper)
	maskBlue = cv2.bitwise_and(maskBlue, robotMask)
	#mask = cv2.erode(mask, None, iterations=1)
	#mask = cv2.dilate(mask, None, iterations=1)
	cntsYellow = cv2.findContours(maskYellow.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
	cntsBlue = cv2.findContours(maskBlue.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
	cntsOrange = cv2.findContours(maskOrangeAll.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
	cv2.drawContours(frame, cntsYellow, -1, (0, 255, 255), 3)
	cv2.drawContours(frame, cntsBlue, -1, (255, 0, 255), 3)
	cv2.drawContours(frame, cntsOrange, -1, (255, 255, 0), 3)
	extLeftYellow = tuple(cntsYellow[cntsYellow[:, :, 0].argmin()][0])
	extRightYellow = tuple(cntsYellow[cntsYellow[:, :, 0].argmax()][0])
	extTopYellow = tuple(cntsYellow[cntsYellow[:, :, 1].argmin()][0])
	extBotYellow = tuple(cntsYellow[cntsYellow[:, :, 1].argmax()][0])
	extLeftBlue = tuple(cntsBlue[cntsBlue[:, :, 0].argmin()][0])
	extRightBlue = tuple(cntsBlue[cntsBlue[:, :, 0].argmax()][0])
	extTopBlue = tuple(cntsBlue[cntsBlue[:, :, 1].argmin()][0])
	extBotBlue = tuple(cntsBlue[cntsBlue[:, :, 1].argmax()][0])
	if len(cnts) > 0:					#not cnts anymore
		c = max(cnts, key=cv2.contourArea)
		((xBall, yBall), radius) = cv2.minEnclosingCircle(c)
		x1 = xBall - x/2
		y1 = yBall - y/2
		if x1 == 0:
			x1 = 0.01
		polarDist = math.sqrt(abs(x1)+abs(y1))
		floatAngle = math.atan(y1/x1)*180/3.14159265
		polarAngle = round(Decimal(floatAngle),2)
		if (x1<0):
			if polarAngle == 0:
				polarAngle = 0.01
			polarAngle = (polarAngle/abs(polarAngle))*(180-abs(polarAngle))
		else:
			polarAngle = -polarAngle
		xYellow = extTopYellow[0] - x/2
		yYellow = extTopYellow[1] - y/2
		distYellow = math.sqrt(abs(xYellow)+abs(yYellow))
		angleFloatYellow = math.atan(yYellow/xYellow)*180/3.14159265
		angleYellow = round(Decimal(angleFloatYellow),2)
		xBlue = extTopBlue[0] - x/2
		yBlue = extTopBlue[1] - y/2
		distBlue = math.sqrt(abs(xBlue)+abs(yBlue))
		angleFloatBlue = math.atan(yBlue/xBlue)*180/3.14159265
		angleBlue = round(Decimal(angleFloatBlue),2)
		#send = str(polarAngle) + ((119-len(str(polarAngle)))*"a") + ("b")		#old one
		send = str(polarAngle) + ("a") + str(angleYellow) + ("b") + str(angleBlue) 
		#ser.write(bytes(str(send), 'utf-8'))
		#print(str(float(polarDist))+"   "+str(float(polarAngle))+"   "+str(float(radius)))
	#else:
		#print("rip")
		#ser.write(bytes(((119*"r")+("b")), 'utf-8'))
	cv2.imshow("Frame", frame)
	#cv2.imshow("actual", frame)
	#fps.update()
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break


#fps.stop()
#print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
#print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))

cv2.destroyAllWindows()
vs.stop()


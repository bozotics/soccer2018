from __future__ import print_function
from picamera.array import PiRGBArray
from picamera import PiCamera
from threading import Thread
#from imutils.video import FPS
import cv2
import numpy as np
import imutils
import time
from math import sqrt
import serial

ser = serial.Serial(
    port='/dev/serial0',
    baudrate = 230400,
	write_timeout=0,
	timeout=0
)
x=608
y=464
class PiVideoStream:
	def __init__(self):
		# initialize the camera and stream
		self.camera = PiCamera(sensor_mode=4)
		self.camera.resolution = (x, y)
		self.camera.shutter_speed = 16200
		self.camera.framerate = 40
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


global blueGoalMask
global ballx
global bally
global yellowTopx
global yellowTopy
global yellowBottomx
global yellowBottomy
global blueTopx
global blueTopy
global blueBottomx
global blueBottomy

ballx = 0
bally = 0
yellowTopx = 0
yellowTopy = 0
yellowBottomx = 0
yellowBottomy = 0
blueTopx = 0
blueTopy = 0
blueBottomx = 0
blueBottomy = 0

#super old values
#blueLowB = 130
#blueHighB = 255
#blueLowG = 0
#blueHighG = 125
#blueLowR = 0
#blueHighR = 75

#sci center practice field
#orangeLowL = 90
#orangeHighL = 140
#orangeLowA = 160
#orangeHighA = 190
#orangeLowB = 145
#orangeHighB = 180

#striker comps field
#orangeLowL = 110
#orangeHighL = 180
#orangeLowA = 170
#orangeHighA = 210
#orangeLowB = 135
#orangeHighB = 190

#goalie comps field
orangeLowL = 90
orangeHighL = 150
orangeLowA = 170
orangeHighA = 200
orangeLowB = 145
orangeHighB = 170

#g office
#orangeLowL = 110
#orangeHighL = 180
#orangeLowA = 140
#orangeHighA = 170
#orangeLowB = 170
#orangeHighB = 200

orangeLower =  np.array([orangeLowL, orangeLowA, orangeLowB])
orangeUpper =  np.array([orangeHighL, orangeHighA, orangeHighB])

#sci center practice field
#blueLowB = 0
#blueHighB = 60
#blueLowG = 0
#blueHighG = 255
#blueLowR = 0
#blueHighR = 125

#striker comps field
#blueLowB = 0
#blueHighB = 50
#blueLowG = 110
#blueHighG = 145
#blueLowR = 100
#blueHighR = 125

#goalie comps field
blueLowB = 0
blueHighB = 20
blueLowG = 100
blueHighG = 135
blueLowR = 110
blueHighR = 125

#g office
#blueLowB = 30
#blueHighB = 75
#blueLowG = 95
#blueHighG = 120
#blueLowR = 120
#blueHighR = 140

blueLower =  np.array([blueLowB, blueLowG, blueLowR])
blueUpper =  np.array([blueHighB, blueHighG, blueHighR])

#sci center practice field
#yellowLowL = 175
#yellowHighL = 220
#yellowLowA = 115
#yellowHighA = 140
#yellowLowB = 180
#yellowHighB = 220

#striker comps field
#yellowLowL = 145
#yellowHighL = 200
#yellowLowA = 115
#yellowHighA = 160
#yellowLowB = 170
#yellowHighB = 220

#goalie comps field
yellowLowL = 145
yellowHighL = 190
yellowLowA = 115
yellowHighA = 160
yellowLowB = 180
yellowHighB = 220

#g office
#yellowLowL = 110
#yellowHighL = 180
#yellowLowA = 115
#yellowHighA = 140
#yellowLowB = 180
#yellowHighB = 220

yellowLower =  np.array([yellowLowL, yellowLowA, yellowLowB])
yellowUpper =  np.array([yellowHighL, yellowHighA, yellowHighB])


robotMask = np.full((y,x), 0, dtype=np.uint8)
robotMask = cv2.circle(robotMask,(300,228),280,255,-1)
robotMask=cv2.circle(robotMask,(300,228),130,(0),-1)

blueGoalMaskBlue = np.full((y,x), 0, dtype=np.uint8)
blueGoalMask1 = np.full((y,x), 0, dtype=np.uint8)
blueGoalMask1 = cv2.circle(blueGoalMask1,(300,228),280,255,-1)
pts = np.array([[x,y],[x,0],[337,152],[337,304]], np.int32).reshape((-1,1,2))
cv2.fillPoly(blueGoalMaskBlue,[pts],255)
blueGoalMaskBlue = cv2.bitwise_and(blueGoalMaskBlue, blueGoalMask1)
blueGoalMaskBlue = cv2.circle(blueGoalMaskBlue,(300,228),130,(0),-1)
#cv2.imshow("mask",blueGoalMask)

blueGoalMaskYellow = np.full((y,x), 0, dtype=np.uint8)
blueGoalMask1 = np.full((y,x), 0, dtype=np.uint8)
blueGoalMask1 = cv2.circle(blueGoalMask1,(300,228),280,255,-1)
pts = np.array([[0,y],[0,0],[263,152],[263,304]], np.int32).reshape((-1,1,2))
cv2.fillPoly(blueGoalMaskYellow,[pts],255)
blueGoalMaskYellow = cv2.bitwise_and(blueGoalMaskYellow, blueGoalMask1)
blueGoalMaskYellow = cv2.circle(blueGoalMaskYellow,(300,228),130,(0),-1)

blueGoalMask = blueGoalMaskBlue

vs = PiVideoStream().start()
def nothing(x):
    pass
timeout = time.time() + 0.5
while True:
	bgr = vs.read()
	if time.time() > timeout:
		break
#cv2.startWindowThread()
#cv2.namedWindow("Frame")
#cv2.namedWindow("bgm")
#cv2.namedWindow("adjustblue")
#cv2.namedWindow("adjustorange")
#cv2.namedWindow("adjustyellow")
#fps = FPS().start()

#cv2.createTrackbar('exp','Frame',0,25000,nothing)

#cv2.createTrackbar('B-lo','adjustblue',blueLowB ,255,nothing)
#cv2.createTrackbar('B-hi','adjustblue',blueHighB,255,nothing)
#cv2.createTrackbar('G-lo','adjustblue',blueLowG ,255,nothing)
#cv2.createTrackbar('G-hi','adjustblue',blueHighG,255,nothing)
#cv2.createTrackbar('R-lo','adjustblue',blueLowR ,255,nothing)
#cv2.createTrackbar('R-hi','adjustblue',blueHighR,255,nothing)
#
#cv2.createTrackbar('B-lo','adjustyellow',yellowLowL ,255,nothing)
#cv2.createTrackbar('B-hi','adjustyellow',yellowHighL,255,nothing)
#cv2.createTrackbar('G-lo','adjustyellow',yellowLowA ,255,nothing)
#cv2.createTrackbar('G-hi','adjustyellow',yellowHighA,255,nothing)
#cv2.createTrackbar('R-lo','adjustyellow',yellowLowB ,255,nothing)
#cv2.createTrackbar('R-hi','adjustyellow',yellowHighB,255,nothing)
#
#cv2.createTrackbar('B-lo','adjustorange',orangeLowL ,255,nothing)
#cv2.createTrackbar('B-hi','adjustorange',orangeHighL,255,nothing)
#cv2.createTrackbar('G-lo','adjustorange',orangeLowA ,255,nothing)
#cv2.createTrackbar('G-hi','adjustorange',orangeHighA,255,nothing)
#cv2.createTrackbar('R-lo','adjustorange',orangeLowB ,255,nothing)
#cv2.createTrackbar('R-hi','adjustorange',orangeHighB,255,nothing)

start = 1
dist = 0 
xTop = 0
xBottom = 0
yTop = 0
yBottom = 0

#while fps._numFrames < 500:

def goalBigDetect(cnts):
	global xTop
	global xBottom
	global yTop
	global yBottom
	global extTop
	global extBot
	global start
	global dist
	extTop1 = tuple(cnts[cnts[:, :, 1].argmin()][0])
	extBot1 = tuple(cnts[cnts[:, :, 1].argmax()][0])
	xTop1 = extTop1[0]
	xBottom1 = extBot1[0]
	x1 = xTop1 - xBottom1
	yTop1 = extTop1[1]
	yBottom1 = extBot1[1]
	y1 = yTop1 - yBottom1
	dist1 = sqrt(pow(x1,2)+pow(y1,2))
	if dist1>dist:	
		xTop = xTop1
		xBottom = xBottom1
		yTop = yTop1
		yBottom = yBottom1
		extTop = extTop1
		extBot = extBot1
	return dist1

while True:
	if (start == 1):
		start = 2
		print("started")
	#vs.adjustExp((cv2.getTrackbarPos('exp','Frame')+10000))
	bgr = vs.read()
	#eLn: euler number, Ln function, Musk=mask hur dur dur
	Lab = cv2.cvtColor(bgr, cv2.COLOR_BGR2Lab)

	#blueLowB = cv2.getTrackbarPos('B-lo','adjustblue')
	#blueHighB = cv2.getTrackbarPos('B-hi','adjustblue')
	#blueLowG = cv2.getTrackbarPos('G-lo','adjustblue')
	#blueHighG = cv2.getTrackbarPos('G-hi','adjustblue')
	#blueLowR = cv2.getTrackbarPos('R-lo','adjustblue')
	#blueHighR = cv2.getTrackbarPos('R-hi','adjustblue')
	#blueLower =  np.array([blueLowB, blueLowG, blueLowR])
	#blueUpper =  np.array([blueHighB, blueHighG, blueHighR])
#
	#orangeLowL = cv2.getTrackbarPos('B-lo','adjustorange')
	#orangeHighL = cv2.getTrackbarPos('B-hi','adjustorange')
	#orangeLowA = cv2.getTrackbarPos('G-lo','adjustorange')
	#orangeHighA = cv2.getTrackbarPos('G-hi','adjustorange')
	#orangeLowB = cv2.getTrackbarPos('R-lo','adjustorange')
	#orangeHighB = cv2.getTrackbarPos('R-hi','adjustorange')
	#orangeLower =  np.array([orangeLowL, orangeLowA, orangeLowB])
	#orangeUpper =  np.array([orangeHighL, orangeHighA, orangeHighB])
#
	#yellowLowL = cv2.getTrackbarPos('B-lo','adjustyellow')
	#yellowHighL = cv2.getTrackbarPos('B-hi','adjustyellow')
	#yellowLowA = cv2.getTrackbarPos('G-lo','adjustyellow')
	#yellowHighA = cv2.getTrackbarPos('G-hi','adjustyellow')
	#yellowLowB = cv2.getTrackbarPos('R-lo','adjustyellow')
	#yellowHighB = cv2.getTrackbarPos('R-hi','adjustyellow')
	#yellowLower =  np.array([yellowLowL, yellowLowA, yellowLowB])
	#yellowUpper =  np.array([yellowHighL, yellowHighA, yellowHighB])


	maskOrangeOuter = cv2.inRange(Lab, orangeLower, orangeUpper)
	cntsOrangeOuter = cv2.findContours(maskOrangeOuter.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
	#cv2.drawContours(bgr, cntsOrangeOuter, -1, (255, 255, 0), 3)
	if len(cntsOrangeOuter) > 0:
		cntsOrangeOuter = max(cntsOrangeOuter, key=cv2.contourArea)
		((ballx, bally), ballradius) = cv2.minEnclosingCircle(cntsOrangeOuter)
	else:
		ballx = 0
		bally = 0
		ballradius = 0

	
	maskYellow = cv2.inRange(Lab, yellowLower, yellowUpper)
	maskYellow = cv2.bitwise_and(maskYellow, robotMask)
	maskYellow = cv2.erode(maskYellow, None, iterations=3)
	maskYellow = cv2.dilate(maskYellow, None, iterations=11)
	maskYellow = cv2.erode(maskYellow, None, iterations=8)
	cntsYellow = cv2.findContours(maskYellow.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
	#cv2.drawContours(bgr, cntsYellow, -1, (0, 255, 255), 3)
	#cv2.line(bgr, (0,300), (x,300),(0,255,0),3)
	if len(cntsYellow) > 0:
		cntsYellow = max(cntsYellow, key=goalBigDetect)
		#cv2.circle(bgr, extTop, 8, (255, 0, 0), -1)
		#cv2.circle(bgr, extBot, 8, (255, 255, 0), -1)
		yellowTopx = xTop
		yellowTopy = yTop
		#cv2.line(bgr, (0,yellowTopy), (x,yellowTopy),(255,0,0),3)
		yellowBottomx = xBottom
		yellowBottomy = yBottom
		#cv2.line(bgr, (0,yellowBottomy), (x,yellowBottomy),(255,0,0),3)
	else:
		yellowTopx = 0
		yellowTopy = 0
		yellowBottomx = 0
		yellowBottomy = 0

	#if ser.in_waiting > 0:
	#	received = ser.read()
	#	time.sleep(0.5)
	#	if yellowBottomx>400:
	#		ser.write(bytes(("1b"), 'utf-8'))
	#		blueGoalMask = blueGoalMaskBlue
	#		print("blueGoalMaskBlue")
	#	else:
	#		ser.write(bytes(("2b"), 'utf-8'))
	#		blueGoalMask = blueGoalMaskYellow
	#		print("blueGoalMaskYellow")
		#cv2.imshow("bgm", blueGoalMask)

	maskBlue = cv2.inRange(Lab, blueLower, blueUpper)
	maskBlue = cv2.bitwise_and(maskBlue, blueGoalMask)
	maskBlue = cv2.erode(maskBlue, None, iterations=3)
	maskBlue = cv2.dilate(maskBlue, None, iterations=11)
	maskBlue = cv2.erode(maskBlue, None, iterations=8)
	cntsBlue = cv2.findContours(maskBlue.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
	#cv2.drawContours(bgr, cntsBlue, -1, (255, 0, 255), 3)
	if len(cntsBlue) > 0:
		cntsBlue = max(cntsBlue, key=goalBigDetect)
		#cv2.circle(bgr, extTop, 8, (255, 0, 0), -1)
		#cv2.circle(bgr, extBot, 8, (255, 255, 0), -1)
		blueTopx = xTop
		blueTopy = yTop
		blueBottomx = xBottom
		blueBottomy = yBottom
	else:
		blueTopx = 0
		blueTopy = 0
		blueBottomx = 0
		blueBottomy = 0

	#cv2.drawContours(bgr, cntsOrangeOuter, -1, (255, 255, 0), 3)
	#cv2.drawContours(bgr, cntsYellow, -1, (0, 255, 255), 3)
	#cv2.drawContours(bgr, cntsBlue, -1, (255, 0, 255), 3)
	#cv2.imshow("Frame", bgr)
	if ser.in_waiting > 0:
		received = ser.read()
		if yellowBottomx>400:
			blueGoalMask = blueGoalMaskYellow
			print("blueGoalMaskBlue")
		else:
			blueGoalMask = blueGoalMaskBlue
			print("blueGoalMaskYellow")
	send = ("a" + (3-len(str(ballx)))*"0" + str(ballx) + "a" + (3-len(str(bally)))*"0" + str(bally) 
	+ "a" + (3-len(str(yellowTopx)))*"0" + str(yellowTopx) + "a" + (3-len(str(yellowTopy)))*"0" 
	+ str(yellowTopy) + "a" + (3-len(str(yellowBottomx)))*"0" + str(yellowBottomx) + "a" 
	+ (3-len(str(yellowBottomy)))*"0" + str(yellowBottomy) + "a" + (3-len(str(blueTopx)))*"0" 
	+ str(blueTopx) + "a" + (3-len(str(blueTopy)))*"0" + str(blueTopy) + "a" 
	+ (3-len(str(blueBottomx)))*"0" + str(blueBottomx) + "a" + (3-len(str(blueBottomy)))*"0" 
	+ str(blueBottomy) + "ab")
	ser.write(bytes(str(send),'utf-8'))
#	if len(cnts) > 0:
#		c = max(cnts, key=cv2.contourArea)
#		((x, y), radius) = cv2.minEnclosingCircle(c)
#		x1 = x - 400
#		y1 = y - 304
#		if x1 == 0:
#			x1 = 0.01
#		polarDist = math.sqrt(abs(x1)+abs(y1))
#		polarAngle = math.atan(y1/x1)
#		polarAngle = polarAngle*180/3.14159265
#		#if (x1<0):
#		#	polarAngle = - (90 + polarAngle)
#		#else:
#		#	polarAngle = 90 - polarAngle
#		if (x1<0):
#			if polarAngle == 0:
#				polarAngle = 0.001
#			polarAngle = (polarAngle/abs(polarAngle))*(180-abs(polarAngle))
#		else:
#			polarAngle = -polarAngle
#		polarAngle = str(polarAngle) + ((119-len(str(polarAngle)))*"a") + ("b")
		#ser.write(bytes(str(polarAngle), 'utf-8'))
		#print(str(float(polarDist))+"   "+str(float(polarAngle))+"   "+str(float(radius)))
	#else:
		#print("rip")
		#ser.write(bytes(((119*"r")+("b")), 'utf-8'))
	#fps.update()
	#if cv2.waitKey(1) & 0xFF == ord('q'):
	#	break


#fps.stop()
#print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
#print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))

cv2.destroyAllWindows()
vs.stop()


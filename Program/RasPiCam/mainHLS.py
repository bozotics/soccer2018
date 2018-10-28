from __future__ import print_function
from picamera.array import PiRGBArray
from picamera import PiCamera
from threading import Thread
from imutils.video import FPS
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
		# self.camera.framerate = 60
		self.rawCapture = PiRGBArray(self.camera)
		self.stream = self.camera.capture_continuous(self.rawCapture,
			format="bgr", use_video_port=True)

		# initialize the frame and the variable used to indicate
		# if the thread should be stopped
		self.frame = None
		self.stopped = False

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

# LL: Lower Range Lower Bound
# LH: Lower Range Upper Bound
# HL: Higher Range Lower Bound
# HH: Higher Range Upper Bound
# ~~-H: ~~170-180 Hue value 

hueHL = 170
hueHH = 180
hueLL = 0
hueLH = 10
lightLL = 
lightLH = 
lightHL = 
lightHH = 
satLL = 
satLH = 
satHL = 
satHH = 

LL-H = np.array([hueHL, lightLL, satLL])
LH-H = np.array([hueHH, lightLH, satLH])
HL-H = np.array([hueHL, lightHL, satHL])
HH-H = np.array([hueHH, lightHH, satHH])
LL =  np.array([hueLL, lightLL, satLL])
LH =  np.array([hueLH, lightLH, satLH])
HL =  np.array([hueLL, lightHL, satHL])
HH =  np.array([hueLH, lightHH, satHH])

frame = np.empty((y * x * 3,), dtype=np.uint8)

vs = PiVideoStream().start()
frame = vs.read()
time.sleep(0.5)
cv2.startWindowThread()
cv2.namedWindow("Frame")
#cv2.namedWindow("actual")
#fps = FPS().start()

#while fps._numFrames < 100:
while True:
	frame = vs.read()
	#eLn: euler number, Ln function, Musk=mask hur dur dur
	HLS = cv2.cvtColor(frame, cv2.COLOR_BGR2HLS)
	MLH = cv2.inRange(HLS, LL-H, LH-H)
	MHH = cv2.inRange(HLS, HL-H, HH-H)
	ML = cv2.inRange(HLS, LL, LH)
	MH = cv2.inRange(HLS, HL, HH)
	cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
	cnts1 = cv2.findContours(mask1.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)[-2]
	cv2.drawContours(frame, cnts, -1, (0, 255, 255), 3)
	cv2.drawContours(frame, cnts1, -1, (0, 255, 255), 3)
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
		#	polarAngle = 270-polarAngle
		#else:
		#	polarAngle = 90-polarAngle
		if (x1<0):
			polarAngle = - (90 + polarAngle)
		else:
			polarAngle = 90 - polarAngle
		#print(str(float(polarAngle)))
		polarAngle = str(polarAngle) + ((119-len(str(polarAngle)))*"a") + ("b")
		#ser.write(bytes(str(polarAngle), 'utf-8'))
		#print(str(float(polarDist))+"   "+str(float(polarAngle))+"   "+str(float(radius)))
		#print(str(int(x))+"   "+str(int(y))+"   "+str(float(polarAngle)))
		#time.sleep(0.1)
	#else:
		#print("rip")
		#ser.write(bytes(((119*"r")+("b")), 'utf-8'))
	#mask = cv2.erode(mask, None, iterations=2)
	#mask = cv2.dilate(mask, None, iterations=2)
	#cv2.imshow("Frame", mask)
	#cv2.imshow("actual", frame)
	#fps.update()
	Thread(target=cv2.imshow("Frame", frame)).start()
	#if cv2.waitKey(1) & 0xFF == ord('q'):
	#	break


#fps.stop()
#print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
#print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))

cv2.destroyAllWindows()
vs.stop()

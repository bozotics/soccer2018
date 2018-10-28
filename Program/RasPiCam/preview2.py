from picamera.array import PiRGBArray
from picamera import PiCamera
from threading import Thread
import cv2
import imutils
import time
import math

class PiVideoStream:
	def __init__(self):
		# initialize the camera and stream
		self.camera = PiCamera(sensor_mode=4)
		self.camera.resolution = (800, 608)
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
		self.stopped = Truevs = PiVideoStream().start()

vs = PiVideoStream().start()
frame = vs.read()
cv2.startWindowThread()
cv2.namedWindow("actual")
while True:
	frame = vs.read()
	cv2.imshow("actual", frame)
cv2.destroyAllWindows()
vs.stop()

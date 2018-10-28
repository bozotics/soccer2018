from __future__ import print_function
from threading import Thread
import numpy as np
import cv2
import time
import math

def get8n(x, y, shape):
	out = []
	maxx = shape[1]-1
	maxy = shape[0]-1

	#top left
	outx = min(max(x-1,0),maxx)
	outy = min(max(y-1,0),maxy)
	out.append((outx,outy))

	#top center
	outx = x
	outy = min(max(y-1,0),maxy)
	out.append((outx,outy))

	#top right
	outx = min(max(x+1,0),maxx)
	outy = min(max(y-1,0),maxy)
	out.append((outx,outy))

	#left
	outx = min(max(x-1,0),maxx)
	outy = y
	out.append((outx,outy))

	#right
	outx = min(max(x+1,0),maxx)
	outy = y
	out.append((outx,outy))

	#bottom left
	outx = min(max(x-1,0),maxx)
	outy = min(max(y+1,0),maxy)
	out.append((outx,outy))

	#bottom center
	outx = x
	outy = min(max(y+1,0),maxy)
	out.append((outx,outy))

	#bottom right
	outx = min(max(x+1,0),maxx)
	outy = min(max(y+1,0),maxy)
	out.append((outx,outy))

	return out

def region_growing(mask, img, seed):
	list = []
	list.append((seed[1], seed[0]))
	processed = []
	while(len(list) > 0):
		pix = list[0]
		#print(pix[0], pix[1])
		mask[pix[0], pix[1]] = 255
		for coord in get8n(pix[0], pix[1], mask.shape):
			if mask[coord[0], coord[1]] != 0:
				if abs(img[coord[0], coord[1], 0] - 50) < 30 and abs(img[coord[0], coord[1], 1] - 110) < 25 and abs(img[coord[0], coord[1], 2] - 245) < 20: #check whether the difference is within threshold
					mask[coord[0], coord[1]] = 255
					if not coord in processed:
						list.append(coord)
					processed.append(coord)
		list.pop(0)
		#cv2.imshow("progress",outimg)
		#cv2.waitKey(1)
	out = mask
	return mask

cap = cv2.VideoCapture(0)

lower = np.array([40, 95, 240])
upper = np.array([70, 130, 255])

while True:
	_, frame = cap.read()
	mask = cv2.inRange(frame, lower, upper)
	cv2.imshow('maskb4', mask)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
mask = cv2.inRange(frame, lower, upper)
b, g, r = frame[:,:,0], frame[:,:,1], frame[:,:,2]
cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
	cv2.CHAIN_APPROX_SIMPLE)[-2]
cv2.imshow('maskb4', mask)
if len(cnts) > 0:
	c = max(cnts, key=cv2.contourArea)
	extLeft = tuple(c[c[:, :, 0].argmin()][0])
	extRight = tuple(c[c[:, :, 0].argmax()][0])
	extTop = tuple(c[c[:, :, 1].argmin()][0])
	extBot = tuple(c[c[:, :, 1].argmax()][0])
	Thread(target=region_growing(mask, frame, extTop)).start
#cv2.imshow('frame', frame)
#mask = cv2.erode(mask, None, iterations=2)
#mask = cv2.dilate(mask, None, iterations=5)
else:
	out = mask
cv2.imshow('mask', out)
while True:
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
#print(frame)
#print(mask)
#cv2.destroyAllWindows()
#(x,y,w,h) = cv2.selectROI(frame)
#cropped = frame[y:y+h, x:x+w]
#print (cropped)
cap.release()
cv2.destroyAllWindows()

import cv2
import numpy as np

cap = cv2.VideoCapture(0)
frame = cv2.imread("cyan.png")
#while True:
#	_, frame = cap.read()
#	cv2.imshow('frame', frame)
#	if cv2.waitKey(1) & 0xFF == ord('q'):
#		break
imCrop = frame
LAB = cv2.cvtColor(imCrop, cv2.COLOR_BGR2Lab)
HSV = cv2.cvtColor(imCrop, cv2.COLOR_BGR2HSV)
HLS = cv2.cvtColor(imCrop, cv2.COLOR_BGR2HLS)
#print(LAB)
#print(HSV)
print(HLS)
#cv2.imshow('selection', imCrop)
#while True:
#	if cv2.waitKey(1) & 0xFF == ord('q'):
#		break
cv2.destroyAllWindows()
#cap.release()
#(x,y,w,h) = cv2.selectROI(frame)
#cropped = frame[y:y+h, x:x+w]
#print (cropped)
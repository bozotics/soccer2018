from __future__ import print_function
import cv2
import numpy as np
x=600
y=456
blueGoalMaskBlue = np.full((y,x), 0, dtype=np.uint8)
blueGoalMask1 = np.full((y,x), 0, dtype=np.uint8)
blueGoalMask1 = cv2.circle(blueGoalMask1,(300,228),280,255,-1)
pts = np.array([[x,y],[x,0],[337,152],[337,304]], np.int32).reshape((-1,1,2))
cv2.fillPoly(blueGoalMaskBlue,[pts],255)
blueGoalMaskBlue = cv2.bitwise_and(blueGoalMaskBlue, blueGoalMask1)
blueGoalMaskBlue = cv2.circle(blueGoalMaskBlue,(300,228),130,(0),-1)
cv2.imshow("mask",blueGoalMaskBlue)

while True:
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
cv2.destroyAllWindows()


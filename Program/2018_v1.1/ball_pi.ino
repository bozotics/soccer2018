void readCamera(){
	if (Serial4.available()>0){
		while (Serial4.available()>0) {
			incomingByte = Serial4.readString();
		}
		end = incomingByte.indexOf('b') + 1;
		if (end==120);
		else incomingByte.remove(0, end);
		incomingByte.remove(5);
		if (incomingByte == "rrrrr") ballAngle = 0;
		else if (incomingByte == "0.000") ballAngle = 0.001;
		else ballAngle = incomingByte.toFloat();
	}
	else ballAngle = 0;
}
void trackAngle(){
	if (abs(ballAngle)<101) moveAngle = ballAngle*1.8;
	else if (ballAngle>100) moveAngle = ballAngle + 50;
	else if (-100>ballAngle) moveAngle = ballAngle - 50;
	if (moveAngle<0) moveAngle = 360+moveAngle;
}
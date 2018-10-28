float anglePolar(float x, float y){
	x -= 400;
	y -= 304;
	if(x==0) x = 0.001;
	angle = atanf(y/x);
	angle = angle*180/pi;
	if (x<0){
		if (angle == 0) angle = 0.001;
		angle = (angle/fabsf(angle))*(180-fabsf(angle));
	}
		else angle = -angle;
	return angle;
} 
float distPolar(float x, float y){
	x -= 400;
	y -= 304;
	if(x==0) x = 0.001;
	tdist = sqrtf(powf(x,2)+powf(y,2));
	//dist;
	return dist; 
}
/* ancient code
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
}*/
float piSerialCancer(){
	tempString = incomingByte;
	break1 = incomingByte.indexOf("a");
	tempString.remove(0,(break1+1));
	incomingByte = tempString;
	break1 = incomingByte.indexOf("a");
	tempString.remove(break1);
	return tempString.toFloat();
}
void readPi(){
	if (Serial4.available()>0){
		while (Serial4.available()>0) {
			incomingByte = Serial4.readStringUntil('b');
		}
		ballx = piSerialCancer();
		bally = piSerialCancer();
		yellowBotx = piSerialCancer();
		yellowBoty = piSerialCancer();
		yellowTopx = piSerialCancer();
		yellowTopy = piSerialCancer();
		blueBotx = piSerialCancer();
		blueBoty = piSerialCancer();
		blueTopx = piSerialCancer();
		blueTopy = piSerialCancer();
		//eg a010a009a008a007a006a005a004a003a002a001ab
	}
}
void initPi(){
	Serial4.write(1);
	Serial.println("written");
	readPi();
	if (yellowBotx>400){
		side = 0;
	}
	else{
		side = 1;
	}
	Serial.println(side);
}
void trackAngle(){
	ballAngle = anglePolar(ballx, bally);
	if (fabsf(ballAngle)<101) moveAngle = ballAngle*1.8;
	else if (ballAngle>100) moveAngle = ballAngle + 50;
	else if (-100>ballAngle) moveAngle = ballAngle - 50;
	if (moveAngle<0) moveAngle = 360+moveAngle;
}
float findGoalAngle(float x1, float y1, float x2, float y2){
	return anglePolar(((x1+x2)/2),((y1+y2)/2));
}
float findGoaly(float y1, float y2){
	return (y1+y2)/2;
}
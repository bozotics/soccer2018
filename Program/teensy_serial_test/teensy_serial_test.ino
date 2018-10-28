void setup(){
	Serial.begin(9600);
	Serial4.begin(230400);
}
String incomingByte, tempString; float ballx, bally, 
yellowGoalTopx, yellowGoalTopy, yellowGoalBottomx, yellowGoalBottomy, 
blueGoalTopx, blueGoalTopy, blueGoalBottomx, blueGoalBottomy, 
break1;
void loop(){
	if (Serial.available()>0){
		Serial4.write(Serial.read());
	}
}
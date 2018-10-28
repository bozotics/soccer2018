void setup() {
	Serial.begin(9600);
	Serial4.begin(230400);
	Serial4.write(1);
}
String incomingByte;
int end;
void loop() {
	if (Serial4.available()>0){
		while (Serial4.available()>0) {
			incomingByte = Serial4.readString();
		}
		//incomingByte.remove(7);
		end = incomingByte.indexOf('b') + 1;
		if (end==120);
		else incomingByte.remove(0, end);
		incomingByte.remove(4);
		Serial.println(incomingByte);
	}
}
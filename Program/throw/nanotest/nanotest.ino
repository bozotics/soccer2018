#define solenoid 2

void setup() {
	pinMode(solenoid, OUTPUT);
	digitalWrite(solenoid, LOW);
	Serial.begin(9600);
}

void loop() {/*
	digitalWrite(solenoid, HIGH);
	delay(50);
	digitalWrite(solenoid, LOW);
	while(true);*/
	Serial.println(analogRead(A0));
	delay(50);
}
#include <NewPing.h>

#define trigPin 12
#define echoPin 13

NewPing sonar(trigPin, echoPin)

void setup(){
	Serial.begin(115200);
}

void loop(){
	Serial.println(sonar.ping_cm);
	delay(100);
}
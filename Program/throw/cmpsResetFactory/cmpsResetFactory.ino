#include <Wire.h>
void setup() {
	Wire.begin();
	Serial.begin(9600);
	Serial.println("start");
	delay(100);
	Wire.beginTransmission(0x60);
	Wire.write(0);
	Wire.write(0x20);
	Wire.endTransmission();
	delay(50);
	Wire.beginTransmission(0x60);
	Wire.write(0);
	Wire.write(0x2A);
	Wire.endTransmission();
	delay(50);
	Wire.beginTransmission(0x60);
	Wire.write(0);
	Wire.write(0x60);
	Wire.endTransmission();
	delay(50);
}

void loop() {
	Serial.println("done");

}

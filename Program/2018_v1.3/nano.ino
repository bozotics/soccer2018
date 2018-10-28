void readUltra () {
	Wire.requestFrom(nano, 4);
	//while(Wire.available()<1);
	ultraFront = Wire.read();
	ultraLeft = Wire.read();
	ultraRight = Wire.read();
	ultraBack = Wire.read();
}
void solenoidKick() { //must have 100ms delay before sense lightgate or kick again
	Wire.beginTransmission(nano);
	Wire.write(1);
	Wire.endTransmission();
}
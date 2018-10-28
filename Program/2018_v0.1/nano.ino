void readUltra () {
	Wire.beginTransmission(nano);
	Wire.write(0);
	Wire.endTransmission();
	Wire.requestFrom(nano, 4);
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
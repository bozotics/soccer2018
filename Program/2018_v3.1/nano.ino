void retrieveUltra() {
	Wire.requestFrom(nano, 4);
	//while(Wire.available()<1);
	tfrontUltra = Wire.read();
	tleftUltra = Wire.read();
	trightUltra = Wire.read();
	tbackUltra = Wire.read();
}
void solenoidKick() { //must have 100ms delay before sense lightgate or kick again
	Wire.beginTransmission(nano);
	Wire.write(1);
	Wire.endTransmission();
}
void startCmps(){
	Wire.beginTransmission(cmps);
	Wire.write(2);
	Wire.endTransmission();
	Wire.requestFrom(cmps, 2); 
	while(Wire.available()<2);
	hbyte = Wire.read();
	lbyte = Wire.read();
	angle16 = hbyte;
	angle16 <<= 8;
	angle16 += lbyte;
	angle16 = angle16/10; //maybe process in 4 digits
	corrCmps = angle16;
}
int readCmps(){
	Wire.beginTransmission(cmps);
	Wire.write(2);
	Wire.endTransmission(false);
	Wire.requestFrom(cmps, 2);
	while(Wire.available()<2);
	hbyte = Wire.read();
	lbyte = Wire.read();
	angle16 = hbyte;
	angle16 <<= 8;
	angle16 += lbyte;
	angle16 = ((angle16/10)-corrCmps+360)%360; //maybe process in 4 digits
	if (angle16>=180) angleCmps = 360 - angle16;
	else angleCmps = -angle16;
	return angleCmps;
}
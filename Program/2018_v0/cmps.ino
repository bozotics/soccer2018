void cmps_start(){
	Wire.beginTransmission(cmps);
	Wire.write(2);
	Wire.endTransmission();
	Wire.requestFrom(cmps, 2);
	hbyte = Wire.read();
	lbyte = Wire.read();
	angle16 = hbyte;
	angle16 <<= 8;
	angle16 += lbyte;
	angle16 = angle16/10; //maybe process in 4 digits
	cmps_corr = angle16;
}
void cmps_read(){
	Wire.beginTransmission(cmps);
	Wire.write(2);
	Wire.endTransmission();
	Wire.requestFrom(cmps, 2);
	hbyte = Wire.read();
	lbyte = Wire.read();
	angle16 = hbyte;
	angle16 <<= 8;
	angle16 += lbyte;
	angle16 = ((angle16/10)-cmps_corr+360)%360; //maybe process in 4 digits
	if (angle16>=180) cmps_angle = 360 - angle16;
	else cmps_angle = -angle16;
}
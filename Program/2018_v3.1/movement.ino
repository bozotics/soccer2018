void spin(int dir, int speed){ // dir: 0 clockwise 1 counter-clockwise
  	fl_dir = 1; fr_dir = 1; bl_dir = 1; br_dir = 1;
  	if(dir){
  	  	fr_dir = 0;
  	  	br_dir = 0;
  	}
  	else{
  	  	fl_dir = 0;
  	  	bl_dir = 0;
  	}
  	digitalWrite(fldir, fl_dir); analogWrite(flpwm, speed);
  	digitalWrite(frdir, fr_dir); analogWrite(frpwm, speed);
  	digitalWrite(bldir, bl_dir); analogWrite(blpwm, speed);
  	digitalWrite(brdir, br_dir); analogWrite(brpwm, speed);
}
void dribbler(int dir, int speed){
  	digitalWrite(dribDIR, dir);
  	analogWrite(dribPWM, speed);
}
void kick(){
    kickTime = millis();
    while(true){
    speedDrib = speedDrib - (millis() - kickTime)*2.2;
    kickTime = millis();
      if(speedDrib<0) digitalWrite(dribDIR, 0);
      else digitalWrite(dribDIR, 1);
     analogWrite(dribPWM, abs(speedDrib));
     if(speedDrib<(-240)) break;
    }
    solenoidKick();
}
void setmove(float angle, float speed, int angleSpin, int multSpin) {
	readCmps();
	fl_dir = 1; fr_dir = 1; bl_dir = 1; br_dir = 1;
	a = cosf(deg2rad(45+angle));
	b = cosf(deg2rad(45-angle));
	if (fabsf(b)>fabsf(a)) {
		a = a*speed/b;
		b = speed;
	}
	else {
		b = b*speed/a;
		a = speed;
	}
	if (angle >= 90 && angle < 270){
		a = -a;
		b = -b;
	}
	fl_pwm = b; fr_pwm = a; bl_pwm = a; br_pwm = b;
	
	if(multSpin == 0) correction = angleCmps * cmps_mult;
	else correction = (angleSpin - angleCmps)  * multSpin;
	fl_pwm -= correction;
	fr_pwm += correction;
	bl_pwm -= correction;
	br_pwm += correction;
	if (fl_pwm < 0) {
		fl_dir = 0;
		fl_pwm = fabsf(fl_pwm);
	}
	if (fr_pwm < 0) {
		fr_dir = 0;
		fr_pwm = fabsf(fr_pwm);
	}
	if (bl_pwm < 0) {
		bl_dir = 0;
		bl_pwm = fabsf(bl_pwm);
	}
	if (br_pwm < 0) {
		br_dir = 0;
		br_pwm = fabsf(br_pwm);
	}
	digitalWrite(fldir, fl_dir); analogWrite(flpwm, fl_pwm);
	digitalWrite(frdir, fr_dir); analogWrite(frpwm, fr_pwm);
	digitalWrite(bldir, bl_dir); analogWrite(blpwm, bl_pwm);
	digitalWrite(brdir, br_dir); analogWrite(brpwm, br_pwm);
}
float deg2rad(float deg){
	return (deg / 180 * pi);
}

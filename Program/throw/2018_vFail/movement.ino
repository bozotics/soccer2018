void spin(int dir, int speed){ // dir: 0 clockwise 1 counter-clockwise
  fl_dir = 1; fr_dir = 0; bl_dir = 1; br_dir = 0;
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
void setmove(float angle, float speed, int spinspeed) {
	fl_dir = 1; fr_dir = 1; bl_dir = 1; br_dir = 1;
	vx = speed*sin(deg2rad(angle));
	vy = speed*cos(deg2rad(angle));
	fl_pwm = (vx*nmoveconst)+(vy*nmoveconst);
	fr_pwm = (vx*pmoveconst)+(vy*nmoveconst);
	bl_pwm = (vx*pmoveconst)+(vy*pmoveconst);
	br_pwm = (vx*nmoveconst)+(vy*nmoveconst); 
	if(spinspeed==0){
		spinspeed = cmps_mult*(angle-cmps_angle);
	}
	fl_pwm = (fl_pwm + baserad*spinspeed)/2.7;
	fr_pwm = (fr_pwm + baserad*spinspeed)/2.7;
	bl_pwm = (bl_pwm + baserad*spinspeed)/2.7;
	br_pwm = (br_pwm + baserad*spinspeed)/2.7;
	if (fl_pwm < 0) {
		fl_dir = 0;
		fl_pwm = abs(fl_pwm);
	}
	if (fr_pwm < 0) {
		fr_dir = 1;
		fr_pwm = abs(fr_pwm);
	}
	if (bl_pwm < 0) {
		bl_dir = 0;
		bl_pwm = abs(bl_pwm);
	}
	if (br_pwm < 0) {
		br_dir = 1;
		br_pwm = abs(br_pwm);
	}
	digitalWrite(fldir, fl_dir); analogWrite(flpwm, fl_pwm);
	digitalWrite(frdir, fr_dir); analogWrite(frpwm, fr_pwm);
	digitalWrite(bldir, bl_dir); analogWrite(blpwm, bl_pwm);
	digitalWrite(brdir, br_dir); analogWrite(brpwm, br_pwm);
}
float deg2rad(float deg){
	return (deg / 180 * pi);
}

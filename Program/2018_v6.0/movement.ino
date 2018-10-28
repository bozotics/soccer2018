void spin(int dir, int speed){ // dir: 0 clockwise 1 counter-clockwise
  	fl_dir = 1; fr_dir = 1; bl_dir = 1; br_dir = 1;
  	if(dir){
  	  	fl_dir = 0;
  	  	bl_dir = 0;
  	}
  	else{
  	  	fr_dir = 0;
  	  	br_dir = 0;
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
void home(){
	if(backUltra > 60) setmove(180, 40, 0, 0);
	else if(rightUltra > 60) setmove(90, 40, 0, 0);
	else if(leftUltra > 60) setmove(270, 40, 0, 0);	
}
void kick(){
	if((millis()- prevkick) > 1000){
		prevkick = millis();
    /*timeKick = millis();
    while(true){
    speedDrib = speedDrib - (millis() - timeKick)*2.2;
    timeKick = millis();
      if(speedDrib<0) digitalWrite(dribDIR, 0);
      else digitalWrite(dribDIR, 1);
     analogWrite(dribPWM, abs(speedDrib));
     if(speedDrib<(-240)) break;
    }*/	
    solenoidKick();
	}
}
void setmove(float angle, float speed, float angleSpin, float multSpin) {
	getAngle = readCmps();
	#if defined striker
		fl_dir = 1; fr_dir = 1; bl_dir = 1; br_dir = 1;
	#elif defined goalie
		fl_dir = 0; fr_dir = 0; bl_dir = 0; br_dir = 0;
	#endif
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
	
	correction = getAngle * cmps_mult;
	fl_pwm -= correction;
	fr_pwm += correction;
	bl_pwm -= correction;
	br_pwm += correction;
	#if defined striker
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
	#elif defined goalie
		if (fl_pwm < 0) {
			fl_dir = 1;
			fl_pwm = fabsf(fl_pwm);
		}
		if (fr_pwm < 0) {
			fr_dir = 1;
			fr_pwm = fabsf(fr_pwm);
		}
		if (bl_pwm < 0) {
			bl_dir = 1;
			bl_pwm = fabsf(bl_pwm);
		}
		if (br_pwm < 0) {
			br_dir = 1;
			br_pwm = fabsf(br_pwm);
		}
	#endif
	digitalWrite(fldir, fl_dir); analogWrite(flpwm, fl_pwm);
	digitalWrite(frdir, fr_dir); analogWrite(frpwm, fr_pwm);
	digitalWrite(bldir, bl_dir); analogWrite(blpwm, bl_pwm);
	digitalWrite(brdir, br_dir); analogWrite(brpwm, br_pwm);
}
float deg2rad(float deg){
	return (deg / 180 * pi);
}

void goalieAlignBall(float yBall, float goal[2][3], float backUltra, float yLeeway, float ultraLeeway, float goalLeeway){
	backUltraDiff = backUltraThreshold - backUltra;
	backUltraCorr = fabsf(backUltraDiff*backUltraMult);
	yDiff = yBall-300;
	yCorr = fabsf(yDiff*yMult);
	if (goal[side][1]>(300-goalLeeway)){
		setmove(90, (goal[side][1]-300+goalLeeway)*goalMult, 0, 0);
	}
	else if (goal[side][0]<(300+goalLeeway)){
		setmove(270, (goal[side][0]-300-goalLeeway)*goalMult, 0, 0);
	}
	else if (backUltraDiff > ultraLeeway && yDiff > yLeeway){
		setmove(293, fabsf(yCorr) + fabsf(backUltraCorr), 0, 0);
	}
	else if (backUltraDiff > ultraLeeway && yDiff < -yLeeway){
		setmove(67, fabsf(yCorr) + fabsf(backUltraCorr), 0, 0);
	}
	else if (backUltraDiff < -ultraLeeway && yDiff > yLeeway){
		setmove(247, fabsf(yCorr) + fabsf(backUltraCorr), 0, 0);
	}
	else if (backUltraDiff < -ultraLeeway && yDiff < -yLeeway){
		setmove(113, fabsf(yCorr) + fabsf(backUltraCorr), 0, 0);
	}
	else if (backUltraDiff > ultraLeeway){
		setmove(0, fabsf(backUltraCorr), 0, 0);
	}
	else if (backUltraDiff < ultraLeeway){
		setmove(180, fabsf(backUltraCorr), 0, 0);
	}
	else if (yDiff > yLeeway){
		setmove(270, fabsf(yCorr), 0, 0);
	}
	else if (yDiff < -yLeeway){
		setmove(90, fabsf(yCorr), 0, 0);
	}
	else setmove (0,0,0,0);
}
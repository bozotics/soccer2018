#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//i2c
#define cmps 0x60
#define nano 0x08

//movement
#define fldir 7
#define flpwm 3
#define frdir 9
#define frpwm 5
#define bldir 22
#define blpwm 23
#define brdir 6
#define brpwm 2
#define dribDIR 8
#define dribPWM 4

//LDR
#define LDR_FL A2
#define LDR_FR A16
#define LDR_LI A20
#define LDR_LM A3
#define LDR_LO A0
#define LDR_RI A19
#define LDR_RM A15
#define LDR_RO A18
#define LDR_BIL A6
#define LDR_BIR A14
#define LDR_BOL A1
#define LDR_BOR A17
#define LDR_GATE A7

#define GATE_Threshold 35
#define FL_threshold 217
#define FR_threshold 174
#define LI_threshold 115
#define LM_threshold 131
#define LO_threshold 112
#define RI_threshold 78
#define RM_threshold 74
#define RO_threshold 78
#define BIL_threshold 185
#define BIR_threshold 173
#define BOL_threshold 84
#define BOR_threshold 82

int FR, FL, LI, LM, LO, RI, RM, RO, BIL, BIR, BOL, BOR;
int rfront, rleft, rright, rback, dir;
int FL_max=0, FR_max=0, LI_max=0, LM_max=0, LO_max=0, RI_max=0, RM_max=0, RO_max=0, BIL_max=0, BIR_max=0, BOL_max=0, BOR_max=0;
int FL_min=999, FR_min=999, LI_min=999, LM_min=999, LO_min=999, RI_min=999, RM_min=999, RO_min=999, BIL_min=999, BIR_min=999, BOL_min=999, BOR_min=999;
int cmps_corr = 0, cmps_angle=0, flag = 0, receive;
int fl_pwm, fr_pwm, bl_pwm, br_pwm;
int end; String incomingByte; float ballAngle, moveAngle;
const float cmps_mult = 0.5, pi = 3.141592653589793, pmoveconst = 1/(sqrt(2)), nmoveconst = (-1)/(sqrt(2));
float fl_dir = 1, fr_dir = 1, bl_dir = 1, br_dir = 1, vx, vy, correction, baserad = 10.8, wheelrad = 2.7;
unsigned int angle16;
unsigned char hbyte, lbyte;
bool robot_out = false, prevfront=false, prevback=false;

//LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
	//lcd.begin();
	//lcd.backlight();
	Serial.begin(9600);
	Wire.begin(0x06);
	Serial4.begin(230400);
	Wire.onReceive(i2c_receive);
	pinMode (fldir, OUTPUT);
	pinMode (flpwm, OUTPUT);
	pinMode (frdir, OUTPUT);
	pinMode (frpwm, OUTPUT);
	pinMode (bldir, OUTPUT);
	pinMode (blpwm, OUTPUT);
	pinMode (brdir, OUTPUT);
	pinMode (brpwm, OUTPUT);
	pinMode (dribDIR, OUTPUT);
	pinMode (dribPWM, OUTPUT);
	setmove(0,0,0);
	analogWrite(dribPWM, 0);
	digitalWrite(dribDIR, 0);
	//analogWrite(dribPWM, 255);
	delay(1000);
	cmps_start();
	/*
	digitalWrite(dribDIR, 1);
	analogWrite(dribPWM, 255);
	delay(1000);
	*/
}

void loop() {
	cmps_read();
	setmove(0, 60, 0);
	Serial.println(cmps_angle);
    Serial.print(bl_pwm);
    Serial.print(" ");
    Serial.print(br_pwm);
    Serial.print(" ");
    Serial.print(fl_pwm);
    Serial.print(" ");
    Serial.println(fr_pwm);
	/*
	cmps_read();
	if(cmps_angle< (-20) || cmps_angle> (-1)){
		if (cmps_angle< 0 && abs(cmps_angle) < 125) spin(1, 0);
		else if(cmps_angle< 0 && abs(cmps_angle) < 130) spin(1, 40);
		else spin(1, 10);
	}
	else{
    	spin(0, 0);
    	analogWrite(dribPWM, 0);
  	}
	if (analogRead(LDR_GATE)<GATE_Threshold) {
		setmove(0,0);
		analogWrite(dribPWM, 200);
	}
	else {
		analogWrite(dribPWM, 0);
		cmps_read();
		readCamera();
		trackAngle();
		setmove(moveAngle, 40);*/
}

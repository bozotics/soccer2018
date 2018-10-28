//#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define striker
#if defined striker //2nd bot
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
#define LDR_FL A17
#define LDR_FR A14
#define LDR_LI A1
#define LDR_LM A6
#define LDR_LO A0
#define LDR_RI A3
#define LDR_RM A20
#define LDR_RO A2
#define LDR_BIL A18
#define LDR_BIR A15
#define LDR_BOL A19
#define LDR_BOR A16
#define LDR_GATE A7

#define GATE_Threshold 50
#define FL_threshold 310
#define FR_threshold 240
#define LI_threshold 140
#define LM_threshold 210
#define LO_threshold 180
#define RI_threshold 140
#define RM_threshold 90
#define RO_threshold 110
#define BIL_threshold 310
#define BIR_threshold 300
#define BOL_threshold 110
#define BOR_threshold 100

int FR, FL, LI, LM, LO, RI, RM, RO, BIL, BIR, BOL, BOR;
int rfront, rleft, rright, rback, rdir;
int FL_max=0, FR_max=0, LI_max=0, LM_max=0, LO_max=0, RI_max=0, RM_max=0, RO_max=0, BIL_max=0, BIR_max=0, BOL_max=0, BOR_max=0;
int FL_min=999, FR_min=999, LI_min=999, LM_min=999, LO_min=999, RI_min=999, RM_min=999, RO_min=999, BIL_min=999, BIR_min=999, BOL_min=999, BOR_min=999;
int cmps_corr = 0, cmps_angle=0, flag = 0, receive;
int fl_pwm, fr_pwm, bl_pwm, br_pwm;
int ultraFront, ultraLeft, ultraRight, ultraBack, tultraFront, tultraLeft, tultraRight, tultraBack, currUltra, ultraThreshold = 40;
int end; String incomingByte; float ballAngle, moveAngle;
const float cmps_mult = 0.35, pi = 3.141592653589793;
float fl_dir = 1, fr_dir = 1, bl_dir = 1, br_dir = 1, a, b, correction;
unsigned int angle16;
unsigned char hbyte, lbyte;
bool robot_out = false, prevfront=false, prevback=false, out=false;
int lightcnt=0, light_mult = 6;
char temp;

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
	//setmove(0,0);
	analogWrite(dribPWM, 0);
	digitalWrite(dribDIR, 1);
	readUltra();
	delay(2000);
	//cmps_start();
}
void loop() {
	if(Serial.available()>0){
		int temp=Serial.read();
		Serial.println("blast");
		Wire.write(1);
	}
	//cmps_read();
	checkUltra();
	readUltra(); //test Ultra
	 digitalWrite(dribDIR, 0); analogWrite(dribPWM, 255);
  //digitalWrite(frdir, fr_dir); analogWrite(frpwm, speed);
  //digitalWrite(bldir, bl_dir); analogWrite(blpwm, speed);
  //digitalWrite(brdir, br_dir); analogWrite(brpwm, speed);
	//LDR_check();
	/*if(LDR_check()){
		setmove(rdir, 60);
	}
	else setmove(0, 0);*/	
}
#elif defined goalie
	#define LDR_FL A17
	#define LDR_FR A14
	#define LDR_LI A1
	#define LDR_LM A6
	#define LDR_LO A0
	#define LDR_RI A3
	#define LDR_RM A20
	#define LDR_RO A2
	#define LDR_BIL A18
	#define LDR_BIR A15
	#define LDR_BOL A19
	#define LDR_BOR A16
	#define LDR_GATE A7
#else 

#endif	

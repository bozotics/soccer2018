//#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <math.h>

#define striker

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

#if defined striker //2nd bot
	
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

	#define GATE_Threshold 50
	#define FL_threshold 183
	#define FR_threshold 150
	#define LI_threshold 300
	#define LM_threshold 90
	#define LO_threshold 80
	#define RI_threshold 110
	#define RM_threshold 110
	#define RO_threshold 110
	#define BIL_threshold 130
	#define BIR_threshold 200
	#define BOL_threshold 80
	#define BOR_threshold 81	

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

	#define GATE_Threshold 200
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
#else 

#endif	

//LDR
int FR, FL, LI, LM, LO, RI, RM, RO, BIL, BIR, BOL, BOR;
int FL_max=0, FR_max=0, LI_max=0, LM_max=0, LO_max=0, RI_max=0, RM_max=0, RO_max=0, BIL_max=0, BIR_max=0, BOL_max=0, BOR_max=0;
int FL_min=999, FR_min=999, LI_min=999, LM_min=999, LO_min=999, RI_min=999, RM_min=999, RO_min=999, BIL_min=999, BIR_min=999, BOL_min=999, BOR_min=999;
int rfront, rleft, rright, rback, rdir;
bool robot_out = false, prevfront=false, prevback=false, out=false;
int lightcnt=0, light_mult = 3;
//Cmps
int corrCmps = 0, angleCmps=0, flag = 0, receive;
unsigned int angle16;
unsigned char hbyte, lbyte;
//Ultra
int frontUltra, rightUltra, leftUltra, backUltra, tfrontUltra, trightUltra, tleftUltra, tbackUltra, currUltra, thresholdUltra = 30; 
//movement
int fl_pwm, fr_pwm, bl_pwm, br_pwm, fl_dir = 1, fr_dir = 1, bl_dir = 1, br_dir = 1;
const float cmps_mult = 0.5, pi = 3.141592653589793;
float a, b, correction;
float speedDrib, kickTime;
char temp;
//pi xy coords
float ballx, bally, yellowTopx, yellowTopy, yellowBotx, yellowBoty, blueTopx, blueTopy, blueBotx, blueBoty, angle, break1, side, tdist; //side==1 is start at blue side, side==2 is start at yellow side. 
float dist, angleBall, angleMove, distBall, centerx, centery, angleGoal, distGoal, fieldside; //fieldside==1 is at right, fieldside==2 is at the left
String incomingByte, tempString;

//LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
	//lcd.begin();
	//lcd.backlight();
	Serial.begin(9600);
	Serial.println("start");
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
	//setmove(0, 0, 0, 0);
	readUltra();
	delay(2000);
	startCmps();
	initPi();
	//analogWrite(dribPWM, 255);
	//digitalWrite(dribDIR, 0);
	//while(!Light_Gate());
}
void loop() {
	//run_LDRDebug();
	readPi();
	trackAngle();
	trackGoal();
	readUltra();
	//Serial.println(angleMove);
	/*if(frontUltra < 20 && fabsf(angleMove)<80){
		Serial.println("slow");
		setmove(angleMove, 20, 0, 0);
	}*/
	readCmps();
	Serial.println(distBall);
	//Serial.println(angleCmps);
	if(checkLDR()){
		//Serial.println("out");
		//Serial.println(rdir);
		setmove(rdir, 40, 0, 0);
	}
	else{
		setmove(angleMove, 60, 0, 0);
		//Serial.println("tracking");
	}
	/*else if(checkLDR()){
		if(fieldside=='r'){
			if(rright==1){
				if(angleBall>=5 && angleBall<=60) setmove(0, 30, 0, 0);
				else if(angleBall<5){
					setmove(angleMove, 60, 0, 0);
					robot_out = false;
				}
				else setmove(0, 0, 0, 0);
			}
			else setmove(rdir, 60, 0, 0);
		}
		else if(fieldside=='l'){
			if(rleft==1){
				if(angleBall<=-5 && angleBall>=-60) setmove(0, 30, 0, 0);
				else if(angleBall>-5){
					setmove(angleMove, 60, 0, 0);
					robot_out = false;
				}
				else setmove(0, 0, 0, 0);
			}
			else setmove(rdir, 60, 0, 0);
		}
	}
	else{
		setmove(angleMove, 60, 0, 0);
	}*/
}
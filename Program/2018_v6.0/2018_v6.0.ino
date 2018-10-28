//#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <math.h>

#define goalie

//i2c
#define cmps 0x60
#define nano 0x08
#define ADDRESS 0x60
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

	#define GATE_Threshold 150
	#define FL_threshold 45
    #define FR_threshold 45
    #define LI_threshold 70
    #define LM_threshold 80
    #define LO_threshold 50
    #define RI_threshold 60
    #define RM_threshold 70
    #define RO_threshold 90
    #define BIL_threshold 50
    #define BIR_threshold 1008
    #define BOL_threshold 45
    #define BOR_threshold 43
	

#elif defined goalie

	#define LDR_FL A2
	#define LDR_FR A20
	#define LDR_LI A16
	#define LDR_LM A19
	#define LDR_LO A15
	#define LDR_RI A18
	#define LDR_RM A14
	#define LDR_RO A17
	#define LDR_BIL A3
	#define LDR_BIR A0
	#define LDR_BOL A6
	#define LDR_BOR A1
	#define LDR_GATE A7

    #define GATE_Threshold 90
	#define FL_threshold 120
    #define FR_threshold 80
    #define LI_threshold 90
    #define LM_threshold 90
    #define LO_threshold 70
    #define RI_threshold 70
    #define RM_threshold 65
    #define RO_threshold 50
    #define BIL_threshold 110
    #define BIR_threshold 125
    #define BOL_threshold 1015
	#define BOR_threshold 70


#else 

#endif	

//LDR
int FR, FL, LI, LM, LO, RI, RM, RO, BIL, BIR, BOL, BOR;
int FL_max=0, FR_max=0, LI_max=0, LM_max=0, LO_max=0, RI_max=0, RM_max=0, RO_max=0, BIL_max=0, BIR_max=0, BOL_max=0, BOR_max=0;
int FL_min=999, FR_min=999, LI_min=999, LM_min=999, LO_min=999, RI_min=999, RM_min=999, RO_min=999, BIL_min=999, BIR_min=999, BOL_min=999, BOR_min=999;
int rfront, rleft, rright, rback, rdir;
bool robot_out = false, prevfront=false, prevback=false, out=false, stall = false;
int lightcnt=0, light_mult = 3, timeLDR, timeStall;
//Cmps
int corrCmps = 0, angleCmps=0, flag = 0, receive, getAngle;
unsigned int angle16;
unsigned char hbyte, lbyte;
//Ultra
int frontUltra, rightUltra, leftUltra, backUltra, tfrontUltra, trightUltra, tleftUltra, tbackUltra, currUltra, thresholdUltra = 35; 
//movement
int fl_pwm, fr_pwm, bl_pwm, br_pwm, fl_dir = 1, fr_dir = 1, bl_dir = 1, br_dir = 1;
const float cmps_mult = 0.5, pi = 3.141592653589793;
float a, b, correction;
float speedDrib, timeKick;
char temp;
float prevkick, ldrtime;
//pi xy coords
int side;
float ballx, bally, 
yellowTopx, yellowTopy, yellowBotx, yellowBoty, 
blueTopx, blueTopy, blueBotx, blueBoty, 
angle, break1, tdist, tclr, //side==0 is start at blue side, side==1 is start at yellow side. 
dist, angleBall, angleMove, distBall, 
centerx, centery, angleGoal, distGoal, fieldside, //fieldside==1 is at right, fieldside==2 is at the left
goaly[2][3], goalMult = 2.5, blueGoaly, yellowGoaly, yCorr, yDiff, yMult = 2, //goal[*][0] is top, goal[*][1] is bottom, goal[*][2] is middle
backUltraCorr, backUltraDiff, backUltraMult = 2, backUltraThreshold = 13,
ballThreshold = 140, goalThreshold = 160;
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
	delay(2000);
	startCmps();
	initPi();
	Serial.println("start");
}

void loop() {
	//indiv_debugLDR();
	getAngle= readCmps();
	//indiv_debugLDR();
	readPi();
	readUltra();
	trackAngle();
	trackGoal();
	if(checkLDR()) setmove(rdir, 60, 0, 0);
	else if(leftUltra < 30 || rightUltra < 30 || frontUltra<10||backUltra< 10) setmove(angleMove, 60, 0, 0);
	else if(distBall<120) setmove(angleMove,60, 0, 0);
	else  setmove(angleMove, 85, 0, 0);

//else if(frontUltra < 20 || backUltra < 20 || leftUltra < 20 || rightUltra < 20) setmove(angleMove, 40, 0, 0);
		/*else if(false && (millis()-ldrtime) > 500){
			ldrtime = millis();
			//dribbler(0, 255);
			if(distGoal < 180){
				setmove(0, 130, 0, 0);
				delay(200);
				//if(abs(getAngle - angleGoal)<5){
				kick();
				}
			else setmove(0, 80, 0, 0);
	}
		/*else if(distBall < 120 && fabsf(angleBall)<50){
			//dribbler(0, 255);
			setmove(angleMove, 45, 0, 0);
		}
		else if(angleMove > 100 && distBall < 140) setmove(angleMove, 40, 0, 0);
		else{
			if(angleMove < 30 && angleMove >330) setmove(angleMove, 100, 0, 0);
			else setmove(angleMove, 45, 0, 0);
		}*/
}
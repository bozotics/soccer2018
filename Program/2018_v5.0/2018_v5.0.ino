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

	#define GATE_Threshold 300
	#define FL_threshold 180
    #define FR_threshold 190
    #define LI_threshold 90
    #define LM_threshold 90
    #define LO_threshold 140
    #define RI_threshold 90
    #define RM_threshold 90
    #define RO_threshold 90
    #define BIL_threshold 210
    #define BIR_threshold 1000
    #define BOL_threshold 110
    #define BOR_threshold 100
	

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

    #define GATE_Threshold 80
	#define FL_threshold 220
    #define FR_threshold 260
    #define LI_threshold 140
    #define LM_threshold 300
    #define LO_threshold 260
    #define RI_threshold 140
    #define RM_threshold 180
    #define RO_threshold 180
    #define BIL_threshold 280
    #define BIR_threshold 140
    #define BOL_threshold 260
	#define BOR_threshold 200


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
int timekick;
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
	//initPi();
}

void loop() {
	#if defined goalie
	getAngle= readCmps();
	readPi();
	readUltra();
	trackAngle();
	trackGoal();
	Serial.println(distBall);
	//if(checkLDR()) setmove(rdir, 60, 0, 0);
	/*else if(Light_Gate()){
			dribbler(1, 255);
			if(distGoal < 200){
				setmove(-angleCmps, 80, angleGoal, 0.3);
				if(abs(getAngle - angleGoal)<4)
				kick();
			}
			else setmove(-angleCmps, 60, angleGoal, 0.3);
		}
		else if(distBall < 120 && fabsf(angleBall)<50){
			dribbler(1, 255);
			setmove(angleMove, 60, 0, 0);
		}*/
		else{
			setmove(angleMove, 60, 0, 0);
		}

	#endif
}
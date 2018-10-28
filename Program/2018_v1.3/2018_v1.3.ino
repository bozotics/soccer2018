//#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define goalie

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

#elif defined goalie

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
	#define FL_threshold 262
	#define FR_threshold 210
	#define LI_threshold 94
	#define LM_threshold 109
	#define LO_threshold 70
	#define RI_threshold 85
	#define RM_threshold 77
	#define RO_threshold 93
	#define BIL_threshold 184
	#define BIR_threshold 240
	#define BOL_threshold 66
	#define BOR_threshold 47

#else 

#endif	

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
char fieldside;
bool robot_out = false, prevfront=false, prevback=false, out=false;
int lightcnt=0, light_mult = 3;
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
	//setmove(0, 0, 0, 0);
	analogWrite(dribPWM, 0);
	digitalWrite(dribDIR, 1);
	readUltra();
	delay(2000);
	cmps_start();
	while(Serial.available() == 0){
		setmove(0, 0, 0, 0);
	}
	int useless = Serial.read();
}
void loop() {
	cmps_read();
	readUltra();
	if(ultraLeft>35) setmove(270, 40, 0, 0);
  	else if(ultraLeft<10) setmove(90,40, 0, 0);
   	FL = analogRead(LDR_FL);
    FR = analogRead(LDR_FR);
    LI = analogRead(LDR_LI);
    LM = analogRead(LDR_LM);
    LO = analogRead(LDR_LO);
    RI = analogRead(LDR_RI);
    RM = analogRead(LDR_RM);
    RO = analogRead(LDR_RO);
    BIL = analogRead(LDR_BIL);
    BIR = analogRead(LDR_BIR);
    BOL = analogRead(LDR_BOL);
    BOR = analogRead(LDR_BOR);
    
    if(FL<FL_min) FL_min = FL; if(FL>FL_max) FL_max = FL;
    if(FR<FR_min) FR_min = FR; if(FR>FR_max) FR_max = FR;
    if(LI<LI_min) LI_min = LI; if(LI>LI_max) LI_max = LI;
    if(LM<LM_min) LM_min = LM; if(LM>LM_max) LM_max = LM;
    if(LO<LO_min) LO_min = LO; if(LO>LO_max) LO_max = LO;
    if(RI<RI_min) RI_min = RI; if(RI>RI_max) RI_max = RI;
    if(RM<RM_min) RM_min = RM; if(RM>RM_max) RM_max = RM;
    if(RO<RO_min) RO_min = RO; if(RO>RO_max) RO_max = RO;
    if(BIL<BIL_min) BIL_min = BIL; if(BIL>BIL_max) BIL_max = BIL;
    if(BIR<BIR_min) BIR_min = BIR; if(BIR>BIR_max) BIR_max = BIR;
    if(BOL<BOL_min) BOL_min = BOL; if(BOL>BOL_max) BOL_max = BOL;
    if(BOR<BOR_min) BOR_min = BOR; if(BOR>BOR_max) BOR_max = BOR;
    
  if(Serial.available()>0){
    int temp = Serial.read();
	if(temp == 1){
		setmove(0, 0, 0, 0);
		while(true);
	}
	else if(temp == 2){
    Serial.print("FL  Min: "); Serial.print(FL_min); Serial.print(" Max: "); Serial.print(FL_max); Serial.print(" Threshold: "); Serial.println(FL_max-30);
    Serial.print("FR  Min: "); Serial.print(FR_min); Serial.print(" Max: "); Serial.print(FR_max); Serial.print(" Threshold: "); Serial.println(FR_max-30);
    Serial.print("LI  Min: "); Serial.print(LI_min); Serial.print(" Max: "); Serial.print(LI_max); Serial.print(" Threshold: "); Serial.println(LI_max-30);
    Serial.print("LM  Min: "); Serial.print(LM_min); Serial.print(" Max: "); Serial.print(LM_max); Serial.print(" Threshold: "); Serial.println(LM_max-30);
    Serial.print("FO  Min: "); Serial.print(LO_min); Serial.print(" Max: "); Serial.print(LO_max); Serial.print(" Threshold: "); Serial.println(LO_max-30);
    Serial.print("RI  Min: "); Serial.print(RI_min); Serial.print(" Max: "); Serial.print(RI_max); Serial.print(" Threshold: "); Serial.println(RI_max-30);
    Serial.print("RM  Min: "); Serial.print(RM_min); Serial.print(" Max: "); Serial.print(RM_max); Serial.print(" Threshold: "); Serial.println(RM_max-30);
    Serial.print("RO  Min: "); Serial.print(RO_min); Serial.print(" Max: "); Serial.print(RO_max); Serial.print(" Threshold: "); Serial.println(RO_max-30);
    Serial.print("BIL  Min: "); Serial.print(BIL_min); Serial.print(" Max: "); Serial.print(BIL_max); Serial.print(" Threshold: "); Serial.println(BIL_max-30);
    Serial.print("BIR  Min: "); Serial.print(BIR_min); Serial.print(" Max: "); Serial.print(BIR_max); Serial.print(" Threshold: "); Serial.println(BIR_max-30);
    Serial.print("BOL  Min: "); Serial.print(BOL_min); Serial.print(" Max: "); Serial.print(BOL_max); Serial.print(" Threshold: "); Serial.println(BOL_max-30);
    Serial.print("BOR  Min: "); Serial.print(BOR_min); Serial.print(" Max: "); Serial.print(BOR_max); Serial.print(" Threshold: "); Serial.println(BOR_max-30);
    Serial.println();
	}
  }
}
	/*cmps_read();
	readCamera();
	trackAngle();	
	checkUltra();
	if(ultraFront < 30 && abs(moveAngle)<30) setmove(moveAngle, 20, 0, 0);
	else if(LDR_check()){
		setmove(rdir, 60, 0, 0);
	} 
	else setmove(moveAngle, 60, 0, 0);*/
	/*else if(LDR_check()){
		if(fieldside=='r'){
			if(rright==1){
				if(ballAngle>=5 && ballAngle<=60) setmove(0, 40, 0, 0);
				else if(ballAngle<5){
					setmove(moveAngle, 60, 0, 0);
					robot_out = false;
				}
				else setmove(0, 0, 0, 0);
			}
			else setmove(rdir, 60, 0, 0);
		}
		else if(fieldside=='l'){
			if(rleft==1){
				if(ballAngle<=-5 && ballAngle>=-60) setmove(0, 40, 0, 0);
				else if(ballAngle>-5){
					setmove(moveAngle, 60, 0, 0);
					robot_out = false;
				}
				else setmove(0, 0, 0, 0);
			}
			else setmove(rdir, 60, 0, 0);
		}
	}
	else{
		setmove(moveAngle, 60, 0, 0);
	}*/
#include <Wire.h>
#include <SPI.h>

#define SONAR_NUM 3

#define MicroADDR 121
 
#define PIN_FL_A 34
#define PIN_FR_A 33
#define PIN_BL_A 36
#define PIN_BR_A 31

#define PIN_FL_B 35
#define PIN_FR_B 32
#define PIN_BL_B 37
#define PIN_BR_B 30

#define PWM_FL 9
#define PWM_FR 11
#define PWM_BL 8
#define PWM_BR 10

#define CMPSADDR 0x60
#define ANGLE_8 1

#define IRADDR_F 0x01
#define IRADDR_B 0x02
#define compensationmult 110

int rangeUS[SONAR_NUM]; // 0=US_Left, 1=US_Back, 2=US_Right

int maxspeed = 100;
float cmpsangleradian = 0;
int SmotorFL = 0, SmotorFR = 0, SmotorBL = 0, SmotorBR=0; 
int cmpsoffset = 0;
int IRdir=0, IRstr=0, IRFB=0;
int IRthreshold = 0;
int IRspeed = 110;
int clockwisecompensation = 0;
int counterclockwisecompensation = 0;
int compensateangle = 3.141592654*30/180; 
unsigned char high_byte, low_byte, angle8;
unsigned int angle16, cmpsangle;
bool out=false;
int distance = 160;
int leeway = 30;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  initIR();
  pinMode(PIN_FL_A,OUTPUT);
  pinMode(PIN_FR_A,OUTPUT);
  pinMode(PIN_BL_A,OUTPUT);
  pinMode(PIN_BR_A,OUTPUT);
  pinMode(PIN_FL_B,OUTPUT);
  pinMode(PIN_FR_B,OUTPUT);
  pinMode(PIN_BL_B,OUTPUT);
  pinMode(PIN_BR_B,OUTPUT);
  pinMode(PWM_FL,OUTPUT);
  pinMode(PWM_FR,OUTPUT);
  pinMode(PWM_BL,OUTPUT);
  pinMode(PWM_BR,OUTPUT);
  initcomp();
  initUS();
}

void loop() {
    maxspeed=100;
    readIR();
    readComp();
    readUS(); 
    out=false;
    //checkout();
    if(!out){
    if(IRstr>15) trackball();
    else returnbase();
    }
    analogWrite(PWM_FL,abs(SmotorFL));digitalWrite(PIN_FL_A,SmotorFL>0?HIGH:LOW);digitalWrite(PIN_FL_B,SmotorFL<0?HIGH:LOW);
    analogWrite(PWM_FR,abs(SmotorFR));digitalWrite(PIN_FR_A,SmotorFR>0?HIGH:LOW);digitalWrite(PIN_FR_B,SmotorFR<0?HIGH:LOW);
    analogWrite(PWM_BL,abs(SmotorBL));digitalWrite(PIN_BL_A,SmotorBL>0?HIGH:LOW);digitalWrite(PIN_BL_B,SmotorBL<0?HIGH:LOW);
    analogWrite(PWM_BR,abs(SmotorBR));digitalWrite(PIN_BR_A,SmotorBR>0?HIGH:LOW);digitalWrite(PIN_BR_B,SmotorBR<0?HIGH:LOW);
}

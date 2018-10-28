#include <Wire.h>
#include <NewPing.h>

#define teensy 0x06

#define MAX_DISTANCE 200
#define SONAR_NUM 4
#define PING_INTERVAL 31
unsigned long pingTimer[SONAR_NUM], solenoidTimer;
unsigned int cm[SONAR_NUM];
uint8_t currentSensor=0;
NewPing sonar[SONAR_NUM]{
	NewPing(11,12,230), //front
	NewPing(9,10,170), //left
	NewPing(7,8,170), //right
	NewPing(5,6,230) //back
};

int receive, requested, leftUltra, rightUltra, frontUltra, backUltra;
bool received = false, kick = false;

void setup(){
	Serial.begin(9600);
	Wire.begin(0x08);
	pinMode(2, OUTPUT);
	digitalWrite(2, 0);
	pingTimer[0] = millis()+75;
	for (uint8_t i = 1; i < SONAR_NUM; i++) pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
	Wire.onReceive(i2c_receive);
	Wire.onRequest(i2c_request);
}

void loop(){
	ultraRead();
	solenoidKick();
}
#include <Wire.h>

#define SLAVE_ADDR 0x08

int i=0, first=0;

void setup() {
	Serial.begin(9600);
	Wire.begin(SLAVE_ADDR);
	//Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
}

void loop() {
	// put your main code here, to run repeatedly:
}

void sendData(){
	if (first==0){
		first=1;
		i=0;
	}
	i++;
	if (i==1) Wire.write(1);
	else if (i==2) Wire.write(2);
	else Wire.write(34);
}

#include <NewPing.h>
 
#define TRIGGER_PIN  30
#define ECHO_PIN     32
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
	pinMode(22,OUTPUT);
	pinMode(24,OUTPUT);
  Serial.begin(115200);
}
 
void loop() {
	digitalWrite(22,HIGH);
	digitalWrite(24,LOW);

  delay(50);
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
}

#include <NewPing.h>
#include <Wire.h>

// Micro Address
#define MicroADDR 121

// Multiplexer Pins

#define s0 A0
#define s1 A1
#define s2 A2
#define s3 A3

#define SIG_pin A6

// US Pins
#define US_L_Trig 9
#define US_L_Echo 10

#define US_B_Trig 11
#define US_B_Echo 12

#define US_R_Trig 7
#define US_R_Echo 8

#define US_F_Trig 5
#define US_F_Echo 6

#define SONAR_NUM      4 // Number of sensors.
#define MAX_DISTANCE 250 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
byte cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.
byte light[18];

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  NewPing(US_L_Trig, US_L_Echo, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. (In this order)
  NewPing(US_B_Trig, US_B_Echo, MAX_DISTANCE),
  NewPing(US_R_Trig, US_R_Echo, MAX_DISTANCE),
  NewPing(US_F_Trig, US_F_Echo, MAX_DISTANCE)
};

void setup() {
  Wire.begin(MicroADDR);                        // Initialise device #121 (random large number here <128)
  Wire.onRequest(requestCallback);        // When a request for data is receive call function requestCallback
  
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  
  Serial.begin(9600);
  pingTimer[0] = millis() + 25;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      //cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      // NOTE FROM JM: I COMMENTED OUT THE PREVIOUS LINE. BASICALLY THIS MEANS IT WILL USE THE LAST VALUE IF NO ECHO DETECTED 
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
  for(int i = 2; i < 16; i ++){
    light[i-2+SONAR_NUM] = readMux(i);
    //Serial.print(readMux(i));
    //Serial.print("   ");    
  }
  for (int i = 0; i < 18; i++) {
  //Serial.print(light[i]);
  //Serial.print("   ");
  }
  //Serial.println("");
  // Other code that *DOESN'T* analyze ping results can go here.
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    light[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
    //Serial.print(light[currentSensor]);
    //Serial.print("  ");
    //cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  for (uint8_t i = 0; i < 18; i++) {
    //Serial.print(i);
    //Serial.print("=");
    Serial.print(light[i]);
    //Serial.print("cm");
    Serial.print("  ");
  }
  Serial.println("   ");
}

void requestCallback(){
  Wire.write(light, 18); // Send array of sensor values
}

int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  return val;
}

 #include <Wire.h>

#define ADDRESS 0x60

void setup(){
  Wire.begin();
  Serial.begin(9600);
  calibrate();
}

void loop(){
}

void calibrate(){

  Serial.println("Calibration Mode");
  delay(2000);  //2 second before starting
  Serial.println("Start");

  Wire.beginTransmission(ADDRESS);
  Wire.write(0); //command register
  Wire.write(0xF0);
  Wire.endTransmission();
  delay(25);

  Wire.beginTransmission(ADDRESS);
  Wire.write(0); //command register
  Wire.write(0xF5);
  Wire.endTransmission();
  delay(25);

  Wire.beginTransmission(ADDRESS);
  Wire.write(0); //command register
  Wire.write(0xF7);
  Wire.endTransmission();

  delay(30000);

  Wire.beginTransmission(ADDRESS);
  Wire.write(0); //command register
  Wire.write(0xF8);
  Wire.endTransmission();
  Serial.println("done");


}
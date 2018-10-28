void initcomp() {
  readComp();
  cmpsoffset = cmpsangle;
 // Serial.print(cmpsoffset);
}

void readComp() {
  
  Wire.beginTransmission(CMPSADDR);  //starts communication with CMPS11
  Wire.write(ANGLE_8);                //Sends the register we wish to start reading from
  Wire.endTransmission();
 
  // Request 5 bytes from the CMPS11
  // this will give us the 8 bit bearing, 
  // both bytes of the 16 bit bearing, pitch and roll
  Wire.requestFrom(CMPSADDR, 5);       
  
  while(Wire.available() < 5);        // Wait for all bytes to come back
  
  angle8 = Wire.read();               // Read back the 5 bytes
  high_byte = Wire.read();
  low_byte = Wire.read();
//  pitch = Wire.read();
 // roll = Wire.read();
  
  angle16 = high_byte;                 // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;
    
  //Serial.print("roll: ");               // Display roll data
  //Serial.print(roll, DEC);
  
  //Serial.print("    pitch: ");          // Display pitch data
  //Serial.print(pitch, DEC);
  
  //Serial.print("    angle full: ");     // Display 16 bit angle with decimal place
  //Serial.print(angle16 / 10, DEC);
  //Serial.print(".");
  //Serial.print(angle16 % 10, DEC);
  cmpsangle = angle16/10;
  if (cmpsangle<cmpsoffset){
    cmpsangle = cmpsangle+360;
    cmpsangle = cmpsangle - cmpsoffset;
  }
  else {
    cmpsangle = cmpsangle - cmpsoffset;
  }
  cmpsangleradian = 3.141592654/180*cmpsangle;
  
  //Serial.print("    angle 8: ");        // Display 8bit angle
  //Serial.println(angle8, DEC);

}

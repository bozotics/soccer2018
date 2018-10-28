void initUS(){
  Wire.beginTransmission(MicroADDR); //Request from slave
  Wire.requestFrom(MicroADDR,SONAR_NUM); //Request 3 values from slave
  /*
  if (Wire.available() == SONAR_NUM) {
    for (int i=1; i<=SONAR_NUM; i++) rangeUS[i]=Wire.read();
  }
  */
  Wire.endTransmission();
}

void readUS(){
  Wire.beginTransmission(MicroADDR); //Request from slave
  Wire.requestFrom(MicroADDR,SONAR_NUM); //Request 3 values from slave
  Wire.endTransmission();

  if (Wire.available() == SONAR_NUM) {
    for (int i=0; i<SONAR_NUM; i++) rangeUS[i]=Wire.read();
  }

  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(rangeUS[i]);
    Serial.println("cm    ");
  }
 Serial.println("");
  
}
int getRangeB() {
   return (cos(cmpsangleradian)*rangeUS[1]);
}

int getRangeR() {
  if(cmpsangle>=0&&cmpsangle<180){
    return (cos(abs(compensateangle-cmpsangleradian))*rangeUS[2]);  
  }
  else if (cmpsangle>=180&&cmpsangle<360){
    return (cos(compensateangle+cmpsangleradian)*rangeUS[2]);
  }
}

int getRangeL() {
  if(cmpsangle>=0&&cmpsangle<180){
    return (cos(compensateangle+cmpsangleradian)*rangeUS[0]);  
  }
  else if (cmpsangle>=180&&cmpsangle<360){
    return (cos(abs(compensateangle-cmpsangleradian))*rangeUS[0]);
  }
}




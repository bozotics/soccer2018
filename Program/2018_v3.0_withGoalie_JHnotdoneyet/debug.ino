    //test LDR
    //setup
	void setup_LDRDebug(){
    while(Serial.available() == 0){
		Serial.println("Activate");
    delay(100);
		  setmove(0, 0, 0, 0);
	  }
	  int useless = Serial.read();
	  Serial.println("Done");
    setmove(90, 40, 0, 0);
  }
    // loop
  void run_LDRDebug(){
    readCmps();
  	readUltra();
	  if(rightUltra>35) setmove(90, 40, 0, 0);
  	else if(rightUltra<10) setmove(270, 40, 0, 0);
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
	Serial.println("Got it");
	if(temp == 50){
		Serial.println("exit");
		setmove(0, 0, 0, 0);
		while(true);
	}
	else if(temp == 49){
		Serial.println("Values: ");
    Serial.print("FL  Min: "); Serial.print(FL_min); Serial.print(" Max: "); Serial.print(FL_max); Serial.print(" Threshold: "); Serial.println(FL_max-30);
    Serial.print("FR  Min: "); Serial.print(FR_min); Serial.print(" Max: "); Serial.print(FR_max); Serial.print(" Threshold: "); Serial.println(FR_max-30);
    Serial.print("LI  Min: "); Serial.print(LI_min); Serial.print(" Max: "); Serial.print(LI_max); Serial.print(" Threshold: "); Serial.println(LI_max-30);
    Serial.print("LM  Min: "); Serial.print(LM_min); Serial.print(" Max: "); Serial.print(LM_max); Serial.print(" Threshold: "); Serial.println(LM_max-30);
    Serial.print("LO  Min: "); Serial.print(LO_min); Serial.print(" Max: "); Serial.print(LO_max); Serial.print(" Threshold: "); Serial.println(LO_max-30);
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

     //test movement
  void moveDebug(){
    //Serial.println(angleCmps);
    Serial.print(bl_pwm);
    Serial.print(" ");
    Serial.print(br_pwm);
    Serial.print(" ");
    Serial.print(fl_pwm);
    Serial.print(" ");
    Serial.println(fr_pwm);
  }


void ultraDebug(){
	readUltra(); //test Ultra
  	Serial.print("Front: ");
	Serial.print(tfrontUltra);
	Serial.print(" Left: ");
	Serial.print(tleftUltra);
	Serial.print(" Right: ");
	Serial.print(trightUltra);
	Serial.print(" Back: ");
	Serial.println(tbackUltra);
}

void camDebug(){
  Serial.println(ballx);
  Serial.print("ballx: "); //test Cam
  Serial.println(bally);
  Serial.print("bally: ");
	Serial.println(yellowTopx);
  Serial.print("yellowTopx: ");
  Serial.println(yellowTopy);
  Serial.print("yellowTopy: ");
	Serial.println(yellowBotx);
	Serial.print("yellowBotx: ");
  Serial.println(yellowBoty);
	Serial.print("yellowBoty: ");
	Serial.println(blueTopx);
	Serial.print("blueTopx: ");
	Serial.println(blueTopy);
  Serial.print("blueTopy: ");
	Serial.println(blueBotx);
  Serial.print("blueBotx: ");
	Serial.println(blueBoty);
	Serial.print("blueBoty: ");
}

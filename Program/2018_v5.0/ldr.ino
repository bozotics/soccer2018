bool Light_Gate(){
  if (analogRead(LDR_GATE)<GATE_Threshold) return true;
  else return false;
}
bool checkLDR(){
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
	if ((FL>FL_threshold  || FR>FR_threshold) && (frontUltra < thresholdUltra)) rfront = 2;
	if(backUltra < thresholdUltra){
	if (BOL>BOL_threshold || BOR>BOR_threshold) rback = 1;
	else if (BIL>BIL_threshold || BIR>BIR_threshold) rback = 2;
	}
	if(leftUltra < thresholdUltra && fieldside == 1){
	if (LO>LO_threshold) rleft = 1;
	else if (LM>LM_threshold) rleft = 2;
	else if (LI>LI_threshold) rleft = 3;
	else if (RO>RO_threshold) rleft = 4;
	else if (RM>RM_threshold) rleft = 5;
	else if (RI>RI_threshold) rleft = 6;
	}
	if(rightUltra < thresholdUltra && fieldside == 2){
	if (RO>RO_threshold) rright = 1;
	else if (RM>RM_threshold) rright = 2;
	else if (RI>RI_threshold) rright = 3;
	else if (LO>LO_threshold) rright = 4;
	else if (LM>LM_threshold) rright = 5;
	else if (LI>LI_threshold) rright = 6;
	}
	if(robot_out){
	  if((millis()-timeLDR) > 1000) robot_out = false;
	  else if(rdir > 45 && rdir <= 135){
		  if(leftUltra > (currUltra+(rleft*light_mult))){
			  rleft = 0;
			  robot_out = false;
		  }
	  }
	  else if(rdir > 135 && rdir <=225){
		  if(frontUltra > (currUltra+(rfront*light_mult))){
			  rfront = 0;
			  robot_out = false;
		  }
	  }
	  else if(rdir > 225 && rdir <=315){
		  if(rightUltra > (currUltra+(rright*light_mult))){
			  rright = 0;
			  robot_out = false;
		  }
	  }
	  else if(rdir > 315 || rdir <=45){
		  if(backUltra > (currUltra+(rback*light_mult))){
			  rback = 0;
			  robot_out = false;
		  }
	  }
	  if(leftUltra > 28){
		  rleft = 0;
	  }
	  if(frontUltra > 28){
		  rfront = 0;
		}
	  if(rightUltra > 28){
		  rright = 0;
	  }
	  if(backUltra > 28){
		  rback = 0;
	  }
	}
	else if(rfront>0 || rback>0 || rleft>0 || rright>0){
		timeLDR = millis();
		 robot_out = true; 
		if(rleft > 0 && rright > 0) rdir = 180; 
    	else if(rright > 0) rdir = 270;
    	else if(rleft > 0) rdir = 90;
    	else if(rfront > 0) rdir = 180;
    	else if(rback > 0) rdir = 0;
	  if(rdir > 45 && rdir <= 135){
		  currUltra = leftUltra;
	  }
	  else if(rdir > 135 && rdir <=225){
		  currUltra = frontUltra;
	  }
	  else if(rdir > 225 && rdir <=315){
		  currUltra = rightUltra;
	  }
	  else if(rdir > 315 || rdir <=45){
		  currUltra = backUltra;
	  }
	}
	else robot_out = false;
	return robot_out;
}
void out_2(){
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
	newlight[0] = analogRead(LDR_FL);
	newlight[1] = analogRead(LDR_FR);
	newlight[2] = analogRead(LDR_LI);
	newlight[3] = analogRead(LDR_LM);
	newlight[4] = analogRead(LDR_LO);
	newlight[5] = analogRead(LDR_RI);
	newlight[6] = analogRead(LDR_RM);
	newlight[7] = analogRead(LDR_RO);
	newlight[8] = analogRead(LDR_BIL);
	newlight[9] = analogRead(LDR_BIR);
	newlight[10] = analogRead(LDR_BOL);
	newlight[11] = analogRead(LDR_BOR);
	newlight[12] = analogRead(LDR_GATE);
	Serial.print(FL);
	Serial.print(" ");
		Serial.print(FR);
	Serial.print(" ");
		Serial.print(LI);
	Serial.print(" ");
		Serial.print(LM);
	Serial.print(" ");
		Serial.print(LO);
	Serial.print(" ");
		Serial.print(RI);
	Serial.print(" ");
		Serial.print(RM);
	Serial.print(" ");
		Serial.print(RO);
	Serial.print(" ");
		Serial.print(FL);
	Serial.print(" ");
		Serial.print(BIL);
	Serial.print(" ");
		Serial.print(BIR);
	Serial.print(" ");
		Serial.print(BOL);
	Serial.print(" ");
		Serial.print(BOR);
	Serial.println(" ");
	for(int i=0; i<13; i++){
		Serial.print(newlight[i]/oldlight[i]);
		Serial.print(" ");
		oldlight[i] = newlight[i];
	}
	Serial.println();
}
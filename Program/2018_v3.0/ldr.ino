bool Light_Gate(){
  if (analogRead(LDR_GATE)<GATE_Threshold) return true;
  else return false;
}
bool checkLDR(){
	readUltra();
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
	if ((FL>FL_threshold  || FR>FR_threshold) && (frontUltra < thresholdUltra)) rfront = 1;
	if(backUltra < thresholdUltra){
	if (BOL>BOL_threshold || BOR>BOR_threshold) rback = 1;
	else if (BIL>BIL_threshold || BIR>BIR_threshold) rback = 2;
	}
	if(leftUltra < thresholdUltra){
	if (LO>LO_threshold) rleft = 1;
	else if (LM>LM_threshold) rleft = 2;
	else if (LI>LI_threshold) rleft = 3;
	}
	if(rightUltra < thresholdUltra){
	if (RO>RO_threshold) rright = 1;
	else if (RM>RM_threshold) rright = 2;
	else if (RI>RI_threshold) rright = 3;
	}
	if(robot_out){
	  //if(rleft == 1 || rright == 1) robot_out = false;
	  if(rdir > 45 && rdir <= 135){
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
	  if(leftUltra > thresholdUltra){
		  rleft = 0;
	  }
	  if(frontUltra > thresholdUltra){
		  rfront = 0;
		}
	  if(rightUltra > thresholdUltra){
		  rright = 0;
	  }
	  if(backUltra > thresholdUltra){
		  rback = 0;
	  }
	  //if(rfront==0 || rback==0 || rleft==0 || rright==0) robot_out = false;
	  //else robot_out = true;
	}
	else if(rfront>0 || rback>0 || rleft>0 || rright>0){
		 robot_out = true; 
    	if(rright > 0) rdir = 270;
    	else if(rleft > 0) rdir = 90;
    	else if(rfront > 0) rdir = 180;
    	else if(rback > 0) rdir = 0;
	  if(rdir > 45 && rdir <= 135){
		  fieldside = 'l';
		  currUltra = leftUltra;
	  }
	  else if(rdir > 135 && rdir <=225){
		  currUltra = frontUltra;
	  }
	  else if(rdir > 225 && rdir <=315){
		  fieldside = 'r';
		  currUltra = rightUltra;
	  }
	  else if(rdir > 315 || rdir <=45){
		  currUltra = backUltra;
	  }
	}
	else robot_out = false;
	return robot_out;
}

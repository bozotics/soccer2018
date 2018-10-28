bool Light_Gate(){
  if (analogRead(LDR_GATE)<GATE_Threshold) return true;
  else return false;
}
bool LDR_check(){
	lightcnt++;
	if(lightcnt>100){
		lightcnt=0;
		prevfront = false;
		prevback = false;
	}
	rfront = 0, rleft = 0, rright = 0, rback = 0;
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
	if ((FL>FL_threshold  || FR>FR_threshold) && (ultraFront < ultraThreshold)) rfront = 1;
	if(ultraBack < ultraThreshold){
	if (BOL>BOL_threshold || BOR>BOR_threshold) rback = 1;
	else if (BIL>BIL_threshold || BIR>BIR_threshold) rback = 2;
	}
	if(ultraLeft < ultraThreshold){
	if (LI>LI_threshold) rleft = 1;
	else if (LM>LM_threshold) rleft = 2;
	else if (LO>LO_threshold) rleft = 3;
	}
	if(ultraRight < ultraThreshold){
	if (RI>RI_threshold) rright = 1;
	else if (RM>RM_threshold) rright = 2;
	else if (RO>RO_threshold) rright = 3;
	}
	if (rleft>0&&rright>0) {
		if (prevfront){ 
			rfront = 3;
     		rleft = 0;
     		rright =  0;
		}
		if (prevback){
			rback = 3;
      		rleft = 0;
      		rright = 0;
		}
	}
	if(rfront>0 || rback>0 || rleft>0 || (rright>0 && !robot_out)){
		 robot_out = true; 
	  if(rfront > 0){
			lightcnt = 0;
			prevfront = true;
			prevback = false;
  	  if(rleft > 0) rdir = 135;
    	else if(rright > 0) rdir = 225;
  	}
  	else if(rback > 0){
			lightcnt = 0;
			prevback = true;
			prevfront = false;
    	if(rleft > 0) rdir = 45;
    	else if(rright > 0) rdir = 315;
  	}
  	else{
    	if(rright > 0) rdir = 270;
    	else if(rleft > 0) rdir = 90;
    	else if(rfront > 0) rdir = 180;
    	else if(rback > 0) rdir = 0;
  	}
	  if(rdir > 45 && rdir <= 135){
		  fieldside = 'l';
		  currUltra = ultraLeft;
	  }
	  else if(rdir > 135 && rdir <=225){
		  currUltra = ultraBack;
	  }
	  else if(rdir > 225 && rdir <=315){
		  fieldside = 'r';
		  currUltra = ultraRight;
	  }
	  else{
		  currUltra = ultraFront;
	  }
	}
	else if(robot_out){
		if(rdir > 45 && rdir <= 135){
		  if((ultraLeft > (currUltra+rleft*light_mult)) || ultraLeft > 40){
			  robot_out = false;
		  }
	  }
	  else if(((rdir > 135 && rdir <=225)) || ultraBack > 40){
		  if(ultraBack > (currUltra+rback*light_mult)){
			  robot_out = false;
		  }
	  }
	  else if(rdir > 225 && rdir <=315){
		  if((ultraRight > (currUltra+rright*light_mult)) || ultraRight > 40){
			  robot_out = false;
		  }
	  }
	  else{
		  if((ultraFront > (currUltra+rfront*light_mult)) || ultraFront > 40){
			  robot_out = false;
		  }
	  }
	}
	return robot_out;
}


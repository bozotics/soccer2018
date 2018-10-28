void Light_Gate(){
  
}
void LDR_check(){
	rfront=0, rleft=0, rright=0, rback=0;
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
	if (FL>FL_threshold  || FR>FR_threshold) rfront = 1;
	if (BOL>BOL_threshold || BOR>BOR_threshold) rback = 1;
	else if (BIL>BIL_threshold || BIR>BIR_threshold) rback = 2;
	if (LI>LI_threshold) rleft = 1;
	else if (LM>LM_threshold) rleft = 2;
	else if (LO>LO_threshold) rleft = 3;
	if (RI>RI_threshold) rright = 1;
	else if (RM>RM_threshold) rright = 2;
	else if (RO>RO_threshold) rright = 3;
	/*if (rleft>0&&rright>0) {
		if (prevfront){ 
		 rfront = 3;
     rleft = 0;
     rrigth =  0;
		}
		if (prevback){
		  rback = 3;
      rleft = 0;
      rright = 0;
		}
	}*/
	if(!rfront || !rback || !rleft || !rright) robot_out = false; 
  if(rfront > 0){
    if(rleft > 0) dir = 135;
    else if(rright > 0) dir = 225;
  }
  else if(rback > 0){
    if(rleft > 0) dir = 45;
    else if(rright > 0) dir = 315;
  }
  else{
    if(rright > 0) dir = 270;
    else if(rleft > 0) dir = 90;
    else if(rfront > 0) dir = 180;
    else if(rback > 0) dir = 0;
  }
}


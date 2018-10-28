/*  //test LDR
 *  FL = analogRead(LDR_FL);
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
    Serial.print("FL  Min: "); Serial.print(FL_min); Serial.print(" Max: "); Serial.print(FL_max); Serial.print(" Threshold: "); Serial.println((FL_min+FL_max)/2);
    Serial.print("FR  Min: "); Serial.print(FR_min); Serial.print(" Max: "); Serial.print(FR_max); Serial.print(" Threshold: "); Serial.println((FR_min+FR_max)/2);
    Serial.print("LI  Min: "); Serial.print(LI_min); Serial.print(" Max: "); Serial.print(LI_max); Serial.print(" Threshold: "); Serial.println((LI_min+LI_max)/2);
    Serial.print("LM  Min: "); Serial.print(LM_min); Serial.print(" Max: "); Serial.print(LM_max); Serial.print(" Threshold: "); Serial.println((LM_min+LM_max)/2);
    Serial.print("FO  Min: "); Serial.print(LO_min); Serial.print(" Max: "); Serial.print(LO_max); Serial.print(" Threshold: "); Serial.println((LO_min+LO_max)/2);
    Serial.print("RI  Min: "); Serial.print(RI_min); Serial.print(" Max: "); Serial.print(RI_max); Serial.print(" Threshold: "); Serial.println((RI_min+RI_max)/2);
    Serial.print("RM  Min: "); Serial.print(RM_min); Serial.print(" Max: "); Serial.print(RM_max); Serial.print(" Threshold: "); Serial.println((RM_min+RM_max)/2);
    Serial.print("RO  Min: "); Serial.print(RO_min); Serial.print(" Max: "); Serial.print(RO_max); Serial.print(" Threshold: "); Serial.println((RO_min+RO_max)/2);
    Serial.print("BIL  Min: "); Serial.print(BIL_min); Serial.print(" Max: "); Serial.print(BIL_max); Serial.print(" Threshold: "); Serial.println((BIL_min+BIL_max)/2);
    Serial.print("BIR  Min: "); Serial.print(BIR_min); Serial.print(" Max: "); Serial.print(BIR_max); Serial.print(" Threshold: "); Serial.println((BIR_min+BIR_max)/2);
    Serial.print("BOL  Min: "); Serial.print(BOL_min); Serial.print(" Max: "); Serial.print(BOL_max); Serial.print(" Threshold: "); Serial.println((BOL_min+BOL_max)/2);
    Serial.print("BOR  Min: "); Serial.print(BOR_min); Serial.print(" Max: "); Serial.print(BOR_max); Serial.print(" Threshold: "); Serial.println((BOR_min+BOR_max)/2);
    Serial.println();
}
 */

 /* //test movement
  * Serial.println(cmps_angle);
    Serial.print(bl_pwm);
    Serial.print(" ");
    Serial.print(br_pwm);
    Serial.print(" ");
    Serial.print(fl_pwm);
    Serial.print(" ");
    Serial.println(fr_pwm);
  */

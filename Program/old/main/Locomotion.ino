void setmove(int spd, float dir) {
  int NSEW = 0;
  int SmotorFLO=0, SmotorFRO=0, SmotorBLO=0, SmotorBRO=0;
  float compensation = 0;
  float compensationi = 0;
  float compensationd = 0;
  float speedincreaseratio = 0;
  if(dir<=90){
    NSEW=1;
  }
  else if(dir<=180){
    NSEW=2;
  }
  else if(dir<=270){
    NSEW=3;
  }
  else{
    NSEW=4;
  }
    float csin=0.57, radn1=3.141592654*(dir-38)/180, radn2=3.141592654*(dir+38)/180;
float a=0, b=0;
  a=0.5*cos(radn1)/csin*spd;
  b=0.5*cos(radn2)/csin*spd;
  if (abs(a)>abs(b)){
    speedincreaseratio = spd/a;
    a = spd;
   /*Serial.print(speedincreaseratio);
   Serial.print(" ");
    Serial.print(a);*/
    b = b*speedincreaseratio;
  }
  else {
    speedincreaseratio = spd/b;
    b = spd;
    /*Serial.print(speedincreaseratio);
    Serial.print(" ");
    Serial.print(a);*/
    a = a*speedincreaseratio;
  }
  /*Serial.print(a);Serial.print(" ");Serial.print(b);Serial.println(" ");*/
  if (NSEW == 1) {
    SmotorFLO = -a;
    SmotorFRO = -b;
    SmotorBLO = -b;
    SmotorBRO = -a;
  }
  
  else if (NSEW == 2) {
    SmotorFLO = a;
    SmotorFRO = b;
    SmotorBLO = b;
    SmotorBRO = a; 
  }
  
  else if (NSEW == 3) {
    SmotorFLO = a;
    SmotorFRO = b;
    SmotorBLO = b;
    SmotorBRO = a;
  }
  
  else if(NSEW == 4) {
    SmotorFLO = -a;
    SmotorFRO = -b;
    SmotorBLO = -b;
    SmotorBRO = -a;
    
  }
  /*Serial.print(" ");
  Serial.print(NSEW);
  Serial.print(" "); 
  
  Serial.println(cmpsangle);
  Serial.print(" ");*/
  if(cmpsangle>0&&cmpsangle<=180){
    //Serial.print("compensate c clock");
    compensation=cmpsangle*compensationmult/180;
    compensationi=(100+compensation)/100;
    compensationd=(100-compensation)/100;
    if(SmotorFLO>0){
      SmotorFLO=SmotorFLO*compensationi;
    }
    else{
      SmotorFLO=SmotorFLO*compensationd;
    }
    if(SmotorFRO>0){
      SmotorFRO=SmotorFRO*compensationd;
    }
    else{
      SmotorFRO=SmotorFRO*compensationi;
    }
    if(SmotorBLO>0){
      SmotorBLO=SmotorBLO*compensationi;
    }
    else{
      SmotorBLO=SmotorBLO*compensationd;
    }
     if(SmotorBRO>0){
      SmotorBRO=SmotorBRO*compensationd;
    }
    else{
      SmotorBRO=SmotorBRO*compensationi;
    }
  }
  if(cmpsangle<360&&cmpsangle>180){
    //Serial.print("compensate clock");
    compensation=(360-cmpsangle)*compensationmult/180;
    compensationi=(compensation+100)/100;
    compensationd=(100-compensation)/100;
     if(SmotorFLO>0){
      SmotorFLO=SmotorFLO*compensationd;
    }
    else{
      SmotorFLO=SmotorFLO*compensationi;
    }
     if(SmotorFRO>0){
      SmotorFRO=SmotorFRO*compensationi;
    }
    else{
      SmotorFRO=SmotorFRO*compensationd;
    }
     if(SmotorBLO>0){
      SmotorBLO=SmotorBLO*compensationd;
    }
    else{ 
      SmotorBLO=SmotorBLO*compensationi;
    }
     if(SmotorBRO>0){
      SmotorBRO=SmotorBRO*compensationi;
    }
    else{
      SmotorBRO=SmotorBRO*compensationd;
    }
  }
  /*Serial.print(SmotorFLO);
    Serial.print(' ');
    Serial.print(SmotorFRO);
    Serial.print(' ');
    Serial.print(SmotorBLO);
    Serial.print(' ');
    Serial.println(SmotorBRO);*/
   float term1 = 49.536, term2 = 112.24, e =  2.718;
  SmotorFL = pow(e,(abs(SmotorFLO)+term2)/term1);
  SmotorFR = pow(e,(abs(SmotorFRO)+term2)/term1);
  SmotorBL = pow(e,(abs(SmotorBLO)+term2)/term1);
  SmotorBR = pow(e,(abs(SmotorBRO)+term2)/term1);

  if (SmotorFLO == 0){
    SmotorFL=0;
  }
  if (SmotorFRO == 0){
    SmotorFR=0;
  }
  if (SmotorBLO == 0){
    SmotorBL=0;
  }
  if (SmotorBRO == 0){
    SmotorBR=0;
  }
  if(SmotorFL>maxspeed){
    SmotorFL=maxspeed;
  }
  if(SmotorFR>maxspeed){
    SmotorFR=maxspeed;
  }
  if(SmotorBL>maxspeed){
    SmotorBL=maxspeed;
  }
  if(SmotorBR>maxspeed){
    SmotorBR=maxspeed;
  }
  if (SmotorFLO<0) {
    SmotorFL = -SmotorFL;
  }
  if (SmotorFRO<0) {
    SmotorFR = -SmotorFR;
  }
  if (SmotorBLO<0) {
    SmotorBL = -SmotorBL;
  }
  if (SmotorBRO<0) {
    SmotorBR = -SmotorBR;
  }
  checkout();
  }

void outmove(int spd, float dir) {
  int NSEW = 0;
  int SmotorFLO=0, SmotorFRO=0, SmotorBLO=0, SmotorBRO=0;
  float compensation = 0;
  float compensationi = 0;
  float compensationd = 0;
  float speedincreaseratio = 0;
  if(dir<=90){
    NSEW=1;
  }
  else if(dir<=180){
    NSEW=2;
  }
  else if(dir<=270){
    NSEW=3;
  }
  else{
    NSEW=4;
  }
    float csin=0.57, radn1=3.141592654*(dir-38)/180, radn2=3.141592654*(dir+38)/180;
float a=0, b=0;
  a=0.5*cos(radn1)/csin*spd;
  b=0.5*cos(radn2)/csin*spd;
  if (abs(a)>abs(b)){
    speedincreaseratio = spd/a;
    a = spd;
   /*Serial.print(speedincreaseratio);
   Serial.print(" ");
    Serial.print(a);*/
    b = b*speedincreaseratio;
  }
  else {
    speedincreaseratio = spd/b;
    b = spd;
    /*Serial.print(speedincreaseratio);
    Serial.print(" ");
    Serial.print(a);*/
    a = a*speedincreaseratio;
  }
  /*Serial.print(a);Serial.print(" ");Serial.print(b);Serial.println(" ");*/
  if (NSEW == 1) {
    SmotorFLO = -a;
    SmotorFRO = -b;
    SmotorBLO = -b;
    SmotorBRO = -a;
  }
  
  else if (NSEW == 2) {
    SmotorFLO = a;
    SmotorFRO = b;
    SmotorBLO = b;
    SmotorBRO = a; 
  }
  
  else if (NSEW == 3) {
    SmotorFLO = a;
    SmotorFRO = b;
    SmotorBLO = b;
    SmotorBRO = a;
  }
  
  else if(NSEW == 4) {
    SmotorFLO = -a;
    SmotorFRO = -b;
    SmotorBLO = -b;
    SmotorBRO = -a;
    
  }
  /*Serial.print(" ");
  Serial.print(NSEW);
  Serial.print(" "); 
  
  Serial.println(cmpsangle);
  Serial.print(" ");*/
  if(cmpsangle>0&&cmpsangle<=180){
    //Serial.print("compensate c clock");
    compensation=cmpsangle*compensationmult/180;
    compensationi=(100+compensation)/100;
    compensationd=(100-compensation)/100;
    if(SmotorFLO>0){
      SmotorFLO=SmotorFLO*compensationi;
    }
    else{
      SmotorFLO=SmotorFLO*compensationd;
    }
    if(SmotorFRO>0){
      SmotorFRO=SmotorFRO*compensationd;
    }
    else{
      SmotorFRO=SmotorFRO*compensationi;
    }
    if(SmotorBLO>0){
      SmotorBLO=SmotorBLO*compensationi;
    }
    else{
      SmotorBLO=SmotorBLO*compensationd;
    }
     if(SmotorBRO>0){
      SmotorBRO=SmotorBRO*compensationd;
    }
    else{
      SmotorBRO=SmotorBRO*compensationi;
    }
  }
  if(cmpsangle<360&&cmpsangle>180){
    //Serial.print("compensate clock");
    compensation=(360-cmpsangle)*compensationmult/180;
    compensationi=(compensation+100)/100;
    compensationd=(100-compensation)/100;
     if(SmotorFLO>0){
      SmotorFLO=SmotorFLO*compensationd;
    }
    else{
      SmotorFLO=SmotorFLO*compensationi;
    }
     if(SmotorFRO>0){
      SmotorFRO=SmotorFRO*compensationi;
    }
    else{
      SmotorFRO=SmotorFRO*compensationd;
    }
     if(SmotorBLO>0){
      SmotorBLO=SmotorBLO*compensationd;
    }
    else{ 
      SmotorBLO=SmotorBLO*compensationi;
    }
     if(SmotorBRO>0){
      SmotorBRO=SmotorBRO*compensationi;
    }
    else{
      SmotorBRO=SmotorBRO*compensationd;
    }
  }
  /*Serial.print(SmotorFLO);
    Serial.print(' ');
    Serial.print(SmotorFRO);
    Serial.print(' ');
    Serial.print(SmotorBLO);
    Serial.print(' ');
    Serial.println(SmotorBRO);*/
   float term1 = 49.536, term2 = 112.24, e =  2.718;
  SmotorFL = pow(e,(abs(SmotorFLO)+term2)/term1);
  SmotorFR = pow(e,(abs(SmotorFRO)+term2)/term1);
  SmotorBL = pow(e,(abs(SmotorBLO)+term2)/term1);
  SmotorBR = pow(e,(abs(SmotorBRO)+term2)/term1);

  if (SmotorFLO == 0){
    SmotorFL=0;
  }
  if (SmotorFRO == 0){
    SmotorFR=0;
  }
  if (SmotorBLO == 0){
    SmotorBL=0;
  }
  if (SmotorBRO == 0){
    SmotorBR=0;
  }
  if(SmotorFL>maxspeed){
    SmotorFL=maxspeed;
  }
  if(SmotorFR>maxspeed){
    SmotorFR=maxspeed;
  }
  if(SmotorBL>maxspeed){
    SmotorBL=maxspeed;
  }
  if(SmotorBR>maxspeed){
    SmotorBR=maxspeed;
  }
  if (SmotorFLO<0) {
    SmotorFL = -SmotorFL;
  }
  if (SmotorFRO<0) {
    SmotorFR = -SmotorFR;
  }
  if (SmotorBLO<0) {
    SmotorBL = -SmotorBL;
  }
  if (SmotorBRO<0) {
    SmotorBR = -SmotorBR;
  }
  }


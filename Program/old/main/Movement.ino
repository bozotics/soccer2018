void returnbase(){
  int rangeL=getRangeL(), rangeB=getRangeB(), rangeR=getRangeR();
  if(rangeB>60){
    setmove(70, 180);
  }
  else if(rangeB<30){
    setmove(70, 0);
  }
  else if(rangeR<70){
    setmove (70, 271);
  }
  else if(rangeL<75){
    setmove (70, 91);
  }
  else if(rangeB>40){
    setmove(70, 180);
  }
  else{
    setmove(0, 0);
  }
}
void checkout(){
  int rangeL=getRangeL(), rangeB=getRangeB(), rangeR=getRangeR();
  if(((rangeL+rangeR)<leeway || rangeL==200 || rangeR==200) && (rangeB>120)) {outmove(150, 180); out=true;}
  else if((rangeL+rangeR)<leeway || rangeL==200 || rangeR==200) {outmove(150, 0); out=true;}
  else if(rangeL<45 && ((rangeB>110 && rangeL<40) || rangeR>115)) {outmove(100, 91); out=true;}
  else if(rangeR<45 && ((rangeB>110 && rangeR<40) || rangeL>115)) {outmove(100, 271); out=true;}
}
void trackball(){
  int rangeL=getRangeL(), rangeB=getRangeB(), rangeR=getRangeR();
  Serial.print(rangeB);
  Serial.print(" ");
  Serial.print(rangeL);
  Serial.print(" ");
  Serial.println(rangeR);
  Serial.println(IRdir);
  Serial.println(IRstr);
  if(IRFB == 0){
    if(IRdir == 4){
      if(IRstr > IRspeed){
      if((rangeL>70)||(rangeR>70)){
        maxspeed=120;
      setmove(125, 0);
      } 
      /*else if(rangeL<70){
        maxspeed=120;
        setmove(125, 30);
      }
      else if(rangeR<70){
        maxspeed = 120;
        setmove(125, 330);
      }*/
      }
      else{
        setmove(100, 0);
      }
    }
    if(IRdir == 3){
      IRthreshold = 90;
      if(IRstr > IRspeed){
      if((rangeL>70)||(rangeR>70)){
        maxspeed=120;
      setmove(125, 0);
      } 
      /*else if(rangeL<60){
        maxspeed=120;
        setmove(125, 30);
      }
      else if(rangeR<60){
        maxspeed = 120;
        setmove(125, 330);
      }*/
      }
      else{
        if(IRstr < IRthreshold){
        setmove(100, 320);
      }
      else setmove(100, 340);
      }
    }
    else if(IRdir == 5){
      IRthreshold = 90;
       if(IRstr > IRspeed){
      if((rangeL>60)||(rangeR>60)){
        maxspeed=120;
      setmove(125, 0);
      } 
      /*else if(rangeL<60){
        maxspeed=120;
        setmove(125,30);
      }
      else if(rangeR<60){
        maxspeed = 120;
        setmove(125, 330);
      }*/
      }
      else{
      if(IRstr < IRthreshold){
        setmove(100, 20);
      }
      else setmove(100,90);
    }
    }
    else if(IRdir == 2){
      IRthreshold = 70;
      if(IRstr < IRthreshold){
        setmove(100, 285);
      }
      else setmove(100, 250);
    }
    else if(IRdir == 6){
      IRthreshold = 70;
      if(IRstr < IRthreshold){
        setmove(100, 50);
      }
      else setmove(100, 120);
    }
    else if(IRdir == 1){ //curveball
      IRthreshold = 90;
      if(IRstr < IRthreshold){
        setmove(100, 250);
      }
      else setmove(100, 170);
    }
    else if(IRdir == 7){ //curveball
      IRthreshold = 90;
      if(IRstr < IRthreshold){
        setmove(100, 110);
      }
      else setmove(100, 170);
    }
  }
  else if(IRFB == 1){
    if(IRdir == 4){
      IRthreshold=100;
      if(IRstr < IRthreshold){
        setmove(100, 135);
      }
      else{
        setmove(90, 95);
      }
    }
    else if(IRdir == 3){
      IRthreshold = 95;
      if(IRstr > IRthreshold){
        setmove(100, 150);
      }
      else setmove(100, 255);
    }
    else if(IRdir == 5){
      IRthreshold = 80;
      if(IRstr > IRthreshold){
        setmove(100, 210);
      }
      else setmove(100,130);
    }
    else if(IRdir == 2){
      IRthreshold = 80;
      if(IRstr > IRthreshold){
        setmove(100, 160);
      }
      else setmove(100, 250);
    }
    else if(IRdir == 6){
      IRthreshold = 80;
      if(IRstr > IRthreshold){
        setmove(100, 190);
      }
      else setmove(100, 150);
    }
    else if(IRdir == 1){ //curveball
      IRthreshold = 70;
      if(IRstr > IRthreshold){
        setmove(100, 180);
      }
      else setmove(100, 260);
    }
    else if(IRdir == 7){ //curveball
      IRthreshold = 60;
      if(IRstr > IRthreshold){
        setmove(100, 180);
      }
      else setmove(100, 170);
    }
  }
}


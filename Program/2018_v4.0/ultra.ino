void readUltra(){
    getAngle = readCmps();
    retrieveUltra();
    if(tfrontUltra > 0){
        frontUltra = tfrontUltra;
        if(fabsf(getAngle) > 5){
            frontUltra *= cosf(deg2rad(abs(getAngle)));
        }
    }
    else frontUltra = 255;
    if(tleftUltra > 0){
        leftUltra = tleftUltra;
        if(fabsf(getAngle) > 5){
            leftUltra *= cosf(deg2rad(abs(getAngle)));
        }
    }
    else leftUltra = 255;
    if(trightUltra > 0){
        rightUltra = trightUltra;
        if(fabsf(getAngle) > 5){
            rightUltra *= cosf(deg2rad(abs(getAngle)));
        }
    }
    else leftUltra = 255;            
    if(tbackUltra > 0){
        backUltra = tbackUltra;
        if(fabsf(getAngle) > 5){
            backUltra *= cosf(deg2rad(abs(getAngle)));
        }
    }
    else backUltra = 255;
}
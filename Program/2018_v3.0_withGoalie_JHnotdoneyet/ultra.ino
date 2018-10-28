void readUltra(){
    retrieveUltra();
    if(tfrontUltra > 0){
        frontUltra = tfrontUltra;
        if(fabsf(angleCmps) > 5){
            frontUltra *= cosf(deg2rad(abs(angleCmps)));
        }
    }
    if(tleftUltra > 0){
        leftUltra = tleftUltra;
        if(fabsf(angleCmps) > 5){
            leftUltra *= cosf(deg2rad(abs(angleCmps)));
        }
    }
    if(trightUltra > 0){
        rightUltra = trightUltra;
        if(fabsf(angleCmps) > 5){
            rightUltra *= cosf(deg2rad(abs(angleCmps)));
        }
    }
    if(tbackUltra > 0){
        backUltra = tbackUltra;
        if(fabsf(angleCmps) > 5){
            backUltra *= cosf(deg2rad(abs(angleCmps)));
        }
    }
}
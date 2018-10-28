void checkUltra(){
    readUltra();
    if(tultraFront > 0){
        ultraFront = tultraFront;
        if(abs(cmps_angle) > 5){
            ultraFront *= cos(deg2rad(cmps_angle));
        }
    }
    if(tultraLeft > 0){
        ultraLeft = tultraLeft;
        if(abs(cmps_angle) > 5){
            ultraLeft *= cos(deg2rad(cmps_angle));
        }
    }
    if(tultraRight > 0){
        ultraRight = tultraRight;
        if(abs(cmps_angle) > 5){
            ultraRight *= cos(deg2rad(cmps_angle));
        }
    }
    if(tultraBack > 0){
        ultraBack = tultraBack;
        if(abs(cmps_angle) > 5){
            ultraBack *= cos(deg2rad(cmps_angle));
        }
    }
}
void ultraRead(){
	for (uint8_t i = 0; i < SONAR_NUM; i++) {
		if (millis() >= pingTimer[i]) { 
			pingTimer[i] += PING_INTERVAL * SONAR_NUM;
			if (i == 0 && currentSensor == SONAR_NUM - 1){
				frontUltra = cm[0];
				leftUltra = cm[1];
				rightUltra = cm[2];
				backUltra = cm[3];
			}
			sonar[currentSensor].timer_stop();
			currentSensor = i;
			cm[currentSensor] = 0;
			sonar[currentSensor].ping_timer(echoCheck);
    	}
  	}
}

void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}


/*
ultra config:
  1
2   3
  4

5 trigger,2 echo
*/
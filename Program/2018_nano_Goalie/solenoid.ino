void solenoidKick(){
	if (received && receive == 1){
		digitalWrite(2,1);
		solenoidTimer = millis();
		kick = true;
	}
	if (received) received = false;
	if (kick){
		if (millis() >= solenoidTimer  + 70){
			digitalWrite(2, 0);
			kick = false;
		}
	}
}
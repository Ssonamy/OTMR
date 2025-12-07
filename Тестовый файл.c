task main(){
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	
	motor[motorB] = 100;
	motor[motorC] = 100;
	wait10Msec(1000);
}

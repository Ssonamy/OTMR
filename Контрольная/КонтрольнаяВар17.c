task main(){
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	
	// Доехать до начала:
	nSyncedMotors = synchBC;
	nSyncedTurnRatio = 100;
	
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 930;
	motor[motorB] = 50;
	while(nMotorRunState[motorB] != runStateIdle) {}
	motor[motorB] = 0;
	wait10Msec(100);
	
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 200;
	motor[motorB] = 50;
	while(nMotorRunState[motorB] != runStateIdle) {}
	motor[motorB] = 0;
	wait10Msec(100);
	
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 512;
	motor[motorB] = 50;
	while(nMotorRunState[motorB] != runStateIdle) {}
	motor[motorB] = 0;
	wait10Msec(100);
	
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 830;
	motor[motorB] = 50;
	while(nMotorRunState[motorB] != runStateIdle) {}
	motor[motorB] = 0;
	wait10Msec(100);
	
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 1300;
	motor[motorB] = 50;
	while(nMotorRunState[motorB] != runStateIdle) {}
	motor[motorB] = 0;
	wait10Msec(100);
	
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorB] = 1233;
	motor[motorB] = 50;
	while(nMotorRunState[motorB] != runStateIdle) {}
	motor[motorB] = 0;
}

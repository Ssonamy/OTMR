#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)

void waitAfterTask(){
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(500);
}

void forwardToStart(){
	nSyncedMotors = synchBC;
	nSyncedTurnRatio = 100;
	motor[motorB] = 50;
	wait1Msec(500);
	nSyncedMotors = synchNone;
}

// void movingForvardAlongLine(int value, int power = 50){
	// nMotorEncoder[motorB] = 0;
	// nMotorEncoder[motorC] = 0;

	// nSyncedMotors = synchBC;
	// nSyncedTurnRatio = 100;
	// motor[motorB] = power;
	// while (true){
		// if (SensorValue(lightSensor) > value){
			// motor[motorB] = 0;
			// wait1Msec(100);
			// nSyncedMotors = synchNone;
			// break;
		// }
	// }
// }

// void arcingForwardRightAlongLine(int value, int power = 50){
	// nMotorEncoder[motorB] = 0;
	// nMotorEncoder[motorC] = 0;

	// nSyncedMotors = synchCB;
	// nSyncedTurnRatio = 40;
	// motor[motorC] = power;
	// wait1Msec(100);
	// while (true){
		// if (SensorValue(lightSensor) > value){
			// motor[motorC] = 0;
			// wait1Msec(200);
			// nSyncedMotors = synchNone;
			// break;
		// }
	// }
// }
// void arcingForwardLeftAlongLine(int value, int power = 50){
	// nMotorEncoder[motorB] = 0;
	// nMotorEncoder[motorC] = 0;

	// nSyncedMotors = synchBC;
	// nSyncedTurnRatio = 40;
	// motor[motorB] = power;
	// wait1Msec(1200);
	// while (true){
		// if (SensorValue(lightSensor) > value){
			// motor[motorB] = 0;
			// wait1Msec(100);
			// nSyncedMotors = synchNone;
			// break;
		// }
	// }
// }

void followLineThresholdRange(int low, int high, int power = 40) {
	while (true) {
		int light = SensorValue(lightSensor);

		if (light < low) {
			// слишком темно — отклонение влево
			motor[motorB] = power - 10;
			motor[motorC] = power + 10;
		} else if (light > high) {
			// слишком светло — отклонение вправо
			motor[motorB] = power + 10;
			motor[motorC] = power - 10;
		} else {
			// середина диапазона — едем прямо
			motor[motorB] = power;
			motor[motorC] = power;
		}
	}
}


task main(){
	forwardToStart();
	followLineThresholdRange(55, 90);
}

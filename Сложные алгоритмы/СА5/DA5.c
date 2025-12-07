#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)
#pragma config(Sensor, S2,     gyroSensor,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)

float Kp = 0.5;
int targetAngle = 0;
int error, motorCorrection;
int gyroValue = SensorValue[gyroSensor];
#define BLACK_THRESHOLD 40

void turn180(int time) {
	motor[motorB] = 25;
	motor[motorC] = -25;
	wait1Msec(time);
}

void turnLeft90(int time) {
	motor[motorB] = -25;
	motor[motorC] = 25;
	wait1Msec(time);
}

void turnRight90(int time) {
	motor[motorB] = 25;
	motor[motorC]= -25;
	wait1Msec(time);

}


void moveForward(int angle, int speed) {
	while (true) {
		targetAngle = angle;
		gyroValue = SensorValue[gyroSensor];
		error = targetAngle - SensorValue[gyroSensor];
		motorCorrection = Kp * error;

		motor[motorB] = speed + motorCorrection;
		motor[motorC] = speed - motorCorrection;

		if (SensorValue[sonar] < 12) {
			motor[motorC] = 0;
			motor[motorB] = 0;
			break;
		}
	}
	targetAngle = 0;
}

void moveForward1(int angle, int speed, int duration) {
	clearTimer(T1);
	while (time1[T1] < duration) {
		targetAngle = angle;
		gyroValue = SensorValue[gyroSensor];
		error = targetAngle - SensorValue[gyroSensor];
		motorCorrection = Kp * error;
		motor[motorB] = speed + motorCorrection;
		motor[motorC] = speed - motorCorrection;
	}
	motor[motorB] = 0;
	motor[motorC] = 0;
	targetAngle = 0;
}

void waitForLine() {
	float Kp = 5.5;
	int baseSpeed = 100;
	int error;
	int motorCorrection;
	clearTimer(T1);

	while (time1[T1] < 13500) {
		error = 85 - SensorValue[lightSensor];
		motorCorrection = (int)(Kp * error);
		motor[motorB] = baseSpeed + motorCorrection;
		motor[motorC] = baseSpeed - motorCorrection;
	}

	motor[motorB] = 0;
	motor[motorC] = 0;
}


task main()
{
	turn180(1862);
	moveForward(1800,100);
	turnLeft90(931);
	moveForward(900,100);
	turnLeft90(931);
	moveForward(0,100);
	turnLeft90(931);
	moveForward(-900,100);
	turnRight90(931);
	moveForward(0,100);
	turnRight90(931);
	moveForward(900,100);
	turnLeft90(931);
	moveForward(0,100);
	turnLeft90(931);
	moveForward(-900,100);
	turnLeft90(931);
	moveForward(-1800,100);
	turnRight90(931);
	moveForward(-900,100);
	turnLeft90(931);
	moveForward(-1800,100);
	turnLeft90(931);
	moveForward(-2700,100);
	turnRight90(931);
	moveForward(-1800,100);
	turnRight90(931);
	moveForward(-900,100);
	turnLeft90(931);
	moveForward(-1800,100);
	turnLeft90(931);
	moveForward(-2700,100);
	turnRight90(931);
	moveForward(-1800,100);
	turnRight90(931);
	moveForward(-900,100);
	turnLeft90(931);
	moveForward(-1800,100);
	turnRight90(931);

	moveForward1(-900,50,900);
	clearTimer(T1);
	waitForLine();

	SensorValue[gyroSensor] = 0;
	moveForward(-900,100);
	turnLeft90(931);
	moveForward(-1800,100);
	turnRight90(931);
	moveForward(-900,100);
	turnRight90(931);
	moveForward(0,100);
	turnRight90(931);
	moveForward(900,100);
	turnRight90(931);
	moveForward1(1800,100,2200);
	turnRight90(931);
	moveForward(2700,100);
	turnRight90(931);
	moveForward(3600,100);
	turnLeft90(931);
	moveForward(2700,100);
	turnLeft90(931);
	moveForward(1800,100);
	turnLeft90(931);
	moveForward1(900,100,750);
	turnLeft90(931);
	moveForward(0,100);
}

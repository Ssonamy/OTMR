#pragma config(Sensor, S1, colorRight, sensorLightActive)
#pragma config(Sensor, S2, touch,      sensorTouch)
#pragma config(Sensor, S4, colorLeft,  sensorLightActive)
#pragma config(Motor,  motorC, leftMotor,  tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB, rightMotor, tmotorEV3_Large, PIDControl, encoder)

// 60 - w 
// 25 - b
// 32 - bl

#define SPEED 30
#define TURN_SPEED 25
#define LINE_THR 42     // подбирается!
#define BLUE_THR 46     // подбирается!

/* ===== БАЗА ===== */

void stopMotors() {
    motor[leftMotor] = 0;
    motor[rightMotor] = 0;
}

void moveForward(int d = 1) {
    motor[leftMotor] = SPEED * d;
    motor[rightMotor] = SPEED * d;
}

/* ===== ДО СТЕНЫ ПО TOUCH ===== */

void moveUntilTouch(int bd = 350) {
    moveForward();
    while(SensorValue[touch] == 0) {}
    stopMotors();
    sleep(200);
    moveForward(-1);
    sleep(bd);	
	stopMotors();
    sleep(200);
}

/* ===== ПОВОРОТЫ ===== */

void turnRight90(int d = 255) {
    resetMotorEncoder(leftMotor);
    resetMotorEncoder(rightMotor);
    motor[leftMotor] = TURN_SPEED;
    motor[rightMotor] = -TURN_SPEED;
    while(abs(getMotorEncoder(leftMotor)) < d) {}
    stopMotors();
    sleep(200);
}

void turnLeft90(int d = 255) {
    resetMotorEncoder(leftMotor);
    resetMotorEncoder(rightMotor);
    motor[leftMotor] = -TURN_SPEED;
    motor[rightMotor] = TURN_SPEED;
    while(abs(getMotorEncoder(rightMotor)) < d) {}
    stopMotors();
    sleep(200);
}

/* ===== ЛИНИЯ ===== */

void moveUntilLine() {
    moveForward();
    while(SensorValue[colorLeft] > LINE_THR &&
          SensorValue[colorRight] > LINE_THR) {}
    stopMotors();
    sleep(200);
}

void followLineUntilTouch(int bd = 255) {
    while(SensorValue[touch] == 0) {
        if(SensorValue[colorLeft] < LINE_THR) {
            motor[leftMotor] = SPEED - 10;
            motor[rightMotor] = SPEED + 5;
        }
        else if(SensorValue[colorRight] < LINE_THR) {
            motor[leftMotor] = SPEED + 5;
            motor[rightMotor] = SPEED - 10;
        }
        else {
            moveForward();
        }
    }
    stopMotors();
    sleep(200);
	moveForward(-1);
    sleep(bd);	
	stopMotors();
    sleep(200);
}

/* ===== СИНИЙ КВАДРАТ (ПО ЯРКОСТИ) ===== */

void moveUntilBlue() {

    if(SensorValue[colorLeft] > BLUE_THR ||
          SensorValue[colorRight] > BLUE_THR) {}
    stopMotors();
    sleep(200);
}

/* ===== MAIN ===== */

task main() {

    moveUntilTouch();

    turnRight90();
    moveUntilTouch();

    turnLeft90();
    moveUntilTouch(400);

    turnLeft90(265); // Ручная подстройка - прямая перед линией
	
    moveUntilTouch();
	turnRight90();
	
    followLineUntilTouch();
	turnRight90(265);
	
    moveUntilBlue(); // !!!! 
	moveForward(0.5);
	sleep(700);
    followLineUntilTouch();
	
    // turnRight90();
    // moveUntilTouch();

    turnLeft90();
    moveUntilTouch();

    turnLeft90();
    moveUntilLine();
    moveForward(); sleep(300); stopMotors();

    turnRight90();
    moveUntilTouch();

    turnRight90();
    moveUntilLine();
    moveForward(); sleep(300); stopMotors();

    turnLeft90();
    followLineUntilTouch();

    stopMotors();
}

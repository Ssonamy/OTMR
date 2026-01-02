#pragma config(Sensor, S1, colorRight, sensorLightActive)
#pragma config(Sensor, S2, touch,      sensorTouch)
#pragma config(Sensor, S4, colorLeft,  sensorLightActive)
#pragma config(Motor,  motorC, leftMotor,  tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB, rightMotor, tmotorEV3_Large, PIDControl, encoder)

// 45 - w 
// 20 - b
// 25 - bl 

#define SPEED 27
#define TURN_SPEED 25
#define LINE_THR 32     // подбирается!
#define BLUE_THR 36     // подбирается!

/* ===== БАЗА ===== */

void stopMotors() {
    motor[leftMotor] = 0;
    motor[rightMotor] = 0;
}

void moveForward(float d = 1) {
    motor[leftMotor] = SPEED * d;
    motor[rightMotor] = SPEED * d;
}

/* ===== ДО СТЕНЫ ПО TOUCH ===== */

void moveUntilTouch(int bd = 380) {
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

void turnRight90(int d = 205) {
    resetMotorEncoder(leftMotor);
    resetMotorEncoder(rightMotor);
    motor[leftMotor] = TURN_SPEED;
    motor[rightMotor] = -TURN_SPEED;
    while(abs(getMotorEncoder(leftMotor)) < d) {}
    stopMotors();
    sleep(200);
}

void turnLeft90(int d = 205) {
    resetMotorEncoder(leftMotor);
    resetMotorEncoder(rightMotor);
    motor[leftMotor] = -TURN_SPEED;
    motor[rightMotor] = TURN_SPEED;
    while(abs(getMotorEncoder(rightMotor)) < d) {}
    stopMotors();
    sleep(200);
}

/* ===== ЛИНИЯ ===== */

void followLineUntilTouch(int bd = 380, bool last = false, int timeMs = 2000) {

    // ===== РЕЖИМ 1: обычный — до нажатия touch =====
    if(!last) {
        while(SensorValue[touch] == 0) {
            if(SensorValue[colorLeft] < LINE_THR) {
                motor[leftMotor] = SPEED - 27;
                motor[rightMotor] = SPEED + 5;
            }
            else if(SensorValue[colorRight] < LINE_THR) {
                motor[leftMotor] = SPEED + 5;
                motor[rightMotor] = SPEED - 27;
            }
            else {
                moveForward();
            }
        }
    }
    // ===== РЕЖИМ 2: последний участок — по времени =====
    else {
        clearTimer(T1);
        while(time1[T1] < timeMs) {
            if(SensorValue[colorLeft] < LINE_THR) {
                motor[leftMotor] = SPEED - 27;
                motor[rightMotor] = SPEED + 5;
            }
            else if(SensorValue[colorRight] < LINE_THR) {
                motor[leftMotor] = SPEED + 5;
                motor[rightMotor] = SPEED - 27;
            }
            else {
                moveForward();
            }
        }
    }

    // ===== ОБЩИЙ ФИНИШ =====
    stopMotors();
    sleep(200);

	if (!last){
    // небольшой откат назад, как у тебя
	moveForward(-1);
    sleep(bd);
	}

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

    moveUntilTouch(410);

    turnRight90(206);
    moveUntilTouch(390);

    turnLeft90();
    moveUntilTouch(465);

    turnLeft90(210); // Ручная подстройка - прямая перед линией
	
    moveUntilTouch();
	turnRight90();
	
    followLineUntilTouch(485);
	turnRight90(206);

	
    moveUntilBlue(); // !!!! 
	
	moveForward(1.3);
	sleep(4200);
    followLineUntilTouch();
	
	
    turnRight90();
    followLineUntilTouch(380, true, 6230);
	
	moveUntilTouch();
	turnLeft90(213);
	moveUntilTouch();

    stopMotors();
}

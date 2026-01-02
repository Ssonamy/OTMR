#pragma config(Sensor, S3,     IRSeeker,       sensorI2CCustom)
#pragma config(Sensor, S4,     Compass,        sensorI2CCustom)
#pragma config(Motor,  motorB,          LeftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          RightMotor,    tmotorEV3_Large, PIDControl, encoder)

#include "hitechnic-irseeker-v2.h"

// IR Seeker структура
tHTIRS2 Seeker;

int goalieSpeed = 30;

void moveGoalie(int dir) {
    // Простейшая логика: если мяч слева, поворачиваем влево, если справа – вправо
    if(dir == 5) { // мяч прямо
        motor[LeftMotor]  = goalieSpeed;
        motor[RightMotor] = goalieSpeed;
    } else if(dir < 5) { // мяч слева
        motor[LeftMotor]  = -goalieSpeed;
        motor[RightMotor] = goalieSpeed;
    } else { // мяч справа
        motor[LeftMotor]  = goalieSpeed;
        motor[RightMotor] = -goalieSpeed;
    }
}

task main() {
    // Инициализация IR Seeker
    initSensor(&Seeker, S3);

    while(true) {
        if(readSensor(&Seeker)) {
            int dir = Seeker.enhDirection; // 1..9
            moveGoalie(dir);
        } else {
            // Если не видим мяч, стоим на месте
            motor[LeftMotor]  = 0;
            motor[RightMotor] = 0;
        }
        wait1Msec(50);
    }
}

#pragma config(Sensor, S3, lightFront, sensorLightActive)
#pragma config(Sensor, S2, sonarSensor, sensorSONAR)
#pragma config(Sensor, S1, lightBack, sensorLightActive)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, encoder)


#define LINE_THRESHOLD 55
#define ENEMY_DISTANCE 55
#define DRIVE_SPEED 60
#define TURN_SPEED 50
#define TURN_TIME 600   // время разворота (мс)

void stopMotors()
{
    motor[leftMotor] = 0;
    motor[rightMotor] = 0;
}

void rotateSearch()
{
    motor[leftMotor]  = TURN_SPEED;
    motor[rightMotor] = -TURN_SPEED;
}

void driveForward()
{
    motor[leftMotor]  = DRIVE_SPEED;
    motor[rightMotor] = DRIVE_SPEED;
}

void turnAround()
{
    motor[leftMotor]  = TURN_SPEED;
    motor[rightMotor] = -TURN_SPEED;
    wait1Msec(TURN_TIME);
    stopMotors();
}

bool frontOnLine()
{
    return SensorValue[lightFront] < LINE_THRESHOLD;
}

bool enemyDetected()
{
    return (SensorValue[sonarSensor] > 0 &&
            SensorValue[sonarSensor] < ENEMY_DISTANCE);
}

task main()
{
    clearTimer(T1);

    while (time1[T1] < 60000)   // 1 минута
    {
        // Проверка линии спереди — приоритет
        if (frontOnLine())
        {
            stopMotors();
            wait1Msec(100);
            turnAround();
            continue;
        }

        // Обнаружен противник
        if (enemyDetected())
        {
            driveForward();
        }
        else
        {
            rotateSearch();
        }

        wait1Msec(20); // защита от перегрузки CPU
    }

    stopMotors();
}

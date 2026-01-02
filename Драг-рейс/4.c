#pragma config(Sensor, S3, leftLight,  sensorLightActive)
#pragma config(Sensor, S2, rightLight, sensorLightActive)
#pragma config(Motor,  motorB, rightMotor, tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC, leftMotor,  tmotorEV3_Large, PIDControl, reversed, encoder)

const int threshold  = 47;
const int baseSpeed = 60;   // можно увеличивать
const float kP      = 3.2;  // коэффициент поворота

task main()
{
    int leftVal, rightVal;
    int error;
    int correction;

    while (true)
    {
        leftVal  = SensorValue[leftLight];
        rightVal = SensorValue[rightLight];

        // Финиш
        if (leftVal < threshold && rightVal < threshold)
            break;

        // Ошибка (ВАЖНО: порядок именно такой)
        error = leftVal - rightVal;

        correction = (int)(error * kP);

        motor[leftMotor]  = baseSpeed + correction;
        motor[rightMotor] = baseSpeed - correction;

        wait1Msec(5);   // критично для высокой скорости
    }

    motor[leftMotor]  = 0;
    motor[rightMotor] = 0;
}

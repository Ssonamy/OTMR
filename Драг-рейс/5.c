#pragma config(Sensor, S3, leftLight,  sensorLightActive)
#pragma config(Sensor, S2, rightLight, sensorLightActive)
#pragma config(Motor,  motorB, rightMotor, tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC, leftMotor,  tmotorEV3_Large, PIDControl, reversed, encoder)

const int threshold  = 47;
const int baseSpeed = 50;   // ← ВПЕРЁД при reversed
const float kP      = 1.7;   // ↓ понижен для устойчивости

task main()
{
    int leftVal, rightVal, error, correction;

    while (true)
    {
        leftVal  = SensorValue[leftLight];
        rightVal = SensorValue[rightLight];

        if (leftVal < threshold && rightVal < threshold) break;

        error = leftVal - rightVal;           // >0 → левый датчик темнее → линия СЛЕВА
        correction = (int)(error * kP);

        int leftPower  = baseSpeed - correction;   // замедлить левый при повороте влево
        int rightPower = baseSpeed + correction;   // ускорить правый

        // Ограничение
        if (leftPower > 100)  leftPower = 100;
        if (leftPower < -100) leftPower = -100;
        if (rightPower > 100) rightPower = 100;
        if (rightPower < -100) rightPower = -100;

        motor[leftMotor]  = leftPower;
        motor[rightMotor] = rightPower;

        wait1Msec(5);
    }

    motor[leftMotor] = motor[rightMotor] = 0;
    displayCenteredBigTextLine(3, "FINISHED!");
}
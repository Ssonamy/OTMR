#pragma config(Sensor, S2, irRight, sensorEV3_IRSensor)
#pragma config(Sensor, S3, colorLine, sensorEV3_Color)
#pragma config(Sensor, S4, irLeft,  sensorEV3_IRSensor)
#pragma config(Motor,  motorB, leftMotor,  tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC, rightMotor, tmotorEV3_Large, PIDControl, encoder)

task main()
{
    // ==== ПОРОГИ ====
    const int IR_RIGHT_DETECT = 40;
    const int IR_LEFT_DETECT  = 60;
    const int COLOR_BLACK     = 3;

    // ==== СКОРОСТИ ====
    const int ROTATE_SPEED = 15;
    const int DRIVE_FAST   = 35;
    const int DRIVE_SLOW   = 15;

    while(true)
    {
        // ===============================
        // 1. ПОИСК БАНКИ (вращение)
        // ===============================
        int detectCount = 0;

        motor[leftMotor]  =  ROTATE_SPEED;
        motor[rightMotor] = -ROTATE_SPEED;

        while(detectCount < 3)
        {
            if(SensorValue[irRight] < IR_RIGHT_DETECT ||
               SensorValue[irLeft]  < IR_LEFT_DETECT)
                detectCount++;
            else
                detectCount = 0;

            wait1Msec(30);
        }

        motor[leftMotor]  = 0;
        motor[rightMotor] = 0;
        wait1Msec(200);

        // ===============================
        // 2. СБРОС ЭНКОДЕРОВ
        // ===============================
        resetMotorEncoder(leftMotor);
        resetMotorEncoder(rightMotor);

        // ===============================
        // 3. БЫСТРО ЕДЕМ К БАНКЕ
        // ===============================
        motor[leftMotor]  = DRIVE_FAST;
        motor[rightMotor] = DRIVE_FAST;

        // пока далеко от банки
        while(SensorValue[irRight] > IR_RIGHT_DETECT &&
              SensorValue[irLeft]  > IR_LEFT_DETECT)
        {
        }

        // ===============================
        // 4. МЕДЛЕННЫЙ ПОДЪЕЗД (ВАЖНО!)
        // ===============================
        motor[leftMotor]  = DRIVE_SLOW;
        motor[rightMotor] = DRIVE_SLOW;

        wait1Msec(250); // аккуратный "удар"

        motor[leftMotor]  = 0;
        motor[rightMotor] = 0;
        wait1Msec(150);

        // ===============================
        // 5. ЕДЕМ ДО ЛИНИИ
        // ===============================
        motor[leftMotor]  = DRIVE_FAST;
        motor[rightMotor] = DRIVE_FAST;

        int blackCount = 0;
        while(blackCount < 2)
        {
            if(SensorValue[colorLine] <= COLOR_BLACK)
                blackCount++;
            else
                blackCount = 0;

            wait1Msec(20);
        }

        motor[leftMotor]  = 0;
        motor[rightMotor] = 0;
        wait1Msec(150);

        // ===============================
        // 6. СОХРАНЯЕМ ПРОЕХАННОЕ
        // ===============================
        int dist =
            (abs(getMotorEncoder(leftMotor)) +
             abs(getMotorEncoder(rightMotor))) / 2;

        // ===============================
        // 7. ВОЗВРАТ ПО ЭНКОДЕРАМ
        // ===============================
        resetMotorEncoder(leftMotor);
        resetMotorEncoder(rightMotor);

        motor[leftMotor]  = -DRIVE_FAST;
        motor[rightMotor] = -DRIVE_FAST;

        while(
            (abs(getMotorEncoder(leftMotor)) +
             abs(getMotorEncoder(rightMotor))) / 2 < dist
        )
        {
        }

        motor[leftMotor]  = 0;
        motor[rightMotor] = 0;
        wait1Msec(300);

        // ===============================
        // 8. ФИНАЛЬНАЯ ПРОВЕРКА 360°
        // ===============================
        resetMotorEncoder(leftMotor);
        resetMotorEncoder(rightMotor);

        bool anyBottle = false;

        motor[leftMotor]  = ROTATE_SPEED;
        motor[rightMotor] = -ROTATE_SPEED;

        while(abs(getMotorEncoder(leftMotor)) < 360)
        {
            if(SensorValue[irRight] < IR_RIGHT_DETECT ||
               SensorValue[irLeft]  < IR_LEFT_DETECT)
                anyBottle = true;
        }

        motor[leftMotor]  = 0;
        motor[rightMotor] = 0;

        if(!anyBottle)
            break; // все банки сбиты
    }

    // ===== СТОП =====
    motor[leftMotor]  = 0;
    motor[rightMotor] = 0;
}

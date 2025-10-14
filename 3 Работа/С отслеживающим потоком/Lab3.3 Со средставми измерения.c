#pragma config(Sensor, S2, gyro, sensorAnalogInactive)
// !!Использовал робота LEGO REMBot, все значения актуальны для него!!
// П-регулятор

void waitAfterTask(){
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(500);
}

void forward(float distance, int power = 70){
	int basePower = power;
	float Kp = 0.5;
	int target = ((distance * 30) / 17.6) * 360;	
	
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	
	while (abs(nMotorEncoder[motorB]) < target && abs(nMotorEncoder[motorC]) < target)
	{
		int error = nMotorEncoder[motorB] - nMotorEncoder[motorC];
		int correction = (int)(Kp * error);

		motor[motorB] = basePower - correction;
		motor[motorC] = basePower + correction;
	}
	waitAfterTask();
}

void rotation(int degrees, int dir = 1){
    float L = 116.0;   
    float D = 56.0;    
    int basePower = 36; 
    float Kp = 0.4;
    int target = (int)((L * degrees) / D + (0.5 * dir));

    SensorValue[S2] = 0;
	
    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;

	while ((abs(nMotorEncoder[motorB]) < target) && (abs(nMotorEncoder[motorC])) < target){
        int error = nMotorEncoder[motorB] + nMotorEncoder[motorC];
        int correction = (int)(Kp * error);
        motor[motorB] =  dir * (basePower - correction);
        motor[motorC] = -dir * (basePower - correction);
        wait1Msec(20);
    }
	waitAfterTask();
}

task MonitorTask(){
    static int lastEncoderB = 0;
    static int lastEncoderC = 0;
    static float speedB = 0;
    static float speedC = 0;
	static float angle = 0;
    const int interval = 100;

    wait1Msec(50);
	
    while(true){
        int currentB = nMotorEncoder[motorB];
        int currentC = nMotorEncoder[motorC];

        speedB = (currentB - lastEncoderB) / (interval / 1000.0);
        speedC = (currentC - lastEncoderC) / (interval / 1000.0);
		
		angle = SensorValue[S2];

        writeDebugStreamLine(
            "PowerB: %d | PowerC: %d | SpeedB: %.1f | SpeedC: %.1f | GyroAngle: %.1f",
            motor[motorB], motor[motorC], speedB, speedC, angle
        );

        lastEncoderB = currentB;
        lastEncoderC = currentC;

        wait1Msec(interval);
    }
}

// Функция, запускающая отслеживающий поток при езде прямо
void runForward(int distance, int power){
    startTask(MonitorTask, 50);
    forward(distance, power);
    stopTask(MonitorTask);
}

// Функция, запускающая отслеживающий поток при повороте
void runRotation(int degrees, int dir = 1){
    startTask(MonitorTask, 50);
    rotation(degrees, dir);
    stopTask(MonitorTask);
}

task main(){
	runForward(6, 100);
	runRotation(89);
	waitAfterTask();

	runForward(5.5, 70);	
	runRotation(88, -1);
	waitAfterTask();
	
	runForward(4, 70);	
	runRotation(88, -1);
	waitAfterTask();

	runForward(2, 100);
}

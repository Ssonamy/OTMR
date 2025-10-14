#pragma config(Sensor, S2, gyro, sensorAnalogInactive)
// !!Использовал робота LEGO REMBot, все значения актуальны для него!!
// Синхронизация моторов

void waitAfterTask()
{
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(500);
}

void forward(float distance, int power) 
{	
	int target = ((distance * 30) / 17.6) * 360;	
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	SensorValue[S2] = 0;

	nSyncedMotors = synchBC;
	nSyncedTurnRatio = 100;
	
	nMotorEncoderTarget[motorB] = target;
	
	motor[motorB] = power;
	
	while(nMotorRunState[motorB] != runStateIdle) {}
	nSyncedMotors = synchNone;
	waitAfterTask();
}


void rotation(int degrees)
{
    float L = 118.0;
    float D = 56.0;
	
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	
    int target = (int)((L * degrees) / D + 0.5);

    nSyncedMotors = synchBC;
    nSyncedTurnRatio = -100;

    nMotorEncoder[motorB] = 0;
    nMotorEncoderTarget[motorB] = target;

    motor[motorB] = 30;

    while(nMotorRunState[motorB] != runStateIdle) {}
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
void runRotation(int degrees){
    startTask(MonitorTask, 50);
    rotation(degrees);
    stopTask(MonitorTask);
}

task main()
{
	runForward(6, 70);
	runRotation(90);
	runForward(5.5, 70);	
	runRotation(-90);
	runForward(4, 70);	
	runRotation(-90);
	runForward(2, 100);
}
	
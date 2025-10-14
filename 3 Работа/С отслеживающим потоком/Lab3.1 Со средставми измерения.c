#pragma config(Sensor, S2, gyro, sensorAnalogInactive)
// !!Использовал робота LEGO REMBot, все значения актуальны для него!!
// Ручная подстройка


void waitAfterTask(int duration)
{
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(duration);
}

void rotation(int angle, bool isLeft = false)
{
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	int leftMultipler = 1;
	float angleMultipler = angle / 45;

	if (isLeft) leftMultipler *= -1;
	
	SensorValue[S2] = 0;
	
	motor[motorB] = -20;
	motor[motorC] = -20;
	wait1Msec(220);

	for (int i = 0; i < angleMultipler; i++)
	{
		motor[motorB] = -30 * leftMultipler;
		motor[motorC] =  30 * leftMultipler;

		wait1Msec(530);
	}
}

void movingForward(	int speed = 100, int duration = 320)
{
	nMotorEncoder[motorB]=0;
	nMotorEncoder[motorC]=0;
	motor[motorB] = speed;
	motor[motorC] = speed;
	wait10Msec(duration);
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
    movingForward(distance, power);
    stopTask(MonitorTask);
}

// Функция, запускающая отслеживающий поток при повороте
void runRotation(int degrees, bool dir = false){
    startTask(MonitorTask, 50);
    rotation(degrees, dir);
    stopTask(MonitorTask);
}

task main()
{

	runForward(90, 350);
	waitAfterTask(300);
	
	runRotation(90, true);
	waitAfterTask(300);

	runForward(90, 470);
	waitAfterTask(300);

	runRotation(120);
	waitAfterTask(300);

	runForward(90, 430);
	waitAfterTask(300);

	runRotation(90);
	waitAfterTask(300);

	runForward(100, 150);
	waitAfterTask(300);

}

// !!Использовал робота LEGO REMBot, все значения актуальны для него!!
// Синхронизация моторов

void waitAfterTask()
{
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(500);
}

void forward(float distance, int power) // Дистанция в маленьких клетках
{	
	int target = ((distance * 30) / 17.6) * 360;	

	nSyncedMotors = synchBC;
	nSyncedTurnRatio = 100;
	
	nMotorEncoder[motorB] = 0;
	
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

    int target = (int)((L * degrees) / D + 0.5);

    nSyncedMotors = synchBC;
    nSyncedTurnRatio = -100;

    nMotorEncoder[motorB] = 0;
    nMotorEncoderTarget[motorB] = target;

    motor[motorB] = 30;

    while(nMotorRunState[motorB] != runStateIdle) {}
    waitAfterTask();
}


task main()
{
	forward(6, 70);
	rotation(90);
	forward(5.5, 70);	
	rotation(-90);
	forward(4, 70);	
	rotation(-90);
	forward(2, 100);
}
	
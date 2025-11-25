// !!Использовал робота LEGO REMBot, все значения актуальны для него!!
// Ручная подстройка
void waitAfterTask(int duration = 500)
{
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(duration);
}

void rotation(int degrees, int dir = 1)
{
    float L = 118.0;
    float D = 56.0;

    int target = (int)((L * degrees) / D + 0.5);

    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;
    nMotorEncoderTarget[motorB] = target * dir;
    nMotorEncoderTarget[motorC] = -target * dir;

    motor[motorB] = 30 * dir;
    motor[motorC] = -30 * dir;
while(nMotorRunState[motorB] != runStateIdle) {}
    waitAfterTask();
}

void movingForward(	int speed = 100, int duration = 320)
{
	motor[motorB] = speed;
	motor[motorC] = speed;
	wait10Msec(duration);
}

task main()
{

	movingForward(90, 350);
	waitAfterTask(300);
	
	rotation(89);
	waitAfterTask(300);

	movingForward(90, 470);
	waitAfterTask(300);

	rotation(90, -1);
	waitAfterTask(300);

	movingForward(90, 500);
	waitAfterTask(300);

	rotation(90, -1);
	waitAfterTask(300);

	movingForward(100, 150);
	waitAfterTask(300);

}

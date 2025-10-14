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
	int leftMultipler = 1;
	float angleMultipler = angle / 45;

	if (isLeft) leftMultipler *= -1;

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
	motor[motorB] = speed;
	motor[motorC] = speed;
	wait10Msec(duration);
}

task main()
{

	movingForward(90, 350);
	waitAfterTask(300);
	
	rotation(90, true);
	waitAfterTask(300);

	movingForward(90, 470);
	waitAfterTask(300);

	rotation(120);
	waitAfterTask(300);

	movingForward(90, 430);
	waitAfterTask(300);

	rotation(90);
	waitAfterTask(300);

	movingForward(100, 150);
	waitAfterTask(300);

}

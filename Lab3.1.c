void waitAfterTask()
{
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(500);
}

void rotation(int angle, bool isLeft = false)
{
	int leftMultipler = 1, angleMultipler = angle / 45;

	if (isLeft) leftMultipler *= -1;

	motor[motorB] = -20;
	motor[motorC] = -20;
	wait1Msec(220);

	for (int i = 0; i < angleMultipler; i++)
	{
		motor[motorB] = -30 * leftMultipler;
		motor[motorC] =  30 * leftMultipler;

		wait10Msec(53);
	}
}

void movingForward(	int speed = 100, int duration = 320)
{
	motor[motorB] = speed;
	motor[motorC] = speed;
	wait10Msec(duration/2);
	
	motor[motorB] = speed - 1.7;
	motor[motorC] = speed;
	wait10Msec(duration/2);
	waitAfterTask();
}

task main()
{
	movingForward(100, 350);
	rotation(90, true);
	movingForward(100, 440);
	rotation(90);
	movingForward(100, 450);
	rotation(90);
	movingForward(100, 150);
}

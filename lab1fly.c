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

void movingForvard(int times = 1, int duration = 335)
{
	for (int i = 0; i < times; i++)
	{
		if (i % 2 != 0)
		{
			motor[motorB] = 50;
			motor[motorC] = 50;
			wait10Msec(duration);

			waitAfterTask();
		}

		else
		{
			motor[motorB] = 49;
			motor[motorC] = 50;
			wait10Msec(duration);

			waitAfterTask();
		}
	}
}

task main()
{
	rotation(90);
	waitAfterTask();

	movingForvard(4);
	waitAfterTask();

	rotation(90);
	waitAfterTask();

	movingForvard(2);
	waitAfterTask();

	rotation(90, true);
	waitAfterTask();

	movingForvard();
	waitAfterTask();
}

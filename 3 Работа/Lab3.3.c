// !!����������� ������ LEGO REMBot, ��� �������� ��������� ��� ����!!
// �-���������

void waitAfterTask(){
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(500);
}

void forward(float distance, int power = 70){
	// --- ������������� ��������� ---
	int basePower = power; // ������� �������� �������
	float Kp = 0.5;		   // ����������� ������������������ (�����������)
	
    // --- ������ �������� �������� �������� ---
	int target = ((distance * 30) / 17.6) * 360;	
	
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	
	while (abs(nMotorEncoder[motorB]) < target && 
				 abs(nMotorEncoder[motorC]) < target)
	{
		int error = nMotorEncoder[motorB] - nMotorEncoder[motorC];
		int correction = (int)(Kp * error);

		motor[motorB] = basePower - correction;
		motor[motorC] = basePower + correction;
	}
	waitAfterTask();
}

void rotation(int degrees, int dir = 1){
    float L = 116.0;   // ���������� ����� �������, ��
    float D = 56.0;    // ������� ������, ��
    int basePower = 36; // ������� �������� �������
	
    float Kp = 0.4;    // ����������� ������������������ (�����������)
	
    int target = (int)((L * degrees) / D + (0.5 * dir));

    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;

	while ((abs(nMotorEncoder[motorB]) < target)
	&& (abs(nMotorEncoder[motorC])) < target)
    {
        int error = nMotorEncoder[motorB] + nMotorEncoder[motorC];
        int correction = (int)(Kp * error);

        motor[motorB] =  dir * (basePower - correction);
        motor[motorC] = -dir * (basePower - correction);
        wait1Msec(20);
    }
	waitAfterTask();
}

task main(){
	forward(6, 100);
	rotation(87);
	waitAfterTask();

	forward(5.5, 70);	
	rotation(86, -1);
	waitAfterTask();
	
	forward(4, 70);	
	rotation(87, -1);
	waitAfterTask();


















	forward(2, 100);
}
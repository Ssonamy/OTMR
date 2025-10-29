// !!Использовал робота LEGO REMBot, все значения актуальны для него!!
// ПИД-регулятор

void waitAfterTask(){
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(500);
}

void forward(int distance, int power = 70){
	float Kp = 0.4;    	// Пропорциональный коэффициент
	float Ki = 0.01; 	// Интегральный
	float Kd = 0.4;		// Дифференциальный
	
	int basePower = power;
	int target = ((distance * 30) / 17.6) * 360;
	
	int error = 0;
	int prevError = 0;
	float sumError = 0;
	int correction = 0;

	// --- Сброс энкодеров ---
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
	
	// --- Основной цикл ---
	while ((abs(nMotorEncoder[motorB]) < target 
	&& (abs(nMotorEncoder[motorC])) < target))
	{
		error = nMotorEncoder[motorB] - nMotorEncoder[motorC];
		if(abs(error) < 3) error = 0;

		// Интегральная часть — накопление ошибки
		sumError += error;
		if(sumError > 100) sumError = 100;
		if(sumError < -100) sumError = -100;

		// Дифференциальная часть — изменение ошибки
		int deltaError = error - prevError;

		// Расчёт итоговой коррекции
		correction = (int)(Kp * error + Ki * sumError + Kd * deltaError);

		// Применяем мощность с учётом коррекции
		motor[motorB] = basePower - correction;
		motor[motorC] = basePower + correction;

		prevError = error;
		wait1Msec(20);
	}
	waitAfterTask();
}

void rotation(float degrees, int dir = 1){
	float calibration = 1.02;
    // Параметры робота
    float L = 120.0;    // Расстояние между колёсами (мм)
    float D = 56.0;     // Диаметр колеса (мм)
    int basePower = 47;  // Базовая мощность моторов
    
    float Kp = 1.2;     // Пропорциональный
    float Ki = 0.02;    // Интегральный  
    float Kd = 0.8;     // Дифференциальный
    
    float target = (int)((L * degrees * calibration) / D);
    
    float error = 0, prevError = 0;
    float sumError = 0, deltaError = 0;
    float correction = 0;
    
    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;
    
    while(true) {
        // Текущая позиция - используем среднее двух энкодеров
        int encB = nMotorEncoder[motorB];
        int encC = abs(nMotorEncoder[motorC]);
        float currentPos = (abs(encB) + abs(encC)) / 2;
        
        // Проверка достижения цели
        if (currentPos >= target) break;
        
        // Расчет ошибки
        error = target - currentPos;
        
        // ПИД-коррекция
        sumError += error;
        deltaError = error - prevError;
        correction = Kp * error + Ki * sumError + Kd * deltaError;
        
        // Ограничение коррекции
        if (correction > 30) correction = 30;
        if (correction < -30) correction = -30;
        
        // Гарантированная минимальная мощность для обоих моторов
        int powerB = basePower + correction;
        int powerC = basePower + correction;
        
        // Применяем направление
        motor[motorB] = dir * powerB;
        motor[motorC] = -dir * powerC;
        
        // Сохранение ошибки
        prevError = error;
        
        wait1Msec(15);
    }
	waitAfterTask();
}


task main()
{
	forward(6);
	rotation(90);
	waitAfterTask();

	forward(6, 70);	
	rotation(90, -1 );
	waitAfterTask();
	
	forward(4, 70);	
	rotation(90, -1);
	waitAfterTask();

	forward(2, 70);
}

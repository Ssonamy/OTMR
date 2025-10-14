// !!Использовал робота LEGO REMBot, все значения актуальны для него!!
// ПИД-регулятор

void waitAfterTask()
{
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
	&&  + (abs(nMotorEncoder[motorC])) < target))
	{
		// Ошибка = разница между энкодерами
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

		// Сохраняем ошибку для следующего шага
		prevError = error;

		// Задержка для стабильности (цикл ≈ 20 мс)
		wait1Msec(20);
	}
	waitAfterTask();
}

// void rotation(int degrees, int dir = 1){
    // float Kp = 0.7;   // Пропорциональный
    // float Ki = 0.02;  // Интеграл
    // float Kd = 0.4;   // Дифференциальный
	
    // float L = 118.0;   // Расстояние между колёсами, мм
    // float D = 56.0;    // Диаметр колеса, мм

    // int basePower = 50; // Базовая мощность моторов

    // int target = (int)(((L * degrees) / D + (0.5))*dir);

    // int error = 0;
    // int prevError = 0;
    // float sumError = 0;
    // int correction = 0;
    // int deadband = 2; // мёртвая зона для ошибки

    // /* --- Сброс энкодеров --- */
    // nMotorEncoder[motorB] = 0;
    // nMotorEncoder[motorC] = 0;

    // /* --- Основной цикл --- */
    // while(true){
        // /* Текущая разность энкодеров */
        // int currentDiff = abs(nMotorEncoder[motorB]) + abs(nMotorEncoder[motorC]);

        // /* Ошибка = target - пройденное расстояние */
		// error = target - (abs(nMotorEncoder[motorB]) + abs(nMotorEncoder[motorC]))/2;


        // /* Проверка deadband */
        // if(abs(error) <= deadband) break;

        // /* Интеграл с ограничением (antiwindup) */
        // sumError += error;
        // if(sumError > 100) sumError = 100;
        // if(sumError < -100) sumError = -100;

        // /* Дифференциал */
        // int deltaError = error - prevError;

        // /* PID коррекция */
		// correction = (int)(Kp*error + Ki*sumError + Kd*deltaError);


        // /* --- Применение мощности с учётом направления поворота --- */
		// motor[motorB] =  dir * (basePower - correction);
		// motor[motorC] = -dir * (basePower - correction);


        // /* Сохраняем ошибку */
        // prevError = error;

        // /* Цикл ≈ 20 мс */
        // wait1Msec(20);
    // }

    // /* Остановка моторов */
    // motor[motorB] = 0;
    // motor[motorC] = 0;

    // wait1Msec(200); // пауза для механической стабилизации
// }


void rotation(int degrees, int dir = 1){
	/* Переменные робота */
    float L = 116.0;   // Расстояние между колёсами, мм
    float D = 56.0;    // Диаметр колеса, мм
    int basePower = 36; // Базовая мощность моторов
	
    float Kp = 0.4;    // Коэффициент пропорциональности
	float Ki = 0.01;
	float Kd = 0.4;
	
    int target = (int)((L * degrees) / D + (0.5 * dir));

    int deadband = 2;   // Мёртвая зона для ошибки
    float sumError = 0;
    int prevError = 0;
    int correction = 0;	

    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;

    while(abs(nMotorEncoder[motorB]) < target)
    {
        int error = nMotorEncoder[motorB] + nMotorEncoder[motorC];
        int correction = (int)(Kp * error);

        motor[motorB] =  dir * (basePower - correction);
        motor[motorC] = -dir * (basePower - correction);
        wait1Msec(20);
    }
	waitAfterTask();
}


task main()
{
	forward(6);
	rotation(90);
	waitAfterTask();

	forward(5.5, 70);	
	rotation(90, -1 );
	waitAfterTask();
	
	forward(4, 70);	
	rotation(90, -1);
	waitAfterTask();

	forward(2, 100);
}

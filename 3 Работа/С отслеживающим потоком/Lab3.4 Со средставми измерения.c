#pragma config(Sensor, S2, gyro, sensorAnalogInactive)
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

		// Сохраняем ошибку для следующего шага
		prevError = error;

		// Задержка для стабильности (цикл ≈ 20 мс)
		wait1Msec(20);
	}
	waitAfterTask();
}

void rotation(float degrees, int dir = 1){
	float calibration = /* 1.35 */ 1 ;
    // Параметры робота
    float L = 120.0;    // Расстояние между колёсами (мм)
    float D = 56.0;     // Диаметр колеса (мм)
    int basePower = 47;  // Базовая мощность моторов
    
    // Коэффициенты ПИД-регулятора
    float Kp = 1.2;     // Пропорциональный
    float Ki = 0.02;    // Интегральный  
    float Kd = 0.8;     // Дифференциальный
    
    // Расчет целевого значения
    float target = (int)((L * degrees * calibration) / D);
    SensorValue[S2] = 0;
    
    // Переменные ПИД-регулятора
    float error = 0, prevError = 0;
    float sumError = 0, deltaError = 0;
    float correction = 0;
    
    // Сброс энкодеров
    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;
    
    // Основной цикл регулирования
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
void runForward(int distance, int power = 70){
    startTask(MonitorTask, 50);
    forward(distance, power);
    stopTask(MonitorTask);
}

// Функция, запускающая отслеживающий поток при повороте
void runRotation(float degrees, int dir = 1){
    startTask(MonitorTask, 50);
    rotation(degrees, dir);
    stopTask(MonitorTask);
}

task main()
{
	runForward(6);
	runRotation(93.6);
	waitAfterTask();

	runForward(6);	
	runRotation(90, -1 );
	waitAfterTask();
	
	runForward(4);	
	runRotation(90, -1);
	waitAfterTask();

	runForward(2, 100);
}

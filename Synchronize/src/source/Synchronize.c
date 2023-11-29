/*
        * File: char.c
        * Author: Le Quang
        * Date: 27/05/2023
        * Description: This file include function to 
                                * Configurate port
                                * Read encoder
                                * Read potentiometer value
                                * Control servo motor NISCA NFNF5475E via PID algorithm
                                * Generate PWM to control servo motor and stepper motor
                                * Display LCD
*/

#include "Synchronize.h"

/*=======================================================================================================
*                                          PORT CONFIGURATION
=========================================================================================================*/
void gpioConfig(void)
{
        GPIO_InitTypeDef gpioInitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
        
        // Configurate stepper PWM pin
        gpioInitStructure.GPIO_Pin = PWM_STEPPER1_PIN|PWM_STEPPER2_PIN;
        gpioInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(PWM_STEPPER_PORT,&gpioInitStructure);
        
        // Configurate stepper direction and enable pin
        gpioInitStructure = DIR_STEPPER1_PIN|DIR_STEPPER2_PIN|ENA_STEPPER1_PIN|ENA_STEPPER2_PIN;
        gpioInitStructure = GPIO_Mode_Out_PP;
        gpioInitStructure = GPIO_Speed_50MHz;
        GPIO_Init(DIR_ENA_PORT, &gpioInitStructure);

        // Configurate servo motor direction pin
        gpioInitStructure.GPIO_Pin = DIRECT_MOTOR1_PIN1|DIRECT_MOTOR1_PIN2|DIRECT_MOTOR2_PIN1|DIRECT_MOTOR2_PIN2;
        gpioInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(PWM_MOTOR1_PORT, &gpioInitStructure);

        // Configurate PWM pin for motor 1 and motor 2
        gpioInitStructure.GPIO_Pin = PWM_MOTOR1_PIN|PWM_MOTOR2_PIN;
        gpioInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(PWM_MOTOR1_PORT, &gpioInitStructure);

        // Configurate motor 1 read encoder pin
        gpioInitStructure.GPIO_Pin = ENCODER1_PIN_A | ENCODER1_PIN_B;
        gpioInitStructure.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_Init(ENCODER1_PORT, &gpioInitStructure);

        // Configurate motor 2 read encoder pin
        gpioInitStructure.GPIO_Pin = ENCODER2_PIN_A | ENCODER2_PIN_B;
        gpioInitStructure.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_Init(ENCODER2_PORT, &gpioInitStructure);

        // Configurate limit switch pin (at start position)
        gpioInitStructure.GPIO_Pin = LIMIT_SWITCH_START_PIN;
        gpioInitStructure.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_Init(LIMIT_SWITCH_PORT, &gpioInitStructure);

        // Configurate limit switch pin (at end position)
        gpioInitStructure.GPIO_Pin = LIMIT_SWITCH_END_PIN;
        gpioInitStructure.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_Init(LIMIT_SWITCH_PORT, & gpioInitStructure);

        // Configurate ADC pin PC0
        gpioInitStructure.GPIO_Pin = GPIO_Pin_0;
        gpioInitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOC, &gpioInitStructure);

        // Configurate pin 6 SDA, pin 7 SCL
		gpioInitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		gpioInitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
		gpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpioInitStructure);

        // Initial stepper direct pin
        GPIO_SetBits(PWM_MOTOR1_PORT, DIRECT_MOTOR1_PIN1);
	    GPIO_ResetBits(PWM_MOTOR1_PORT, DIRECT_MOTOR1_PIN2);
}

/*=======================================================================================================
*                                       DELAY FUNCTION CONFIGURATION
=========================================================================================================*/
/**Timer 2 configuration:
	*	TIM4CLk is set to 72MHz, the TIM1 prescale is equal to 2000 so the TIM1 counter clock is used 72MHZ/2000 = 36000Hz
	* We need to generate a time baase is equal to 2ms with 36KHz so TIM1 period = 0.002*36000-1 = 71
	*	
*/
void interruptTIM1Config(void)
{
        TIM_TimeBaseInitTypeDef timer1;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
        
        timer1.TIM_Prescaler = 2000;
        timer1.TIM_Period = 71;
        timer1.TIM_CounterMode = TIM_CounterMode_Up;
        timer1.TIM_ClockDivision =  TIM_CKD_DIV1;
        TIM_TimeBaseInit(TIM1, &timer1);
        
        TIM_ITConfig(TIM1, TIM_IT_Update,ENABLE);
        TIM_Cmd(TIM1, ENABLE);
        
        NVIC_InitTypeDef ITstruct;
        ITstruct.NVIC_IRQChannel = TIM1_UP_IRQn;
        ITstruct.NVIC_IRQChannelPreemptionPriority = 0x00;
        ITstruct.NVIC_IRQChannelSubPriority = 0x00;
        ITstruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&ITstruct);
}

void TIM1_UP_IRQHandler(void)
{
        millissecond+=2;
        TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
}
void delayMs(uint32_t ms)
{
        millissecond = 0;
        while(millissecond < ms);
}

/*=======================================================================================================
*                                              INTERRUPT
=========================================================================================================*/
void interruptConfig(void) 
{
        // Configurate EXTI read motor 1 encoder
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);
        EXTI_InitTypeDef EXTI_InitStruct;
        EXTI_InitStruct.EXTI_Line = EXTI_Line1;
        EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_InitStruct.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStruct);

        // Configurate EXTI read motor 2 encoder
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);
        EXTI_InitStruct.EXTI_Line = EXTI_Line2;
        EXTI_Init(&EXTI_InitStruct);

        // Configurate NVIC read motor 1 encoder
        NVIC_InitTypeDef NVIC_InitStruct;
        NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);

        // Configurate NVIC read motor 2 encoder
        NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
        NVIC_Init(&NVIC_InitStruct);
            
        
            
        // Configurate EXTI read limit switch (at start position)
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
        EXTI_InitStruct.EXTI_Line = EXTI_Line3;
        EXTI_Init(&EXTI_InitStruct);
        // Configurate NVIC read limit switch (at start position)
        NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
        NVIC_Init(&NVIC_InitStruct);
            
        // Configurate EXTI read limit switch (at end position)
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
        EXTI_InitStruct.EXTI_Line = EXTI_Line4;
        EXTI_Init(&EXTI_InitStruct);
        // Configurate NVIC read limit switch (at end position)
        NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
        NVIC_Init(&NVIC_InitStruct);
}

// Interrupt function read motor 1 encoder
void EXTI1_IRQHandler(void) 
{
        if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
            if(GPIO_ReadInputDataBit(ENCODER1_PORT, ENCODER1_PIN_B)==1) currentSpeed1++;
            else currentSpeed1--;
            EXTI_ClearITPendingBit(EXTI_Line1);
        }
}

// Interrupt function read motor 2 encoder
void EXTI2_IRQHandler(void) 
{
        if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
            if(GPIO_ReadInputDataBit(ENCODER2_PORT, ENCODER2_PIN_B)==1) currentSpeed2++;
            else currentSpeed2--;
            EXTI_ClearITPendingBit(EXTI_Line2);
        }
}

// Interrupt function read limit switch (at start position)
void EXTI3_IRQHandler(void) 
{
        if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
            stepperDirectStatus = 1;
            EXTI_ClearITPendingBit(EXTI_Line3);
        }
}
// Interrupt function read limit switch (at end position)
void EXTI4_IRQHandler(void) 
{
        if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
            stepperDirectStatus = 0;
            display("APPROACH")
            EXTI_ClearITPendingBit(EXTI_Line4);
        }
}

/*=======================================================================================================
*                                              PWM
=========================================================================================================*/

void initPWM(void)
{
		TIM_TimeBaseInitTypeDef timerInit;
		TIM_OCInitTypeDef pwmInit;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
		timerInit.TIM_CounterMode = TIM_CounterMode_Up;
		timerInit.TIM_Period = 10000 - 1;
		timerInit.TIM_Prescaler = 7200 - 1;
	
		TIM_TimeBaseInit(TIM2, &timerInit);
		TIM_Cmd(TIM2, ENABLE);
	
		// PWM Channel 0 - motor 1
		pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
		pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
		pwmInit.TIM_Pulse = 0;
		pwmInit.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC1Init(TIM2,&pwmInit);
		
		// PWM Channel 1 - motor 2
		pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
		pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
		pwmInit.TIM_Pulse = 0;
		pwmInit.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC2Init(TIM2,&pwmInit);
		
		// PWM Channel 2 - stepper motor 1
		pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
		pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
		pwmInit.TIM_Pulse = 0;
		pwmInit.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC3Init(TIM2,&pwmInit);
		
		// PWM Channel 3 - stepper motor 2
		pwmInit.TIM_OCMode = TIM_OCMode_PWM1;
		pwmInit.TIM_OCPolarity = TIM_OCPolarity_High;
		pwmInit.TIM_Pulse = 0;
		pwmInit.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OC4Init(TIM2,&pwmInit);
}

// PWM control speed of motor 1
void setPWM1Value(uint16_t value) 
{
        TIM2->CCR1 = value;
}
// PWM control speed of motor 2
void setPWM2Value(uint16_t value) 
{
        TIM2->CCR2 = value;
}
// PWM control stepper motor 1
void setPWM3Value(uint16_t value) 
{
        TIM2->CCR3 = value;
}
// PWM control stepper motor 2
void setPWM4Value(uint16_t value)
{
        TIM2->CCR4 = value;
}

/*=======================================================================================================
*                                              ADC
=========================================================================================================*/

void initADC(void) 
{    
        // Initial adc
        ADC_InitTypeDef ADC_InitStructure;

        // Enable ADC1 clock
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

        // Configurate ADC
        ADC_DeInit(ADC1);
        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_InitStructure.ADC_ScanConvMode = DISABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfChannel = 1;
        ADC_Init(ADC1, &ADC_InitStructure);

        // Configurate channel ADC1_IN10 (PC0)
        ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);

        // Enalble ADC
        ADC_Cmd(ADC1, ENABLE);
}

// read potentiometer signal and convert to value range 0 - 10000
uint16_t readAndConvertPotentiometer(void) 
{
        // Read signel in ADC1_IN10 (PC0)
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
        uint16_t adcValue = ADC_GetConversionValue(ADC1);

        // Convert value to range 0 - 10000
        uint16_t convertedValue = (uint16_t)((float)adcValue / 4095 * 10000);//adc 12bit

        return convertedValue;
}

/*=======================================================================================================
*                                              LCD I2C
=========================================================================================================*/

void lcd_send_nibble(char data, uint8_t rs) 
{
    // Send 4 bit data to lcd

    data <<= 4;  // Shift left by 4 to send the higher nibble
    data |= (rs << 1);  // Add the value of RS (Register Select) to the data byte

    // Send data via I2C
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    I2C_GenerateSTART(I2C1, ENABLE);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    I2C_Send7bitAddress(I2C1, LCD_I2C_ADDR<<1, I2C_Direction_Transmitter);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    I2C_SendData(I2C1, data);

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    I2C_GenerateSTOP(I2C1, ENABLE);
    
    delayMs(1);
}

void lcd_send_byte(char data, uint8_t rs) 
{
        // Send byte data to lcd

        // Send 4 high byte first (high nibble)
        lcd_send_nibble(data >> 4, rs);

        // Send 4 byte after (low nibble)
        lcd_send_nibble(data & 0x0F, rs);
}

void lcd_send_cmd(char cmd) 
{
        // Send command to lcd
        lcd_send_byte(cmd, 0);  // RS = 0 (Command mode)
}

void lcd_send_data(char data) 
{
        // Send data to lcd
        lcd_send_byte(data, 1);  // RS = 1 (Data mode)
}

void lcd_clear_display(void) 
{
        // Clear lcd screen
        lcd_send_cmd(0x01);
        delayMs(2);
}

void lcd_goto_XY(int row, int col) 
{
        // Set lcd cussor position

        // Caculate each square of lcd
        uint8_t address = (row == 0) ? col : (0x40 + col);

        // G?i l?nh d?n LCD d? d?t con tr?
        lcd_send_cmd(0x80 | address);
}

void lcd_send_string(char *str) 
{
        // Send string to lcd
        while (*str) {
            lcd_send_data(*str++);
        }
}

void lcd_init(void) 
{
        // Initial lcd

        delayMs(50);  // wait for lcd start

        lcd_send_nibble(0x30, 0);  // Function set
        delayMs(5);
        lcd_send_nibble(0x30, 0);  // Function set
        delayMs(1);
        lcd_send_nibble(0x30, 0);  // Function set
        delayMs(1);
        lcd_send_nibble(0x20, 0);  // Ch? d? 4-bit
        delayMs(1);

        lcd_send_cmd(0x28);
        lcd_send_cmd(0x08);
        lcd_send_cmd(0x01);
        delayMs(2);
        lcd_send_cmd(0x06);
        lcd_send_cmd(0x0C);
}

/*=======================================================================================================
*                                              LOCAL FUNCTION
=========================================================================================================*/

// Function update motor speed value
void updateSpeed() 
{       
        // Set PWM control motor 1 via potentiometer value
        setPWM1Value(readAndConvertPotentiometer());
        //Update encoder pulse at real time 
        currentSpeed1 = encoderCount1;
        currentSpeed2 = encoderCount2;
}

// PID controller function
int16_t pidController() 
{
        error2 = currentSpeed1 - currentSpeed2;
        target2 += Kp * error2 + Ki * (error2 + lastError2) + Kd * (error2 - lastError2);
        lastError2 = error2;
		int16_t output = (uint16_t) target2; 
		
        // if PID value greater than 10000/-10000, set equal 10000/-10000 (PWM pulse from 0 to 10000)
		if(output > 10000) output = 10000; 
		else if (output < -10000) output = -10000;
	
		return output;
}

// Update PWM to control motor 2 base on motor 1 encoder pulse 
void updatePWM(int16_t updateSpeed)
{
    if(updateSpeed > 0)
		{
			GPIO_SetBits(PWM_MOTOR1_PORT, DIRECT_MOTOR2_PIN1);
			GPIO_ResetBits(PWM_MOTOR1_PORT, DIRECT_MOTOR2_PIN2);
			setPWM2Value(updateSpeed);
		}else if(updateSpeed < 0)
		{
			GPIO_ResetBits(PWM_MOTOR1_PORT, DIRECT_MOTOR2_PIN1);
			GPIO_SetBits(PWM_MOTOR1_PORT, DIRECT_MOTOR2_PIN2);
			setPWM2Value(-updateSpeed);
		}
}

void controlStepper (uint16_t long_feedscrew_len, uint16_t short_feedscrew_len)
{
	// caculate ratio among 2 feed screw (the longer one and the shorter one)
	uint8_t ratioFeedscrew = short_feedscrew_len/long_feedscrew_len;
	// Enable stepper
	GPIO_ResetBits(DIR_ENA_PORT, ENA_STEPPER1_PIN|ENA_STEPPER2_PIN);
	// Direct stepper
	if (stepperDirectStatus == 1) GPIO_SetBits(DIR_ENA_PORT, DIR_STEPPER1_PIN|DIR_STEPPER2_PIN);
	else GPIO_ResetBits(DIR_ENA_PORT, DIR_STEPPER1_PIN|DIR_STEPPER2_PIN);
	setPWM4Value(readAndConvertPotentiometer());
	setPWM3Value(readAndConvertPotentiometer()*ratioFeedscrew);
}

/*=======================================================================================================
*                                              CACULATE SPEED/DISPLAY
=========================================================================================================*/

void display (char status)
{
		lcd_clear_display();
		lcd_goto_XY(0,0);
		lcd_send_string("speed:");
		lcd_goto_XY(0,6);
		sprintf(buffer, "%d",motorSpeed1);
		lcd_send_string(buffer);
		lcd_goto_XY(0,12);
		sprintf(buffer, "%d",motorSpeed2);
		lcd_send_string(buffer); // 
		lcd_goto_XY(1,0);
		lcd_send_string("Status:");
		lcd_goto_XY(1,8);
		lcd_send_string(status);
}

/*
	*Timer 3 configuration:
	*	TIM3CLk is set to 72MHz, the TIM3 prescale is equal to 4000 so the TIM3 counter clock is used 72MHZ/4000 = 18000Hz
	* We need to generate a time baase is equal to 1s with 36KHz so TIM3 period = 1*18000-1 = 17999
	*	
*/
void interruptTIM3Config(void)
{
        TIM_TimeBaseInitTypeDef timer3;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
        
        timer3.TIM_Prescaler = 4000;
        timer3.TIM_Period = 17999;
        timer3.TIM_CounterMode = TIM_CounterMode_Up;
        timer3.TIM_ClockDivision =  TIM_CKD_DIV1;
        TIM_TimeBaseInit(TIM3, &timer3);
        
        TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
        TIM_Cmd(TIM3, ENABLE);
        
        NVIC_InitTypeDef ITstruct;
        ITstruct.NVIC_IRQChannel = TIM3_IRQn;
        ITstruct.NVIC_IRQChannelPreemptionPriority = 0x00;
        ITstruct.NVIC_IRQChannelSubPriority = 0x00;
        ITstruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&ITstruct);
}

void TIM3_IRQHandler()
{
        static int curPulse1 = 0;
        static int prePulse1 = 0;
        curPulse1 = currentSpeed1;
        static int curPulse2 = 0;
        static int prePulse2 = 0;
        curPulse2 = currentSpeed2;
        
        // Encoder has 200pulse/wheel, timer interrupt one time/s => number of pulse /200 * 60 = speed (rpm)
        motorSpeed1 = (curPulse1 - prePulse1)/200 * 60; //motor 1 speed
        motorSpeed2 = (curPulse2 - prePulse2)/200 * 60;	//motor 2 speed
        
        prePulse1 = curPulse1;
        prePulse2 = curPulse2;
        display("FAR APART");
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
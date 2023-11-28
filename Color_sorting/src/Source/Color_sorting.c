#include "Color_sorting.h"

/*============================================================================================
*                                       PORT CONFIGURATION
==============================================================================================*/
void portConfig(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;

        // Configurate pin control dc motor
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &PORT_InitStructure.GPIO_Pin);

        // Configurate pin 6 SDA, pin 7 SCL
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

        // Configuration timer3 PWM pin, pin A6 is channel 0, A7 is channel 1
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        // Configuration timer3 PWM pin, pin B0 is channel 2 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*============================================================================================
*                                       I2C CONFIGURATION
==============================================================================================*/

void I2C_Configuration(void) {
	
		I2C_InitTypeDef I2C_InitStructure;

		// Active Clock for GPIOB and I2C1
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
		

		// Configurate I2C1
		I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
		I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
		I2C_InitStructure.I2C_OwnAddress1 = 0x00;
		I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
		I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
		I2C_InitStructure.I2C_ClockSpeed = 100000; // Frequency 100 KHz
		I2C_Init(I2C1, &I2C_InitStructure);

		// Enable I2C1
		I2C_Cmd(I2C1, ENABLE);
}

void I2C_Start(I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction) {
  // Start transmit data
  while (I2Cx->SR2 & I2C_SR2_BUSY);
  I2Cx->CR1 |= I2C_CR1_START;

  // waiting for start successful
  while (!(I2Cx->SR1 & I2C_SR1_SB));

  // Send reciever address and read/write bit
  I2Cx->DR = (address << 1) | direction;

  // waiting for ack/nack bit
  if (direction == I2C_Direction_Transmitter) {
    while (!(I2Cx->SR1 & I2C_SR1_ADDR));
    while (!(I2Cx->SR2 & I2C_SR2_TRA));
  } else if (direction == I2C_Direction_Receiver) {
    while (!(I2Cx->SR1 & I2C_SR1_ADDR));
    while (I2Cx->SR2 & I2C_SR2_TRA);
  }
}

void I2C_Stop(I2C_TypeDef *I2Cx) {
  // stop transmit data
  I2Cx->CR1 |= I2C_CR1_STOP;

  // waiting stop successful
  while (I2Cx->SR2 & I2C_SR2_MSL);
}

void I2C_WriteData(I2C_TypeDef *I2Cx, uint8_t *data, uint8_t dataSize) {
  for (uint8_t i = 0; i < dataSize; i++) {
    // send data
    I2Cx->DR = data[i];

    // wait for send data successful
    while (!(I2Cx->SR1 & I2C_SR1_TXE));
  }
}

uint8_t I2C_ReadAck(I2C_TypeDef *I2Cx) {
  // read ACK bit
  I2Cx->CR1 |= I2C_CR1_ACK;
  while (!(I2Cx->SR1 & I2C_SR1_RXNE));
  return I2Cx->DR;
}

uint8_t I2C_ReadNack(I2C_TypeDef *I2Cx) {
  // read NACK bit
  I2Cx->CR1 &= ~I2C_CR1_ACK;
  while (!(I2Cx->SR1 & I2C_SR1_RXNE));
  return I2Cx->DR;
}

/*============================================================================================
*                                       TCS34725
==============================================================================================*/
void TCS34725_Init(void) 
{
  // Configurate color sensor TCS34725
  uint8_t config_data[] = {0x80, 0x03};
  I2C_Start(I2C1, TCS34725_I2C_ADDR, I2C_Direction_Transmitter);
  I2C_WriteData(I2C1, config_data, sizeof(config_data));
  I2C_Stop(I2C1);
}

void TCS34725_ReadColor(uint16_t *red, uint16_t *green, uint16_t *blue) 
{
  // read color data recieve from TCS34725 sensor
  uint8_t reg_addr = 0x14;
  I2C_Start(I2C1, TCS34725_I2C_ADDR, I2C_Direction_Transmitter);
  I2C_WriteData(I2C1, &reg_addr, 1);
  I2C_Stop(I2C1);

  I2C_Start(I2C1, TCS34725_I2C_ADDR, I2C_Direction_Receiver);

  // save color data to red, green, variable into variable that pointer direct
  *red = (I2C_ReadAck(I2C1) | (I2C_ReadAck(I2C1) << 8));
  *green = (I2C_ReadAck(I2C1) | (I2C_ReadAck(I2C1) << 8));
  *blue = (I2C_ReadNack(I2C1) | (I2C_ReadNack(I2C1) << 8));

  I2C_Stop(I2C1);
}

/*============================================================================================
*                                       Delay Microsecond
==============================================================================================*/

void configInterruptTIM2(void){
	TIM_TimeBaseInitTypeDef timer2;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	timer2.TIM_Prescaler = 2000;
	timer2.TIM_Period = 71;
	timer2.TIM_CounterMode = TIM_CounterMode_Up;
	timer2.TIM_ClockDivision =  TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &timer2);
	
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	
	NVIC_InitTypeDef ITstruct;
	ITstruct.NVIC_IRQChannel = TIM2_IRQn;
	ITstruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	ITstruct.NVIC_IRQChannelSubPriority = 0x00;
	ITstruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&ITstruct);
}

void TIM2_IRQHandler(){
	millissecond+=2;
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void delayMs(uint32_t ms){
	millissecond = 0;
	while(millissecond < ms);
}

/*============================================================================================
*                                       PWM
==============================================================================================*/

void Timer_Configuration(void) {
  // Enable TIM3 clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  // Configurate TIM3 generate PWM
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  // Generate PWM with frequency 50Hz
  TIM_TimeBaseStructure.TIM_Period = 19999;
  TIM_TimeBaseStructure.TIM_Prescaler = 71;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  // Init TIM3
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  // Servo 1 (PA6)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1500;  // 1.5ms
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  // Servo 2 (PA7)
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  // Servo 3 (PB0))
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  // Enable TIM3
  TIM_Cmd(TIM3, ENABLE);
}

void Servo_SetPosition(uint16_t pulseWidth1, uint16_t pulseWidth2, uint16_t pulseWidth3) {
  TIM3->CCR1 = pulseWidth1;
  TIM3->CCR2 = pulseWidth2;
  TIM3->CCR3 = pulseWidth3;
}

/*============================================================================================
*                                       LCD
==============================================================================================*/

void lcd_send_nibble(char data, uint8_t rs) {
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

void lcd_send_byte(char data, uint8_t rs) {
  // Send byte data to lcd

  // Send 4 high byte first (high nibble)
  lcd_send_nibble(data >> 4, rs);

  // Send 4 byte after (low nibble)
  lcd_send_nibble(data & 0x0F, rs);
}

void lcd_send_cmd(char cmd) {
  // Send command to lcd
  lcd_send_byte(cmd, 0);  // RS = 0 (Command mode)
}

void lcd_send_data(char data) {
  // Send data to lcd
  lcd_send_byte(data, 1);  // RS = 1 (Data mode)
}

void lcd_clear_display(void) {
  // Clear lcd screen
  lcd_send_cmd(0x01);
  delayMs(2);
}

void lcd_goto_XY(int row, int col) {
  // Set lcd cussor position

  // Caculate each square of lcd
  uint8_t address = (row == 0) ? col : (0x40 + col);

  // G?i l?nh d?n LCD d? d?t con tr?
  lcd_send_cmd(0x80 | address);
}

void lcd_send_string(char *str) {
  // Send string to lcd
  while (*str) {
    lcd_send_data(*str++);
  }
}

void lcd_init(void) {
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

/*============================================================================================
*                                       LOCAL FUNCTION
==============================================================================================*/

void directServo(void)
{
	static uint8_t directFlagStatus = 0;
	if(directFlagStatus)
	{
		Servo_SetPosition(1700,1000,0);
		directFlagStatus = 0;
	}else if(directFlagStatus == 0)
	{
		Servo_SetPosition(1000,1000,0);
		directFlagStatus = 1;
	}
}
void homeServo(void)
{
	Servo_SetPosition(1000,1000,1500);
}

uint8_t sortColor(void)
{
	uint8_t colorIndex = 0;
	if (green > red && green > blue) {
			totalGreen++;
      Servo_SetPosition(0,0,1000);
			delayMs(800);
			Servo_SetPosition(0,1450,0);
			delayMs(400);
    } else if (blue > red && blue > green) {
			totalBlue++;
      Servo_SetPosition(0,0,1500);
			delayMs(800);
			Servo_SetPosition(0,1450,0);
			delayMs(400);
    } else {
			totalRed++;
      Servo_SetPosition(0,0,2000);
			delayMs(800);
			Servo_SetPosition(0,1450,0);
			delayMs(400);
    }
}

void display(void)
{
			lcd_clear_display();
			lcd_goto_XY(0,0);
			lcd_send_string("RED");
			lcd_goto_XY(1,1);
			sprintf(colorVar,"%d",totalRed);
			lcd_send_string(colorVar);
	
			lcd_goto_XY(0,5);
			lcd_send_string("BLUE");
			lcd_goto_XY(1,7);
			sprintf(colorVar,"%d",totalBlue);
			lcd_send_string(colorVar);
	
			lcd_goto_XY(0,11);
			lcd_send_string("GREEN");
			lcd_goto_XY(1,13);
			sprintf(colorVar,"%d",totalGreen);
			lcd_send_string(colorVar);	
}

void feedMaterial(void)
{
		static uint8_t dcMotorStatus = 0;
		if(dcMotorStatus == 1)
		{
				GPIO_SetBits(GPIOA, GPIO_Pin_4);
				GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		}else if(dcMotorStatus == 0)
		{
				GPIO_SetBits(GPIOA, GPIO_Pin_5);
				GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		}
}
#ifndef _COLOR_SORTING_H
#define _COLOR_SORTING_H

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define TCS34725_I2C_ADDR 0x29 // TCS34725 address
#define LCD_I2C_ADDR 0x27  // Module LCD address

uint32_t millissecond = 0; // Delay variable
uint16_t red, green, blue; // Color variable
uint8_t totalRed = 0, totalBlue = 0, totalGreen = 0; //Quantity of red, blue, green
char colorVar[100]; // string to display in lcd

void portConfig(void);
void I2C_Configuration(void);
void I2C_Start(I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction);
void I2C_Stop(I2C_TypeDef *I2Cx);
void I2C_WriteData(I2C_TypeDef *I2Cx, uint8_t *data, uint8_t dataSize)
uint8_t I2C_ReadAck(I2C_TypeDef *I2Cx)
uint8_t I2C_ReadNack(I2C_TypeDef *I2Cx)
void TCS34725_Init(void);
void TCS34725_ReadColor(uint16_t *red, uint16_t *green, uint16_t *blue);
void configInterruptTIM2(void)
void TIM2_IRQHandler();
void delayMs(uint32_t ms);
void Timer_Configuration(void);
void Servo_SetPosition(uint16_t pulseWidth1, uint16_t pulseWidth2, uint16_t pulseWidth3);
void lcd_send_nibble(char data, uint8_t rs);
void lcd_send_byte(char data, uint8_t rs);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_clear_display(void)
void lcd_goto_XY(int row, int col);
void lcd_send_string(char *str)
void lcd_init(void)
void directServo(void);
void homeServo(void);
uint8_t sortColor(void);
void display(void);
void feedMaterial(void);

#endif
/*
    * File: Synchronize.h
    * Author: Le Quang
    * Date: 27/05/2023
    * Description: inclue defines, initial variable, function name
*/

#ifndef _SYNCHRONIZE_H_
#define _SYNCHRONIZE_H_

#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

#define LCD_I2C_ADDR 0x27  // Module LCD address

#define PWM_MOTOR1_PIN GPIO_Pin_0
#define DIRECT_MOTOR1_PIN1 GPIO_Pin_4
#define DIRECT_MOTOR1_PIN2 GPIO_Pin_5
#define PWM_MOTOR1_PORT GPIOA

#define ENCODER1_PIN_A GPIO_Pin_6
#define ENCODER1_PIN_B GPIO_Pin_7
#define ENCODER1_PORT GPIOC

#define PWM_MOTOR2_PIN GPIO_Pin_1
#define DIRECT_MOTOR2_PIN1 GPIO_Pin_6
#define DIRECT_MOTOR2_PIN2 GPIO_Pin_7
#define PWM_MOTOR2_PORT GPIOA

#define ENCODER2_PIN_A GPIO_Pin_8
#define ENCODER2_PIN_B GPIO_Pin_9
#define ENCODER2_PORT GPIOC

#define PWM_STEPPER1_PIN GPIO_Pin_2
#define PWM_STEPPER1_PIN GPIO_Pin_2
#define PWM_STEPPER_PORT GPIOA

#define DIR_STEPPER1_PIN GPIO_Pin_1
#define ENA_STEPPER1_PIN GPIO_Pin_2
#define DIR_STEPPER1_PIN GPIO_Pin_1
#define ENA_STEPPER1_PIN GPIO_Pin_2
#define DIR_ENA_PORT GPIOC

#define PWM_STEPPER2_PIN GPIO_Pin_3
#define PWM_STEPPER2_PORT GPIOA
#define DIR_STEPPER2_PIN GPIO_Pin_3
#define ENA_STEPPER2_PIN GPIO_Pin_4
#define DIR_ENA_2_PORT GPIOC

#define LIMIT_SWITCH_START_PIN GPIO_Pin_0
#define LIMIT_SWITCH_END_PIN GPIO_Pin_1
#define LIMIT_SWITCH_PORT GPIOB
// PID constants
#define Kp 4.1
#define Ki 0.01
#define Kd 0.0

// Encoder variables
volatile int encoderCount1 = 0;
volatile int encoderCount2 = 0;

// PID variables
volatile int motorSpeed1 = 100;  // �?t t?c d? m?c ti�u c?a motor 1 ? d�y
volatile int motorSpeed2 = 100;  // �?t t?c d? m?c ti�u c?a motor 2 ? d�y
volatile int currentSpeed1 = 0;
volatile int currentSpeed2 = 0;
volatile int error1 = 0;
volatile int lastError1 = 0;
volatile int output1 = 0;
volatile float error2 = 0;
volatile int lastError2 = 0;
volatile int target2 = 0;

// control stepper direct variable
static uint8_t stepperDirectStatus = 1;
// delay microsecond variable
uint16_t millissecond = 0;
// string save speed after convert from uint16_t to char
char buffer[100];

void gpioConfig(void);
void interruptTIM1Config(void);
void delayMs(uint32_t ms);
void interruptConfig(void);
void initPWM(void);
void setPWM1Value(uint16_t value) 
void setPWM2Value(uint16_t value) 
void setPWM3Value(uint16_t value) 
void setPWM4Value(uint16_t value) 
void initADC(void);
uint16_t readAndConvertPotentiometer(void);
void lcd_send_nibble(char data, uint8_t rs);
void lcd_send_byte(char data, uint8_t rs);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_clear_display(void);
void lcd_goto_XY(int row, int col);
void lcd_send_string(char *str);
void lcd_init(void);
void updateSpeed();
int16_t pidController();
void updatePWM(int16_t updateSpeed);
void controlStepper (uint16_t long_feedscrew_len, uint16_t short_feedscrew_len);
void display (char status);
void interruptTIM3Config(void);

#endif
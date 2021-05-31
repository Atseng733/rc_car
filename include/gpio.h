#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f407xx.h"

//Enable GPIOx Clocks
#define GPIOA_CLK_EN (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk)

//GPIO Pins
#define GPIO_PIN_0 (1 << 0)
#define GPIO_PIN_1 (1 << 1)
#define GPIO_PIN_2 (1 << 2)
#define GPIO_PIN_3 (1 << 3)
#define GPIO_PIN_4 (1 << 4)
#define GPIO_PIN_5 (1 << 5)
#define GPIO_PIN_6 (1 << 6)
#define GPIO_PIN_7 (1 << 7)
#define GPIO_PIN_8 (1 << 8)
#define GPIO_PIN_9 (1 << 9)
#define GPIO_PIN_10 (1 << 10)
#define GPIO_PIN_11 (1 << 11)
#define GPIO_PIN_12 (1 << 12)
#define GPIO_PIN_13 (1 << 13)
#define GPIO_PIN_14 (1 << 14)
#define GPIO_PIN_15 (1 << 15)


//GPIO Mode
#define GPIO_MODE_INPUT 0 //Input
#define GPIO_MODE_OUTPUT_PP 0b001 //Push-pull output
#define GPIO_MODE_OUTPUT_OD 0b101 //Open-drain output
#define GPIO_MODE_AFIO 2 //Alternate function
#define GPIO_MODE_ANALOG 3 //Analog

//GPIO Speed
#define GPIO_SPEED_LOW 0 //2MHz
#define GPIO_SPEED_MED 1 //25MHz
#define GPIO_SPEED_HI 2 //50MHz
#define GPIO_SPEED_VHI 3 //100MHz

//GPIO pull-up/pull-down type
#define GPIO_PUPD_NONE 0 //No pull-up/pull-down
#define GPIO_PUPD_PULLUP 1 //Pull-up
#define GPIO_PUPD_PULLDOWN 2 //Pull-down

/*
    GPIO configuration typedef
    Port, pin(s), mode, speed, pupd
*/
typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t mode;
    uint8_t speed;
    uint8_t pupd;
} GPIO_CFG_TypeDef;


void GPIO_CFG(GPIO_CFG_TypeDef *pStruct); //Initialize GPIO pin with GPIO_CFG_TypeDef
void GPIO_TogglePin(GPIO_TypeDef *port, uint16_t pin); //Toggle GPIO pin

#endif
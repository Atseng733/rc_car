#include "main.h"

int main() {
    SysClockSetup();

    /* 
        Enable microcontroller clock output 1 (MCO1) pin (PA8) 
    */

    /* Enable GPIOA clock */
    GPIOA_CLK_EN;
    /* Set PA8 in AFO mode */
    GPIOA->MODER |= GPIO_MODER_MODER8_1;

    GPIO_CFG_TypeDef led_cfg = {
        .port = GPIOA,
        .pin = GPIO_PIN_6 | GPIO_PIN_7,
        .mode = GPIO_MODE_OUTPUT_PP,
        .speed = GPIO_SPEED_LOW,
        .pupd = GPIO_PUPD_PULLDOWN
    };
    GPIO_CFG(&led_cfg);

    led_cfg.pin &= ~(GPIO_PIN_7);
    GPIO_CFG(&led_cfg);

    GPIO_TogglePin(GPIOA, GPIO_PIN_6);
    GPIO_TogglePin(GPIOA, GPIO_PIN_6);
    GPIO_TogglePin(GPIOA, GPIO_PIN_6);
    /* Enable D2 on-board LED (PA6)*/
    //Set PA6 to output
    //GPIOA->MODER |= GPIO_MODER_MODER6_0;
    //Set output register to 1
    //GPIOA->ODR &= ~GPIO_ODR_OD6_Msk;
    /* System Clock Setup */

    while(1) {    

    }

    return 0;
}


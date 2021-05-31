#include "main.h"

int x;
int y;
int z = 5;
static double dub = 2.43;

int add(int a, int b) {
    return a + b;
}

int main() {
    SysClockSetup();

    /* 
        Enable microcontroller clock output 1 (MCO1) pin (PA8) 
    */

    /* Enable GPIOA clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;
    /* Set PA8 in AFO mode */
    GPIOA->MODER |= GPIO_MODER_MODER8_1;
    /* Set HSI clock as output */
    RCC->CFGR &= ~(RCC_CFGR_MCO1_Msk);


    /* Enable D2 on-board LED (PA6)*/
    //Set PA6 to output
    GPIOA->MODER |= GPIO_MODER_MODER6_0;
    //Set output register to 1
    GPIOA->ODR &= ~GPIO_ODR_OD6_Msk;

    /* System Clock Setup */

    y = add(x, z);
    int sum = add(y, z);

    while(1) {
        sum++;
    }

    return 0;
}


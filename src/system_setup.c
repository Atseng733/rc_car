/*
    Setup the system clock and other settings needed before program execution
*/

#include "system_setup.h"

/* 
    Setup the system clock, using HSE by default, to the value of F_SYS_CLK
*/
void SysClockSetup() {
    /*
        Calculate multiplication and division factors needed for PLL
    */
    uint8_t PLLM = F_HSE / 2000000; //Division factor set to result in recommended VCO input frequency of 2MHz
    uint16_t PLLN = F_SYS_CLK / 2000000; //Multiplication factor set to result in F_SYS_CLK after multiplying by 2MHz
    PLLN *= 2; //Multply by 2 since default PLL output divisor = 2

    uint8_t PLLP = 0;
    if(PLLN*2 > 50) {
        PLLN = PLLN * 2;
        PLLP = 0b01;
    }
    else if(PLLN*3 > 50) {
        PLLN = PLLN * 3;
        PLLP = 0b10;
    }
    else if(PLLN*4 > 50) {
        PLLN = PLLN * 4;
        PLLP = 0b11;
    }
    else {
        while(1);
    }

    /*
        Calculate APB1 (84MHz max) and APB2 (42MHz max) prescalers
        @TODO
    */
    //uint8_t PPRE2 = F_SYS_CLK / 84000000;

    /* 
        Enable HSE clock and wait for stabilization
    */
    RCC->CR |= RCC_CR_HSEON_Msk;
    while(!((RCC->CR & RCC_CR_HSEON_Msk) >> RCC_CR_HSEON_Pos));

    /*
        Setup PLL configuration register
    */
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE_Msk; //HSE as PLL source
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk | RCC_PLLCFGR_PLLP_Msk);
    RCC->PLLCFGR |= (PLLM << RCC_PLLCFGR_PLLM_Pos) | (PLLN << RCC_PLLCFGR_PLLN_Pos) | (PLLP << RCC_PLLCFGR_PLLP_Pos);


    /*
        Enable PLL and wait until ready
    */
    RCC->CR |= RCC_CR_PLLON_Msk;
    while(!((RCC->CR & RCC_CR_PLLRDY_Msk) >> RCC_CR_PLLRDY_Pos));

    /* Set PLL output as system clock and wait until ready*/
    RCC->CFGR |= RCC_CFGR_SW_1;
    while(!(((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos) == 0b10));

    /* Disable HSI clock */
    RCC->CR &= ~(RCC_CR_HSION_Msk);
}
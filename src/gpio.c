#include "gpio.h"

void GPIO_CFG(GPIO_CFG_TypeDef *pStruct) {
    int8_t position;
    uint16_t temp_pins = pStruct->pin;
    
    //Check pStruct->pins for bits set to 1 and set the corresponding pin's MODER to pStruct->mode
    for(position = 15; position >= 0; position--) {
        if((temp_pins & (1 << position))) {
            //Set MODER
            pStruct->port->MODER &= ~(3 << (position*2));
            pStruct->port->MODER |= ((pStruct->mode & 0b11) << (position*2));

            //Set OTYPER if output
            if(pStruct->mode == GPIO_MODE_OUTPUT_PP || pStruct->mode == GPIO_MODE_OUTPUT_OD) {
                pStruct->port->OTYPER &= ~(1 << position);
                pStruct->port->OTYPER |= ((pStruct->mode >> 2) << position);
            }

            //Set OSPEEDR
            pStruct->port->OSPEEDR &= ~(3 << (position*2));
            pStruct->port->OSPEEDR |= (pStruct->speed << (position*2));
        }
    }
}

void GPIO_TogglePin(GPIO_TypeDef *port, uint16_t pin) {
    int8_t position;
    uint16_t temp_pins = pin;

    //get current pin state
    for(position = 15; position >= 0; position--) {
        if(temp_pins & (1 << position)) {
            uint16_t odr = port->ODR;
            odr &= (1 << position);
            odr >>= position;
            port->BSRR |= (1 << (position + (16*odr)));
        }   
    }
}
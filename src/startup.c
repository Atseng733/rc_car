/*
    Sets up IRQ handlers and interrupt vector table
    Initializes variables
*/

#include <stdint.h>
#include "startup.h"
#include "main.h"

extern uint32_t INIT_SP; //Start of SRAM1 + STACK_SIZE in linker script

/*
    Interrupt Handler Declarations
*/
void Reset_Handler();
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak));
void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

void WWDG_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream0_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream1_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream2_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream3_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream4_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream5_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream6_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX0_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_WKUP_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FSMC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void ETH_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void ETH_WKUP_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_TX_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX0_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX1_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_SCE_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_WKUP_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DCMI_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CRYP_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void HASH_RNG_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));

/*
    Interrupt Vector Table
*/
void (*const __VECTOR_TABLE[98])() __attribute__ ((section(".vectors"))) = {
  (void (*)())(&INIT_SP),            /*     Initial Stack Pointer */
  Reset_Handler,                       /*     Reset Handler */
  NMI_Handler,                         /* -14 NMI Handler */
  HardFault_Handler,                   /* -13 Hard Fault Handler */
  MemManage_Handler,                   /* -12 MPU Fault Handler */
  BusFault_Handler,                    /* -11 Bus Fault Handler */
  UsageFault_Handler,                  /* -10 Usage Fault Handler */
  0,                                   /*     Reserved */
  0,                                   /*     Reserved */
  0,                                   /*     Reserved */
  0,                                   /*     Reserved */
  SVC_Handler,                         /*  -5 SVCall Handler */
  DebugMon_Handler,                    /*  -4 Debug Monitor Handler */
  0,                                   /*     Reserved */
  PendSV_Handler,                      /*  -2 PendSV Handler */
  SysTick_Handler,                     /*  -1 SysTick Handler */
  WWDG_Handler,                        /*  0x0040  */
  PVD_Handler,
  TAMP_STAMP_Handler,
  RTC_WKUP_Handler,
  FLASH_Handler,
  RCC_Handler,
  EXTI0_Handler,
  EXTI1_Handler,
  EXTI2_Handler,
  EXTI3_Handler,
  EXTI4_Handler,
  DMA1_Stream0_Handler,
  DMA1_Stream1_Handler,
  DMA1_Stream2_Handler,
  DMA1_Stream3_Handler,
  DMA1_Stream4_Handler,
  DMA1_Stream5_Handler,
  DMA1_Stream6_Handler,
  ADC_Handler,
  CAN1_TX_Handler,
  CAN1_RX0_Handler,
  CAN1_RX1_Handler,
  CAN1_SCE_Handler,
  EXTI9_5_Handler,
  TIM1_BRK_TIM9_Handler,
  TIM1_UP_TIM10_Handler,
  TIM1_TRG_COM_TIM11_Handler,
  TIM1_CC_Handler,
  TIM2_Handler,
  TIM3_Handler,
  TIM4_Handler,
  I2C1_EV_Handler,
  I2C1_ER_Handler,
  I2C2_EV_Handler,
  I2C2_ER_Handler,
  SPI1_Handler,
  SPI2_Handler,
  USART1_Handler,
  USART2_Handler,
  USART3_Handler,
  EXTI15_10_Handler,
  RTC_Alarm_Handler,
  OTG_FS_WKUP_Handler,
  TIM8_BRK_TIM12_Handler,
  TIM8_UP_TIM13_Handler,
  TIM8_TRG_COM_TIM14_Handler,
  TIM8_CC_Handler,
  DMA1_Stream7_Handler,
  FSMC_Handler,
  SDIO_Handler,
  TIM5_Handler,
  SPI3_Handler,
  UART4_Handler,
  UART5_Handler,
  TIM6_DAC_Handler,
  TIM7_Handler,
  DMA2_Stream0_Handler,
  DMA2_Stream1_Handler,
  DMA2_Stream2_Handler,
  DMA2_Stream3_Handler,
  DMA2_Stream4_Handler,
  ETH_Handler,
  ETH_WKUP_Handler,
  CAN2_TX_Handler,
  CAN2_RX0_Handler,
  CAN2_RX1_Handler,
  CAN2_SCE_Handler,
  OTG_FS_Handler,
  DMA2_Stream5_Handler,
  DMA2_Stream6_Handler,
  DMA2_Stream7_Handler,
  USART6_Handler,
  I2C3_EV_Handler,
  I2C3_ER_Handler,
  OTG_HS_EP1_OUT_Handler,
  OTG_HS_EP1_IN_Handler,
  OTG_HS_WKUP_Handler,
  OTG_HS_Handler,
  DCMI_Handler,
  CRYP_Handler,
  HASH_RNG_Handler,
  FPU_Handler
};

extern uint32_t _etext;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;

void Reset_Handler(void)
{
    /* Initialize .bss section to zero */
    for(uint32_t *p_bss = &_sbss; p_bss < &_ebss; p_bss++) {
        *p_bss = 0;
    }

    /* Initialize .data section to init values */
    uint32_t *p_init_val = &_etext;
    uint32_t *p_data = &_sdata;
    if(p_init_val != p_data) {
        for(;p_data < &_edata;) {
            *p_data++ = *p_init_val++;
        }
    }    

    main();

    while(1);
}

void HardFault_Handler(void) {
    while(1);
}

void Default_Handler()
{
    while(1);
}
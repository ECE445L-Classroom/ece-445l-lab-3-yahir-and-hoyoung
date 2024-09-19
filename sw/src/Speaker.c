// SysTick.c
// Runs on the TM4C123
// Provides functions to display data to the LCD. 
// Hoyoung Song
// September 18, 2024


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"


// have multiple ringtone
void Sound_Init(void);
void SysTick_Handler(void);

void Sound_Init(void){ uint32_t volatile delay;

  SYSCTL_RCGCGPIO_R |= 0x08; // activate port A
  delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTA_DIR_R |= 0x01;     // make PA5 out
  GPIO_PORTA_DR8R_R |= 0x01;    // can drive up to 8mA out
  GPIO_PORTA_DEN_R |= 0x01;     // enable digital I/O on PA5
  NVIC_ST_CTRL_R = 0;           // disable SysTick during setup
  NVIC_ST_RELOAD_R = 39999;     // reload value for 500us (assuming 80MHz)
  NVIC_ST_CURRENT_R = 0;        // any write to current clears it
  NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF; // priority 0               
  NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts

}

void SysTick_Handler(void){

  GPIO_PORTA_DATA_R ^= 0x01;     // toggle PA5

}
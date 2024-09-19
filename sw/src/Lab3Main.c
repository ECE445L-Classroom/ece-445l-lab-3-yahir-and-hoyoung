// Lab3Main.c
// Runs on LM4F120/TM4C123
// Uses ST7735.c to display the clock
// patterns to the LCD.
//    16-bit color, 128 wide by 160 high LCD
// Mark McDermott, Daniel Valvano and Jonathan Valvano
// Lab solution, do not post
// August 3,2024

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2024

 Copyright 2024 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Specify your hardware connections, feel free to change
// PD0 is squarewave output to speaker
// PE0 is mode select
// PE1 is left
// PE2 is right 
// PE3 is up
// PE4 is down
// if alarm is sounding, any button will quiet the alarm

#include <stdio.h>
#include <stdint.h>
#include "../inc/ST7735.h"
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/Timer0A.h"
#include "Lab3.h"
// ---------- Prototypes   -------------------------

#define  Mode (*((volatile unsigned long *) 0x40034004))			// PE0
#define  Left (*((volatile unsigned long *) 0x40034008))			// PE1
#define  Right (*((volatile unsigned long *) 0x40034010))			// PE2
#define  Up (*((volatile unsigned long *) 0x40034020))				// PE3
#define  Down (*((volatile unsigned long *) 0x40034040))			// PE4
#define  Speaker (*((volatile unsigned long *) 0x40007004))  	// PD0

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

void DisplayTime(void);    // 
void SetTime(void);      
void SetAlarm(void);
void AlarmSound(void);
void AlarmSwitch(void);
void StopAlarm(void);
void PortE_Init(void);      //
void Sound_Init(void);      //
uint32_t Mode_Change(void); //

int8_t hour = 0, minute = 0, second = 0;
uint32_t alarm = 0;

typedef enum {
		WAIT_FOR_PRESS,
    WAIT_FOR_RELEASE
} FSM_State;



void DisplayTime(void){
	char str[16];
	sprintf(str, "%02d:%02d:%02d", hour, minute, second);
	ST7735_DrawString(5,5,str,ST7735_ORANGE);
	
}
void UpdateTime(void){

	second += 1;
	if(second == 60){
		second = 0;
		minute += 1;
		if(minute == 60){
			minute = 0;
			hour += 1;
			if (hour == 24){
				hour = 0;
			}
		}
	}
}



void AlarmSound(void){
	
	alarm = 1;
	Speaker = 1 ;

}


void StopAlarm(void){


}



void PortE_Init(void){
	
	SYSCTL_RCGCGPIO_R |= 0x10;                 // Activate Port E
	while((SYSCTL_PRGPIO_R & 0x10) == 0){}	 	 // Wait for Port E clock
	GPIO_PORTE_DIR_R &= ~0x11;                 // PE0 - PE4 input
	GPIO_PORTE_DEN_R |= 0x11;									 // Enable digital I/O 

}


uint32_t Mode_Change(void){
	
	return(GPIO_PORTE_DATA_R & 0x01);
	
}

void Wait10ms(uint32_t delay){
  NVIC_ST_RELOAD_R = 800000;  // 10ms delay with 80 MHz clock
  NVIC_ST_CURRENT_R = 0;      
  for (uint32_t i = 0; i < delay; i++) {
    while ((NVIC_ST_CTRL_R & 0x00010000) == 0){}; 
  }
}

int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz
  // write this
	ST7735_InitR(INITR_REDTAB);
	PortE_Init();
	Timer0A_Init(&UpdateTime,80000000,2);
  EnableInterrupts();
	
	FSM_State current_state = WAIT_FOR_PRESS;
	uint8_t current_mode = 0;   //Mode 1: display time, Mode 2: SetTime,  Mode 3: Set Alarm,  Mode 4: Alarm switch
  while(1){
      // write this
		/*
		switch(current_state){
			case WAIT_FOR_PRESS:
				if(Mode_Change()){
					Wait10ms(10);
					if(Mode_Change()){
						current_state = WAIT_FOR_RELEASE;
					}
				}
				break;
			case WAIT_FOR_RELEASE:
				if(!Mode_Change()){
					Wait10ms(10);
					if(!Mode_Change()){
						if(current_mode == 1){
							DisplayTime();
							current_mode += 1;
						}
						else if(current_mode == 2){
							SetTime();
							current_mode += 1;
						}
						else if(current_mode ==3){
							SetAlarm();
							current_mode += 1;
						}
						
						else if(current_mode == 4){
							current_mode = 1;
							AlarmSwitch();
						}
					}
				}
				break;
		}
		*/
		DisplayTime();
		UpdateTime();
		WaitForInterrupt();
  }
}




// Switches.c
// Runs on the TM4C123
// Provides functions to use PE0-4 as positive logic input switches. 
// Yahir Lopez
// September 18, 2024

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/CortexM.h"


// ***************** Swtiches_Init ****************
// Initiate PE0-4 to be postive-logic input pins with a pull down resistor.  
// Inputs:  none
// Outputs: none
void Switches_Init(){
	SYSCTL_RCGCGPIO_R|=0x10;				//	activate clock for Port E
	while(SYSCTL_PRGPIO_R&0x10){} 	//	wait for activation
	GPIO_PORTE_DIR_R|=~0x1F;				//	Set 0-4 as input by writing to low.
	GPIO_PORTE_DEN_R|=0x0F;					// 	Enable Pins by writing high. 
	// EdgeCounter_Init();					// 	Turn on PF4/SW1 to be an button that triggers an interput. 
}

// ***************** PE0_Data ****************
// Read data from PE0 
// Inputs:  none
// Outputs: 32-bit result of data from PE0 as 0 or 1
uint32_t PE0_Data(){
	int32_t value = (GPIO_PORTE_DATA_R&0x01);
	Clock_Delay1ms(10); // Debounce
	return value;
}

// ***************** PE1_Data ****************
// Read data from PE1
// Inputs:  none
// Outputs: 32-bit result of data from PE1 as 0 or 1
uint32_t PE1_Data(){ 
	uint32_t value = ((GPIO_PORTE_DATA_R&0x02)>>1);
	Clock_Delay1ms(10); // Debounce
	return value;
}

// ***************** PE2_Data ****************
// Read data from PE2 
// Inputs:  none
// Outputs: 32-bit result of data from PE2 as 0 or 1
uint32_t PE2_Data(){
	uint32_t value = ((GPIO_PORTE_DATA_R&0x02)>>2);
	Clock_Delay1ms(10); // Debounce
	return value;	
}

// ***************** PE3_Data ****************
// Read data from PE3 
// Inputs:  none
// Outputs: 32-bit result of data from PE3 as 0 or 1
uint32_t PE3_Data(){
	uint32_t value = ((GPIO_PORTE_DATA_R&0x02)>>3);
	Clock_Delay1ms(10); // Debounce
	return value;
}

// ***************** PE4_Data ****************
// Read data from PE4 
// Inputs:  none
// Outputs: 32-bit result of data from PE4 as 0 or 1
uint32_t PE4_Data(){
	uint32_t value = ((GPIO_PORTE_DATA_R&0x02)>>4);
	Clock_Delay1ms(10); // Debounce
	return value;
}

// ***************** Switches_Data ****************
// Read data from all switches 
// Inputs:  none
// Outputs: 32-bit result of data from all switches
uint32_t Switches_Data(){
	uint32_t value = (GPIO_PORTE_DATA_R&0x1F);
	Clock_Delay1ms(10); // Debounce
	return value;
}

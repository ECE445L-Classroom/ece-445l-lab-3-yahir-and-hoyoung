// Switches.h
// Runs on the TM4C123
// Provides functions to use PE0-4 as positive logic input switches. 
// Yahir Lopez
// September 18, 2024

#ifndef Switches_h
#define Switches_h
#include <stdint.h>

// ***************** Swtiches_Init ****************
// Initiate PE0-4 to be postive-logic input pins with a pull down resistor.  
// Inputs:  none
// Outputs: none
void Switches_Init();

// ***************** PE0_Data ****************
// Read data from PE0 
// Inputs:  none
// Outputs: 32-bit result of data from PE0
uint32_t PE0_Data();

// ***************** PE1_Data ****************
// Read data from PE1
// Inputs:  none
// Outputs: 32-bit result of data from PE1 as 0 or 1
uint32_t PE1_Data();

// ***************** PE2_Data ****************
// Read data from PE2 
// Inputs:  none
// Outputs: 32-bit result of data from PE2 as 0 or 1
uint32_t PE2_Data();

// ***************** PE3_Data ****************
// Read data from PE3 
// Inputs:  none
// Outputs: 32-bit result of data from PE3 as 0 or 1
uint32_t PE3_Data();

// ***************** PE4_Data ****************
// Read data from PE4 
// Inputs:  none
// Outputs: 32-bit result of data from PE4 as 0 or 1
uint32_t PE4_Data();

// ***************** Switches_Data ****************
// Read data from all switches 
// Inputs:  none
// Outputs: 32-bit result of data from all switches
uint32_t Switches_Data();

#endif
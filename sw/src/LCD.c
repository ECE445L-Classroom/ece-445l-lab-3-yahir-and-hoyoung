// LCD.c
// Runs on the TM4C123
// Provides functions to display data to the LCD. 
// September 18, 2024

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/ST7735.h"
#include <stdio.h>





// Display Time on LCD
void DisplayTime(int8_t hour, int8_t minute, int8_t second){
	char str[16];
	sprintf(str, "%02d:%02d:%02d", hour, minute, second);
	ST7735_DrawString(5,5,str,ST7735_ORANGE);
	
}


// Create a menu to change ringtone
// Change color of clock 
// Display hour and minute hand
// Come up with a Menu (?) 

void DisplayClock(){
	

}
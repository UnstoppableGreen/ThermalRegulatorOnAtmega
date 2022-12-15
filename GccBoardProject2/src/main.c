#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>
#include "LCD.h"
#include "adc.h"

#define TempOnOff 0
#define PotateOnOff 1

// АЦП
// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))
#define COUNT_DRB 15 // порог считывания кнопки
#define ADC_PIN 3


uint16_t read_adc(uint8_t adc_input);

void StateTempRotate(bool stateTemp, bool statePotate);

int main(void) {
	_delay_ms(100);
	lcdInit();
	lcdClear();
	lcdSetDisplay(LCD_DISPLAY_ON);
	lcdSetCursor(LCD_CURSOR_OFF);
	char text[17];

	
	int adcValue;
	int temp;
	    
	ADC_Init();       /* Initialize the ADC module */
	
	
	//работа со светодиодами
	DDRF = 0b00000011;
	DDRA = 0b00000001;
	
	while (1)
	{
		adcValue = ADC_GetAdcValue(0); // Read the ADC value of channel zero(PA0) where the temperature sensor(LM35) is connected
        
        /* Convert the raw ADC value to equivalent temperature with 5v as ADC reference
		 Step size of AdC= (5v/1023)=4.887mv = 5mv.
		 for every degree celcius the Lm35 provides 10mv voltage change.
	     1 step of ADC=5mv=0.5'c, hence the Raw ADC value can be divided by 2 to get equivalent temp*/
        
       // temp = adcValue/2.0; // Divide by 2 to get the temp value.
		//strcpy(text, "ADC0 Value: " + adcValue);
		strcpy(text, adcValue);
		lcdGotoXY(0, 0);
		lcdPuts(text);
		//strcpy(text, "temp: " + temp);
		strcpy(text, temp);
		lcdGotoXY(1, 0);
		lcdPuts(text); 			
		//StateTempRotate(true, false); //работа устройств
	}
}

void StateTempRotate(bool stateTemp, bool statePotate){
	if (stateTemp) {
	PORTF |= 1<<TempOnOff;} //включаем
	else { PORTF &= ~(1<<TempOnOff);//выключаем
	}
	if (statePotate) {
	PORTF |= 1<<PotateOnOff;}//включаем
	else { PORTF &= ~(1<<PotateOnOff);//выключаем
	}
}


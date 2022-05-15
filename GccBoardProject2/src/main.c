#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>
#include "LCD.h"

#define TempOnOff 0
#define PotateOnOff 1

// ���
// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))
#define COUNT_DRB 15 // ����� ���������� ������
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
	strcpy(text, "    t = 10 C   ");
	lcdGotoXY(0, 0);
	lcdPuts(text);
	strcpy(text, " ProjByKursovik ");
	lcdGotoXY(1, 0);
	lcdPuts(text);
	

	//������ �� ������������
	DDRF = 0b00000011;
	while (1)
	{
		StateTempRotate(true, false); //������ ���������
	}
}

void StateTempRotate(bool stateTemp, bool statePotate){
	if (stateTemp) {
	PORTF |= 1<<TempOnOff;} //��������
	else { PORTF &= ~(1<<TempOnOff);//���������
	}
	if (statePotate) {
	PORTF |= 1<<PotateOnOff;}//��������
	else { PORTF &= ~(1<<PotateOnOff);//���������
	}
}

// Read the AD conversion result
uint16_t read_adc(uint8_t adc_input){
	uint16_t abc=0;
	ADMUX=adc_input | ADC_VREF_TYPE;
	// Delay needed for the stabilization of the ADC input voltage
	_delay_ms(10);
	// Start the AD conversion
	ADCSRA|=(1<<ADSC);
	// Wait for the AD conversion to complete
	while ((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	// warning
	abc=ADCL+ADCH;
return ADC;}

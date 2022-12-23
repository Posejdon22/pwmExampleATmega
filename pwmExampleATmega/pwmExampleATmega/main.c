/*
 * pwmExampleATmega.c
 *
 * Created: 23.12.2022 18:47:49
 * Author : mateu
 */ 

#define F_CPU 16000000UL             //define CPU frequency
#include "avr/io.h"
#include <util/delay.h>


void PWM_set(){                                 // PWM setup function
	DDRD |= (1<<PD7);                              //set PD7 as PWM output
	PORTD |= (1<<PD7);
	TCCR2 |= (1<<WGM20)|(1<<WGM21);                //select Fast PWM mode by setting bits
	TCCR2 |=(1<<COM21)|(1<<CS20)|(0<<CS21)|(0<<CS22);   //clear OC2 on compare match
}

void Input_set(){
	DDRD = DDRD & (~(1<<PD6));					//set PD2 as input
	PORTD |= (1<<PD6);							// pull-up
}

int main ()
{
	int duty = 0;
	uint8_t direction = 0;
	int pin_status_curret;
	int pin_status_old=0;
	
	PWM_set();         //call PWM setup function
	Input_set();
	while (1)
	{
		//OCR2=duty;     //slowly increase the LED brightness
		_delay_ms(10);
		pin_status_curret = PIND & (1<<PD6);
				
		if(pin_status_curret != pin_status_old){	
			if(direction == 0){
				direction=1;
			}
			else{
				direction = 0;
			}
		pin_status_old = pin_status_old;
		}

		if(direction == 1){
			if(duty<255){
				duty++;
				OCR2=duty;
			}
		}
		else{
			if(duty>0){
				duty--;
				OCR2=duty;
			}
		}
	}
}


/*
 * AnetE10_LimitSwitch.c
 *
 * Author : Веренич Николай
 */ 

#define F_CPU 9800000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/eeprom.h>

unsigned char			trigger; // объявляем глобальную 8-битную переменную
unsigned char EEMEM		trigger_ee;//объявляем её копию в памяти еепрома


void Init_Port (void){
	
	PORTB |= (1<<0);	// кнопка МИНУС
	PORTB |= (1<<1);	// кнопка ПЛЮС
	DDRB |= (1<<2);		// выход
						// вход АЦП
	DDRB |= (1<<4);		// индикаторный светодиод
	
}

void Init_ADC (void){

	ADMUX = (1<<MUX1)|                                             // два регистра MUX отвечающие за подтяжку ноги к АЦП
			(1<<MUX0)|
			(1<<ADLAR);
			
	ADCSRA = (0<<ADPS2)|
	         (0<<ADPS1)|
	         (1<<ADPS0)|    			//настройка частоты дискретизации АЦП
	         (1<<ADEN);                //включение АЦП
			 
	DIDR0 =  (1<<ADC2D);
	
}
uint8_t ADC_Read (void){
	    
	ADCSRA |=(1<<ADSC);	                                     //запуск преобразования АЦП
	while(!(ADCSRA & (1<<ADIF)));							 //окончание преобразования АЦП
	return ADCH;                                            //ADCH - регистр хранения прочитанного

}





uint16_t resalt_adc;


int main(void)
{
    Init_Port();
	Init_ADC();
	
// 		    TCCR0A = (1<<COM0A1)|(0<<COM0A0)| // подключение пина B0
// 		    (1<<WGM01)|(1<<WGM00); // установка режима Fast PWM
// 		    TCCR0B = (1<<CS02)|(0<<CS01)|(1<<CS00); //предделитель

	trigger = eeprom_read_byte (&trigger_ee); // записали значение из еепрома в переменную
		    
	
    while (1) 
    {
		resalt_adc = ADC_Read();
		
		if (trigger == resalt_adc)		PORTB |= (1<<2);
		else							PORTB &= ~(1<<2);
		
		if(!(PINB&(1<<1)))	{
			trigger = trigger + 10;
			if(trigger >= 256)	trigger = 255;
			
			PORTB |= (1<<4);
			_delay_ms(100);
			PORTB &= ~(1<<4);
			
			eeprom_write_byte (& trigger_ee, trigger);
			
			
		}
		if(!(PINB&(1<<0)))	{
			trigger = trigger - 10;
			if(trigger <= 0)	trigger = 0;
			
			PORTB |= (1<<4);
			_delay_ms(100);
			PORTB &= ~(1<<4);
			
			eeprom_write_byte (& trigger_ee, trigger);
			
			
		}

	




    }
}


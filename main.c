/*
 * main.c
 *
 *  Created on: Feb 19, 2021
 *      Author: dell
 */



#include"Library.h"


void PWM_Timer0_Init(uint8 set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = set_duty_cycle; // Set Compare Value

	SET_BIT(DDRB,PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
	DDRB|=(1<<PB0)|(1<<PB1);
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}


/*INT1 function*/
void INT1_Init(void)
{
    SET_BIT(SREG,7);                           //	SREG  |= (1<<7);

	MCUCR |= (1<<ISC10) | (1<<ISC11);          // Trigger INT1 with the raising edge

	GICR  |= (1<<INT1);                        // Enable external interrupt pin INT1

}


/*ISR of INT1*/

ISR(INT1_vect)
{
	volatile uint16 res_value;


	 LCD_goToRowColumn(0,12); /* display the number every time at this position */
     res_value = ADC_readchannel(0); /* read channel zero where the potentiometer is connect */

     PWM_Timer0_Init((res_value)/4);

     TOGGLE_BIT(PORTB,PB0);
     TOGGLE_BIT(PORTB,PB1);

     LCD_intgerToString(res_value); /* display the ADC value on LCD screen */
}




int main(void)
{

	INT1_Init();                             /*initialize INT1*/

	uint16 res_value;
	SET_BIT(DDRB,PB1);
	CLEAR_BIT(DDRD,PD3);


	ADC_init(); 							 /* initialize ADC driver */
	LCD_init();                              /* initialize LCD driver */

	LCD_clearScreen();                       /* clear LCD at the beginning */

	LCD_displayString("ADC Value = ");       /* display this string "ADC Value = " only once at LCD */


	SET_BIT(PORTB,PB0);                      /* motors will spin with clockwise */

    while(1)
    {
		LCD_goToRowColumn(0,12);             /* display the number every time at this position */

		res_value = ADC_readchannel(0); /* read channel zero where the potentiometer is connect */

		PWM_Timer0_Init((res_value)/4);

		LCD_intgerToString(res_value); /* display the ADC value on LCD screen */

    }
}





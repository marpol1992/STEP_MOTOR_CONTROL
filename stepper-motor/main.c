/*
 * stepper-motor.c
 *
 * Created: 23.11.2016 18:21:56
 * Author : marek
 */ 

#include <avr/io.h>
#include "stepmotor.h"
#include <util/delay.h>
#include <avr/interrupt.h>

STEPPER_OBJECT _obj;

int main(void)
{
	 OSC.CTRL     =    OSC_RC32MEN_bm;       // w??czenie oscylatora 32MHz
	 while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // czekanie na ustabilizowanie si? generatora
	 CPU_CCP      =    CCP_IOREG_gc;         // odblokowanie zmiany ?ród?a sygna?u
	 CLK.CTRL     =    CLK_SCLKSEL_RC32M_gc; // zmiana ?ród?a sygna?u na RC 32MHz
	 
	 TCC0.INTCTRLA     =   TC_TC0_OVFINTLVL_LO_gc;         // przepe³nienie ma generowaæ przerwanie LO
	 PMIC.CTRL         =    PMIC_LOLVLEN_bm;            // odblokowanie przerwañ o priorytecie LO
	               
	 TCC0.CTRLB        =    TC_TC0_WGMODE_NORMAL_gc;        // tryb normalny
	 // TCC0.CTRLFSET     =    TC0_DIR_bm;                 // liczenie w dó³
	 TCC0.CTRLA        =    TC_TC0_CLKSEL_DIV256_gc;       // ustawienie preskalera i uruchomienie timera
	 TCC0.PER    =   100;
	 
		PORTE.DIRSET	=	PIN0_bm|PIN1_bm|PIN2_bm|PIN3_bm|PIN4_bm;
		PORTE.DIRCLR    =   PIN5_bm;
		PORTE.PIN5CTRL	=	PORT_OPC_PULLUP_gc;	
		uint16_t t = 1250;
		STEPMOTOR_move_forward(&_obj,4,5);
    /* Replace with your application code */
	sei();    
    while (1) 
    {
		if(!(PORTE.IN & PIN5_bm)) /* je?eli przycisk FLIP jest wci?ni?ty*/ {
			while(1){
				uint32_t licz;
				licz++;
				if((licz>15100)&&(PORTE.IN & PIN5_bm)){
					licz=0;
					TCC0.PER=TCC0.PER-1;
					break;
				}
				
			}
		}
		
		//odbiera dane ktore mowia o ile cm ma sie przesunac do przodu albo do ty³u
		//
		

	}
}

static uint8_t counter = 0;
ISR(TCC0_OVF_vect)
{   
	if (counter>=8)
	{
		counter = 0;
	}
	counter++;
	switch(counter){
		case 1:{
			MOTOR_PIN1_ON;
			MOTOR_PIN2_OFF;
			MOTOR_PIN3_ON;
			MOTOR_PIN4_OFF;
			break;
		}
		case 2:{
			MOTOR_PIN1_ON;
			MOTOR_PIN2_OFF;
			MOTOR_PIN3_ON;
			MOTOR_PIN4_ON;
			break;
		}
		case 3:{
			MOTOR_PIN1_ON;
			MOTOR_PIN2_OFF;
			MOTOR_PIN3_OFF;
			MOTOR_PIN4_ON;
			break;
		}
		case 4:{
			MOTOR_PIN1_ON;
			MOTOR_PIN2_ON;
			MOTOR_PIN3_OFF;
			MOTOR_PIN4_ON;
			break;
		}
		case 5:{
			MOTOR_PIN1_OFF;
			MOTOR_PIN2_ON;
			MOTOR_PIN3_OFF;
			MOTOR_PIN4_ON;
			break;
		}
		case 6:{
			MOTOR_PIN1_OFF;
			MOTOR_PIN2_ON;
			MOTOR_PIN3_ON;
			MOTOR_PIN4_ON;
			break;
		}
		case 7:{
			MOTOR_PIN1_OFF;
			MOTOR_PIN2_ON;
			MOTOR_PIN3_ON;
			MOTOR_PIN4_OFF;
			break;
		}
		case 8:{
			MOTOR_PIN1_ON;
			MOTOR_PIN2_ON;
			MOTOR_PIN3_ON;
			MOTOR_PIN4_OFF;
			break;
		}
		default:{
			for(int i = 0; i<counter;i++){
			TEST_GL;
			_delay_ms(1000);
			}
			break;
		}
	}
}
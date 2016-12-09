/*
 * CFile1.c
 *
 * Created: 2015-07-20 17:49:50
 *  Author: marek
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

void timer(void)
{
	
	TCC0.INTCTRLA     =    TC_OVFINTLVL_LO_gc;         // przepe�nienie ma generowa� przerwanie LO
	PMIC.CTRL         =    PMIC_LOLVLEN_bm;            // odblokowanie przerwa� o priorytecie LO
	sei();                                             // globalne odblokowanie przerwa�
	
	// konfiguracja timera
	TCC0.CTRLB        =    TC_WGMODE_NORMAL_gc;        // tryb normalny
	// TCC0.CTRLFSET     =    TC0_DIR_bm;                 // liczenie w d�
	TCC0.CTRLA        =    TC_CLKSEL_DIV64_gc;       // ustawienie preskalera i uruchomienie timera
	TCC0.PER    =    50;
}



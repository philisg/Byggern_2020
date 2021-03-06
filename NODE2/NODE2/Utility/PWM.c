#include "PWM.h"

void PWM_init(void)
{
	PIOC->PIO_PDR |= PIO_PDR_P19;
	PIOC->PIO_ABSR |= PIO_ABSR_P19; //PC19 = pin 44 on shield
	PIOC->PIO_PDR |= PIO_PDR_P18;
	PIOC->PIO_ABSR |= PIO_ABSR_P18; //PC18 = pin 45 on shield
	
	PWM->PWM_WPCR = PWM_WPCR_WPKEY(0x50574D)| PWM_WPCR_WPRG0 |PWM_WPCR_WPRG2|PWM_WPCR_WPRG3;//Enables writing to register group 0,2,3
	
	PWM->PWM_CLK = PWM_CLK_DIVA(28)| PWM_CLK_PREA(0); //PWM_CLK = MCK = 84MHz
	PMC->PMC_PCER1 |= (1 << 4); //Enable PWM clock
	REG_PWM_CMR5 = 0xB | 1 << 9; //CLKA, Polatity start high
	REG_PWM_CPRD5 = 60000;
	REG_PWM_CDTY5 = 4500; // Hver verdi tilsvarer 1us
	REG_PWM_CMR6 = 0xB | 1 << 9; //CLKA, Polatity start high
	REG_PWM_CPRD6 = 60000;
	REG_PWM_CDTY6 = 4500;
	PWM->PWM_ENA |= PWM_ENA_CHID5;
	PWM->PWM_ENA |= PWM_ENA_CHID6;
}

void PWM_set_duty_cycle(uint16_t us, uint8_t channel)
{
	if(us < 900)
	{
		us = 900; //Lowest duty-cycle
	}
	else if(us > 2100)
	{
		us = 2100; //highest duty-cycle
	}
	if (channel == 5)
	{
		REG_PWM_CDTY5 = 3*us; // Hver verdi tilsvarer 1us
	}
	else if(channel == 6)
	{
		REG_PWM_CDTY6 = 3*us; // Hver verdi tilsvarer 1us
	}
}

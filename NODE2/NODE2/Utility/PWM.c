/**
 * @file PWM.c
 * @author TTK4155 2020 Group 28
 * @date 17 nov 2020
 * @brief File containing drivers for PWM.
 */

#include "PWM.h"

void PWM_init(void)
{
	PIOC->PIO_PDR |= PIO_PDR_P19; //Disable pio control
	PIOC->PIO_ABSR |= PIO_ABSR_P19; //Set PIO multiplexer to B
	PIOC->PIO_PDR |= PIO_PDR_P18; //Disable pio contorl
	PIOC->PIO_ABSR |= PIO_ABSR_P18; //Set PIO multiplexer to B
	
	PWM->PWM_WPCR = PWM_WPCR_WPKEY(0x50574D)| PWM_WPCR_WPRG0 |PWM_WPCR_WPRG2|PWM_WPCR_WPRG3;//Enables writing to register group 0,2,3
	
	PWM->PWM_CLK = PWM_CLK_DIVA(28)| PWM_CLK_PREA(0); //PWM_CLK = 3MHz
	PMC->PMC_PCER1 |= (1 << 4); //Enable PWM clock
	REG_PWM_CMR5 = 0xB | 1 << 9; //CLKA, Polatity start high
	REG_PWM_CPRD5 = 60000; // Set period to 20 ms. 60 000 = 20ms * 1000 * 3
	REG_PWM_CDTY5 = 4500; // Set duty-cycle to 1,5ms. 4500 = 1,5 * 1000 * 3
	REG_PWM_CMR6 = 0xB | 1 << 9; //CLKA, Polatity start high
	REG_PWM_CPRD6 = 60000; // Set period to 20 ms. 60 000 = 20ms * 1000 * 3
	REG_PWM_CDTY6 = 4500; // Set duty-cycle to 1,5ms. 4500 = 1,5 * 1000 * 3
	PWM->PWM_ENA |= PWM_ENA_CHID5; //Enable PWM channel 5
	PWM->PWM_ENA |= PWM_ENA_CHID6; //Enable PWM channel 5
}

void PWM_set_duty_cycle(uint16_t us, uint8_t channel) // function to make sure the PWM signal is in the range [0,9ms - 2,1ms]
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
		REG_PWM_CDTY5 = 3*us; //Set new duty-cycle
	}
	else if(channel == 6)
	{
		REG_PWM_CDTY6 = 3*us; //Set new duty-cycle
	}
}

/**
 * @file Timer.c
 * @author TTK4155 2020 Group 28
 * @date 17 nov 2020
 * @brief File containing drivers for timers.
 */

#include "sam.h"
#include <stdio.h>
#include "Timer.h"


void TC0_init(uint32_t periode) //Period in us
{
	NVIC_EnableIRQ(TC0_IRQn); // Enable TC0 IRQ
	REG_PMC_PCER0 |= PMC_PCER0_PID27; // Enable TC0 clock in PMC
	//mainclock div 8 => 10.5MHz
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK2;
	//compare resets counter and clock
	REG_TC0_CMR0 |= TC_CMR_CPCTRG;
	//enable RC compare interrupt
	REG_TC0_IER0 |= TC_IER_CPCS;
	//enable tc clock
	REG_TC0_CCR0 |= TC_CCR_CLKEN;

	uint32_t tick = periode / 0.095;// every tick == 1/f second.  => time = number of ticks / f => number of ticks = time * f
	// wants 2 us. Timer goes in a period of 0.095us
	// We have to wait 2/0.0.95 tick ~= 5

	REG_TC0_RC0 = tick;
}

void TC1_init(uint32_t periode) //Period in us
{
	NVIC_EnableIRQ(TC3_IRQn); // Enable TC3 IRQ
	REG_PMC_PCER0 |= PMC_PCER0_PID30; // Enable TC3 clock in PMC
	//mainclock div 8 => 10.5MHz
	REG_TC1_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK2;
	//compare resets counter and clock
	REG_TC1_CMR0 |= TC_CMR_CPCTRG;
	//enable RC compare interrupt
	REG_TC1_IER0 |= TC_IER_CPCS;
	//enable tc clock
	REG_TC1_CCR0 |= TC_CCR_CLKEN;

	uint32_t tick = periode / 0.095; // every tick == 1/f second.  => time = number of ticks / f => number of ticks = time * f
	// wants 2 us. Timer goes in a period of 0.095us
	// We have to wait 2/0.0.95 tick ~= 5
	REG_TC1_RC0 = tick;
}

void TC2_init(uint32_t periode) //Period in us
{
	NVIC_EnableIRQ(TC6_IRQn); // Enable TC3 IRQ
	REG_PMC_PCER1 |= PMC_PCER1_PID33; // Enable TC3 clock in PMC
	//mainclock div 8 => 10.5MHz
	REG_TC2_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK2;
	//compare resets counter and clock
	REG_TC2_CMR0 |= TC_CMR_CPCTRG;
	//enable RC compare interrupt
	REG_TC2_IER0 |= TC_IER_CPCS;
	//enable tc clock
	REG_TC2_CCR0 |= TC_CCR_CLKEN;

	uint32_t tick = periode / 0.095; // every tick == 1/f second.  => time = number of ticks / f => number of ticks = time * f
	// wants 2 us. Timer goes in a period of 0.095us
	// We have to wait 2/0.0.95 tick ~= 5
	REG_TC2_RC0 = tick;
}

void Timer_start(int timer)
{
	switch(timer)
	{
		case TIMER0:
			REG_TC0_CCR0 = TC_CCR_CLKEN;
			REG_TC0_CCR0 |= TC_CCR_SWTRG;
		break;

		case TIMER1:
			REG_TC1_CCR0 = TC_CCR_CLKEN;
			REG_TC1_CCR0 |= TC_CCR_SWTRG;
		break;
		
		case TIMER2:
			REG_TC2_CCR0 = TC_CCR_CLKEN;
			REG_TC2_CCR0 |= TC_CCR_SWTRG;
		break;
		
	}
}

void Timer_stop(int timer)
{
	switch(timer)
	{
		case TIMER0:
			REG_TC0_CCR0 |= TC_CCR_CLKDIS;
		break;

		case TIMER1:
			REG_TC1_CCR0 |= TC_CCR_CLKDIS;
		break;

		case TIMER2:
			REG_TC2_CCR0 |= TC_CCR_CLKDIS;
		break;
	}
}

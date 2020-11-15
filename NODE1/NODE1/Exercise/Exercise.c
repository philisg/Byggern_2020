

#include "../main.h"
#ifdef EX
void Exercise1(void)
{
	UART_init(UBRR);
	
	printf("Write some input: \n");
	
	char s[100];
	gets(s);
	
	printf("Your input was: %s", s);	
}

void Exercise2(void)
{
	UART_init(UBRR);
	SRAM_init();
	SRAM_test();
}

void Exercise3(void)
{
	UART_init(UBRR);
	SRAM_init();

	Joystick_init();
	slider_init();
}

void Exercise4(void)
{
	
	GPIO_init();
	UART_init(UBRR);
	SRAM_init();
	Joystick_init();
	slider_init();
	OLED_init();
	Menu_init();

	while(1)
	{
		Menu_selection();
		_delay_ms(150);
	}
}

void Exercise5(void)
{
	
	GPIO_init();	
	UART_init(UBRR);
	SRAM_init();
	Joystick_init();
	slider_init();
	OLED_init();
	Menu_init();
		
	CAN_init(MODE_LOOPBACK);
	
	CAN_MESSAGE msg;
	msg.ID = '5';
	strcpy(msg.data, "TEST");
	msg.data_length = 4;
	
	CAN_send(&msg);
	
	while(1)
	{
		CAN_send(&msg);
		_delay_ms(500);
	}
}

void Exercise6(void)
{
	GPIO_init();	
	UART_init(UBRR);
	SRAM_init();
	Joystick_init();
	slider_init();
	OLED_init();
	Menu_init();
		
	CAN_init(MODE_NORMAL);
	
	Joystick_pos_t j_pos;
	CAN_MESSAGE msg;
	msg.ID = '6';
	msg.data_length = 1;
		
	while(1)
	{
		j_pos = Joystick_get_position();
		msg.data[0] = j_pos.x_pos;
		CAN_send(&msg);
		_delay_ms(500);
	}	
}

void Exercise7(void)
{
	GPIO_init();
	UART_init(UBRR);
	SRAM_init();
	Joystick_init();
	slider_init();
	OLED_init();
	Menu_init();
		
	CAN_init(MODE_NORMAL);
		
	Joystick_pos_t j_pos;
	CAN_MESSAGE msg;
	msg.ID = '6';
	msg.data_length = 1;
		
	while(1)
	{
		j_pos = Joystick_get_position();
		msg.data[0] = j_pos.x_pos;
		CAN_send(&msg);
		_delay_ms(500);
	}
}
#endif
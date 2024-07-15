/*
 * Gpio.c
 *
 * Created: 1/15/2021 4:06:31 AM
 *  Author: karim hassan
 */ 

#include "Gpio.h"


volatile uchar8 *register_direction[4] = {&DDRA , &DDRB , &DDRC , &DDRD};
volatile uchar8 *register_data[4] = {&PORTA , &PORTB , &PORTC , &PORTD};
volatile uchar8 *register_input[4] = {&PINA , &PINB , &PINC , &PIND};
	


void initialize_pin(uchar8 reg , uchar8 pin , uchar8 dir)
{
	
	PIN_WRITE(*register_direction[reg] , pin , dir);
	
}



void initialize_port(uchar8 reg , uchar8 dir)
{
	
	WRITE_PORT(*register_direction[reg] , dir);
	
}


void initialize_port_mask(uchar8 reg , uchar8 dir)
{
	
	PORT_MASK(*register_direction[reg] , dir);
	
}


void io_write_pin(uchar8 reg , uchar8 pin , uchar8 val)
{
	
      PIN_WRITE(*register_data[reg] , pin , val);
	
}



void io_write_port(uchar8 reg , uchar8 data)
{
	
	WRITE_PORT(*register_data[reg] , data);
	
}



void io_write_port_mask(uchar8 reg , uchar8 data)
{
	
	PORT_MASK(*register_data[reg] , data);
	
}



void io_write_port_clear(uchar8 reg , uchar8 data)
{
	
	PORT_CLEAR_MASK(*register_data[reg] , data);
	
}



uchar8 read_pin(uchar8 reg , uchar8 pin)
{
	
	return GET_PIN(*register_input[reg] , pin);
	
}


uchar8 read_port(uchar8 reg)
{
	
	return ReadPort(*register_input[reg]);
	
}


void read_pin_argument(uchar8 reg , uchar8 pin , uchar8 *data)
{
	
	*data = GET_PIN(*register_input[reg] , pin);
	
}



void read_port_argument(uchar8 reg , uchar8 port , uchar8 *val)
{
	
	*val = GET_PIN(*register_input[reg] , port);
	
}


void gpio_set_pullup(uchar8 reg, uchar8 pin)
{
	
		PIN_WRITE(*register_data[reg] , pin , HIGH);
	
}


void gpio_set_pulldown(uchar8 reg, uchar8 pin)
{
	
		PIN_WRITE(*register_data[reg] , pin , LOW);

}









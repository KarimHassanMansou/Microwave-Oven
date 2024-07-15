/*
 * LED.c
 *
 * Created: 1/16/2021 3:09:08 AM
 *  Author: karim hassan
 */ 

#include "LED.h"



void LED_INIT(uchar8 port , uchar8 pin , uchar8 dir)
{
	
	initialize_pin(port , pin , dir);
	
}


void LEDS_INIT(uchar8 port , uchar8 dir)
{
	
	initialize_port(port , dir);
	
}


void LED_ON(uchar8 port , uchar8 pin)
{
	
	io_write_pin(port , pin , HIGH);
	
}


void LED_OFF(uchar8 port , uchar8 pin)
{
	
	io_write_pin(port , pin , LOW);
	
}


void LEDS_ON(uchar8 port)
{
	
	io_write_port_mask(port , HIGH);
	
}


void LEDS_OFF(uchar8 port)
{
	
	io_write_port_mask(port , LOW);
	
}








/*
 * Gpio.h
 *
 * Created: 1/15/2021 4:07:05 AM
 *  Author: karim hassan
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "utils.h"
#include "standard types.h"
#include "MCAL REGISTERS.h"


#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

#define HIGH 1
#define LOW  0

#define OUTPUT 1
#define INPUT  0

#define PORT_HIGH 0xFF
#define PORT_LOW  0x00

#define PORT_OUTPUT 0xFF
#define PORT_INPUT  0x00


typedef enum
{
	GPIO_A,
	GPIO_B,
	GPIO_C,
	GPIO_D,

}port_name_t;


typedef enum gpioerror
{
	
	S_PASS=1,
	F_PASS
}gpio_error_t;


/*************initialization***************/

void initialize_pin(uchar8 reg , uchar8 pin , uchar8 dir);

void initialize_port(uchar8 reg , uchar8 data);

void initialize_port_mask(uchar8 reg , uchar8 data);


/*************write**************/

void io_write_pin(uchar8 reg , uchar8 pin , uchar8 val);

void io_write_port(uchar8 reg , uchar8 data);

void io_write_port_mask(uchar8 reg , uchar8 data);

void io_write_port_clear(uchar8 reg , uchar8 data);

void io_SET_PULLUP(uchar8 reg , uchar8 pin , uchar8 val);


/************read*************/

uchar8 read_pin(uchar8 reg , uchar8 pin);

uchar8 read_port(uchar8 reg);

void read_pin_argument(uchar8 reg , uchar8 pin , uchar8 *data);

void read_port_argument(uchar8 reg , uchar8 port , uchar8 *val);


void gpio_set_pullup(uchar8 reg, uchar8 pin);

void gpio_set_pulldown(uchar8 reg, uchar8 pin);

#endif /* GPIO_H_ */
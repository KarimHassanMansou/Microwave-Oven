/*
 * LED.h
 *
 * Created: 1/16/2021 3:15:43 AM
 *  Author: karim hassan
 */ 


#ifndef LED_H_
#define LED_H_

#include "Gpio.h"



void LED_INIT(uchar8 port , uchar8 pin , uchar8 dir);

void LEDS_INIT(uchar8 port , uchar8 dir);

void LED_ON(uchar8 port , uchar8 pin);

void LED_OFF(uchar8 port , uchar8 pin);

void LEDS_ON(uchar8 port);

void LEDS_OFF(uchar8 port);



#endif /* LED_H_ */
/*
 * LCD.h
 *
 * Created: 1/20/2021 12:22:54 AM
 *  Author: karim hassan
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Gpio.h"


#define LCD_PORT         GPIO_A
#define LCD_PORT_CONTROL GPIO_B

/************LCD port***********/
#define D0 PIN_0
#define D1 PIN_1
#define D2 PIN_2
#define D3 PIN_3
#define D4 PIN_4
#define D5 PIN_5
#define D6 PIN_6
#define D7 PIN_7

/**********LCD port control**********/
#define Enable    PIN_0 
#define ReadWrite PIN_1  
#define Regselect PIN_2


/*************prototypes***************/
void LCD_WRITE_COMMAND(uchar8 command);

void LCD_INIT();

void LCD_WRITE_DATA(uchar8 data);

void LCD_WRITE_CHAR(uchar8 character);

void LCD_WRITE_STRING(uchar8 *string);

void LCD_CLEAR();

void LCD_WRITE_NUMBER(uchar8 number);

void LCD_GoTo(uchar8 line  , uchar8 pos);


#endif /* LCD_H_ */
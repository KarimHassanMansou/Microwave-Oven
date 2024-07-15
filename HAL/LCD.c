/*
 * LCD.c
 *
 * Created: 1/20/2021 12:22:29 AM
 *  Author: karim hassan
 */ 

#include "LCD.h"
#include <util/delay.h>



void LCD_WRITE_COMMAND(uchar8 command)
{
	
	io_write_port(LCD_PORT , command);
	
	io_write_pin(LCD_PORT_CONTROL , Regselect , LOW);
	
	io_write_pin(LCD_PORT_CONTROL , ReadWrite , LOW);
	
	io_write_pin(LCD_PORT_CONTROL , Enable , HIGH);
	
	_delay_ms(2);
	
	io_write_pin(LCD_PORT_CONTROL , Enable , LOW);
	
	_delay_ms(2);
	
}





void LCD_INIT()
{
	
	initialize_port(LCD_PORT , HIGH);
	
	initialize_pin(LCD_PORT_CONTROL , Regselect , OUTPUT);
	
    initialize_pin(LCD_PORT_CONTROL , ReadWrite , OUTPUT);
	
	initialize_pin(LCD_PORT_CONTROL , Enable , OUTPUT);
	
	io_write_pin(LCD_PORT_CONTROL , ReadWrite , LOW);
	
	_delay_ms(50);
	
	LCD_WRITE_COMMAND(0x38);
	
	_delay_ms(2);
	
	LCD_WRITE_COMMAND(0x0F);
	
	_delay_ms(2);
	
	LCD_WRITE_COMMAND(0x01);
	
	_delay_ms(20);
	
	LCD_WRITE_COMMAND(0x80);
	
	
}





void LCD_WRITE_DATA(uchar8 data)
{
	
	io_write_port(LCD_PORT , data);
	
	io_write_pin(LCD_PORT_CONTROL , ReadWrite , LOW);
	
	io_write_pin(LCD_PORT_CONTROL , Regselect , HIGH);
	
	io_write_pin(LCD_PORT_CONTROL , Enable , HIGH);
	
	_delay_ms(2);
	
	io_write_pin(LCD_PORT_CONTROL , Enable , LOW);
	
	_delay_ms(2);
	
}



void LCD_WRITE_CHAR(uchar8 character)
{
	
	LCD_WRITE_DATA(character);
	
}


void LCD_WRITE_STRING(uchar8 *string)
{
	
	int counter;
	
	while (string[counter] != '\0')
	{
		LCD_WRITE_CHAR(string[counter]);
		counter++;
	}
	
}




void LCD_GoTo(uchar8 line  , uchar8 pos)/*pos = position in line*/
{

	switch(line)
	{

		case 1:
		LCD_WRITE_COMMAND(pos + 0x80);//line one
		break;

		case 2:
		LCD_WRITE_COMMAND(pos + 0xC0);//line two
		break;

	}

}





void LCD_CLEAR()
{
	LCD_WRITE_COMMAND(0x01);
}




void LCD_WRITE_NUMBER(uchar8 number)
{
	
	uchar8 str[10];
	
	sprintf(str , "%d" , number);
	
	LCD_WRITE_STRING(str);
	
}




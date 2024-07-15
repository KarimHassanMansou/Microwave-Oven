/*
 * new_application.c
 *
 * Created: 1/15/2021 2:57:51 AM
 *  Author: karim hassan
 */ 
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include "Gpio.h"
#include "LED.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"




int INT_KEY = 0;
int Door_flag = 0;

uchar8 key[1];
uchar8 key2;

uchar8 button = 0;
uchar8 ss_switch;

unsigned long int minutes_int = 0;
unsigned long int seconds_int = 0;

int i;
int j;


void STOP(void);
void thirty_seconds(void);


int main(void)
{
	
	
	KEYPAD_INIT();
	LCD_INIT();
	
	
	MGIE_voidEnable();
	MEXTI_voidINT0init();//peripheral interrupt enable
	
	initialize_pin(GPIO_D , PIN_0 , OUTPUT);//yellow led
    initialize_pin(GPIO_D , PIN_1 , OUTPUT);//emitter
	initialize_pin(GPIO_D , PIN_7 , OUTPUT);//DC motor
	
	initialize_pin(GPIO_B , PIN_3 , OUTPUT);//BUZZER
	
	initialize_pin(GPIO_B , PIN_7 , INPUT);//microwave door
	io_write_pin(GPIO_B , PIN_7 , HIGH);//input pull up
	
	initialize_pin(GPIO_D , PIN_3 , INPUT);//microwave door
	io_write_pin(GPIO_D , PIN_3 , HIGH);//input pull up
	
	INI0_set_call_back(&STOP);//INTERRUPT
	
	io_write_pin(GPIO_B , PIN_3 , HIGH);//buzzer
	_delay_ms(3000);
	io_write_pin(GPIO_B , PIN_3 , LOW);//buzzer
	
	while(1)
	{
	    	
		LCD_WRITE_STRING("     welcome");
		LCD_WRITE_COMMAND(0x0C);//turn off cursor
		
		_delay_ms(9000);
		
		LCD_CLEAR();
		_delay_ms(200);
		
		
		jump1:
		
		door:
		
		door2:
		
		LCD_WRITE_STRING("CLOSE THE DOOR");
		
		read_pin_argument(GPIO_B , PIN_7 , &button); //microwave Door
		
		if (button == 0)
		{
			
			reenter:
			
			LCD_CLEAR();
			_delay_ms(300);
			
			label:
			
			LCD_WRITE_STRING("Enter no of mins:");
			LCD_WRITE_COMMAND(0xC0);
			LCD_WRITE_COMMAND(0x0F);
			
			for(int K=0 ; K<1 ; K++)
			{
				
				key[K] = GET_PRESSED();	
				LCD_WRITE_CHAR(key[K]);
					
				_delay_ms(3000);
					
				if (key[K] == '#' ||  key[K] == '0' /*||  key[K] == '*'*/)
				{
						
					LCD_CLEAR();
					_delay_ms(300);
						
					LCD_WRITE_COMMAND(0x0C);
						
					LCD_WRITE_STRING("invalid number");
					_delay_ms(9000);
						
					goto reenter;
						
				}
				
				if (key[K] == '*')
				{
						
					thirty_seconds();
					
					if (Door_flag == 2)
					{
						
						goto door2;
						
					}
						
					goto end_func;
					
				}
					
				
			}
			
			INT_KEY = atoi(key);//convert from char to int
			
			key2 = GET_PRESSED();//second number 
			
			if (key2 == '#')
			{
		
				LCD_WRITE_COMMAND(0x0C);
				
				LCD_CLEAR();
				_delay_ms(300);
				
				io_write_pin(GPIO_D , PIN_7 , HIGH);
				io_write_pin(GPIO_D , PIN_0 , HIGH);
				io_write_pin(GPIO_D , PIN_1 , HIGH);
				
				
				for (i=INT_KEY ; i>0 ; i--)
				{
					
					for(j=59 ; j>=0 ; j--)
					{	
						
						 
						minutes_int = i-1;
						seconds_int = j;
						
			           	read_pin_argument(GPIO_B , PIN_7 , &button);
			           	
			           	if (button == 1)
			           	{
				           	
				          io_write_pin(GPIO_D , PIN_7 , LOW);
				          io_write_pin(GPIO_D , PIN_0 , LOW);
				          io_write_pin(GPIO_D , PIN_1 , LOW);

				          goto door;
			            }
						
					   check:
					   
					   read_pin_argument(GPIO_D , PIN_3 , &ss_switch);
					   
					   if (ss_switch == 0)
					   {
						   
						   io_write_pin(GPIO_D , PIN_7 , LOW);
						   io_write_pin(GPIO_D , PIN_0 , LOW);
						   io_write_pin(GPIO_D , PIN_1 , LOW);
						   
						   LCD_WRITE_STRING("   Time =");
						   
						   LCD_WRITE_STRING("                ");
						   LCD_WRITE_COMMAND(0xC0);
						   LCD_WRITE_STRING("                ");
						   
						   
						   LCD_WRITE_STRING("   Time =");
						   
						   LCD_GoTo(1 , 10);
						   LCD_WRITE_NUMBER(minutes_int);
						   LCD_WRITE_CHAR(':');
						   LCD_GoTo(1  , 12);
						   
						   if (j<10)
						   {
							   LCD_WRITE_NUMBER(0);
							   LCD_WRITE_NUMBER(seconds_int);
						   }
						   else
						   {
							   LCD_WRITE_NUMBER(seconds_int);
						   }
						   
						   goto check;//to handle switch bugs
						  
					   }
					   else if (ss_switch == 1)
					   {
						   
						   io_write_pin(GPIO_D , PIN_7 , HIGH);
						   io_write_pin(GPIO_D , PIN_0 , HIGH);
						   io_write_pin(GPIO_D , PIN_1 , HIGH);
						   
					   }
					   
					   LCD_WRITE_STRING("   Time =");
						
					   LCD_GoTo(1 , 10);
					   LCD_WRITE_NUMBER(i-1);
					   LCD_WRITE_CHAR(':');
					   LCD_GoTo(1  , 12);
						
					   if (j<10)
					   {
						   LCD_WRITE_NUMBER(0);
						   LCD_WRITE_NUMBER(j);
					   }
					   else
					   {
						   LCD_WRITE_NUMBER(j);
					   }
					   
					   _delay_ms(8000);
					  
						
					   LCD_CLEAR();
					   _delay_ms(100);
						
					}
					
				}
				
				
				end_func:
				
				io_write_pin(GPIO_D , PIN_7 , LOW);
				io_write_pin(GPIO_D , PIN_0 , LOW);
				io_write_pin(GPIO_D , PIN_1 , LOW);
				
				LCD_WRITE_STRING("  OPEN THE DOOR");
				
				io_write_pin(GPIO_B , PIN_3 , HIGH);//BUZZER
				_delay_ms(4000);
				io_write_pin(GPIO_B , PIN_3 , LOW);
		        _delay_ms(6000);
				io_write_pin(GPIO_B , PIN_3 , HIGH);
				_delay_ms(4000);
				io_write_pin(GPIO_B , PIN_3 , LOW);
		        _delay_ms(6000);
				io_write_pin(GPIO_B , PIN_3 , HIGH);
				_delay_ms(4000);
				io_write_pin(GPIO_B , PIN_3 , LOW);
				_delay_ms(6000);
				io_write_pin(GPIO_B , PIN_3 , HIGH);
				_delay_ms(4000);
				io_write_pin(GPIO_B , PIN_3 , LOW);
				_delay_ms(6000);
				
				
				LCD_WRITE_STRING("  OPEN THE DOOR");
				_delay_ms(9000);
				
				read_pin_argument(GPIO_B , PIN_7 , &button);//microwave Door
				
				if(button == 1)
				{
					goto jump1;
				}
				else if(button == 0)
				{
					_delay_ms(8000);
				}
				
				
			}
			else if (key2 == '*' || key2 == '0' || key2 == '1' || key2 == '2' || key2 == '3' || key2 == '4' ||
			         key2 == '5' || key2 == '6' || key2 == '7' || key2 == '8' || key2 == '9')
			{
			
			    LCD_CLEAR();
				_delay_ms(300);
			    	
				goto label;
				
			}
			
		}
		
		
	}
	
}





void thirty_seconds(void)
{
	
	minutes_int = 0;
	
	LCD_CLEAR();
	_delay_ms(100);
	
	LCD_WRITE_COMMAND(0x0C);
		
	for(int counter = 30 ; counter > 0 ; counter--)
	{	
		  
		  seconds_int = counter;
		  
		  read_pin_argument(GPIO_B , PIN_7 , &button);
		   	
		  if (button == 1)
		  {
			   	
			  io_write_pin(GPIO_D , PIN_7 , LOW);
			  io_write_pin(GPIO_D , PIN_0 , LOW);
			  io_write_pin(GPIO_D , PIN_1 , LOW);

			  Door_flag = 2;
			  
			  break;
		  }
		  
		  check2:
		  
		  read_pin_argument(GPIO_D , PIN_3 , &ss_switch);
		  
		  if (ss_switch == 0)
		  {
			  
			  io_write_pin(GPIO_D , PIN_7 , LOW);
			  io_write_pin(GPIO_D , PIN_0 , LOW);
			  io_write_pin(GPIO_D , PIN_1 , LOW);
			  
			  LCD_WRITE_STRING("   Time =");
			  
			  LCD_WRITE_STRING("                ");
			  LCD_WRITE_COMMAND(0xC0);
			  LCD_WRITE_STRING("                ");
			  
			  
			  LCD_WRITE_STRING("   Time =");
			  
			  LCD_GoTo(1 , 10);
			  LCD_WRITE_NUMBER(0);
			  LCD_WRITE_CHAR(':');
			  LCD_GoTo(1  , 12);
			  
			  if (counter<10)
			  {
				  LCD_WRITE_NUMBER(0);
				  LCD_WRITE_NUMBER(seconds_int);
			  }
			  else
			  {
				  LCD_WRITE_NUMBER(seconds_int);
			  }
			  
			  goto check2;//to handle switch bugs
			  
			  
		  }
		  else if (ss_switch == 1)
		  {
			  
			  io_write_pin(GPIO_D , PIN_7 , HIGH);
			  io_write_pin(GPIO_D , PIN_0 , HIGH);
			  io_write_pin(GPIO_D , PIN_1 , HIGH);
			  
		  }
		  
		  LCD_WRITE_STRING("   Time =");
		  
		  LCD_GoTo(1 , 10);
		  LCD_WRITE_NUMBER(0);
		  LCD_WRITE_CHAR(':');
		  LCD_GoTo(1  , 12);
		  
		  if (counter<10)
		  {
			  LCD_WRITE_NUMBER(0);
			  LCD_WRITE_NUMBER(counter);
		  }
		  else
		  {
			  LCD_WRITE_NUMBER(counter);
		  }
		  
		  _delay_ms(8000);
		  
		  
		  LCD_CLEAR();
		  _delay_ms(100);
		  
	  }
		
}
	
	
	






void STOP(void)
{

   LED_ON(GPIO_B , PIN_3);
   _delay_ms(2000);
	
}







/*

#define SIZE 10
#define SIZE2 5


int array_to_num(int arr[],int n)
{
	char str[6][3];
	int i;
	
char number[13] = {'\n'};

for(i=0;i<n;i++)
{
	sprintf(str[i],"%d",arr[i]);
}

for(i=0 ; i<n ; i++)
{
	strcat(number , str[i]);
}

i = atoi(number);

return i;

} 

int size1 = 0;
int size2 = 0;


uchar8  key;
uchar8  key2;
uchar8  key3;

uchar8  op1 = '+';
uchar8  op2 = '-';
uchar8  op3 = 'x';
uchar8  op4 = '/';
*/






 //button = 0;
	 
	 /*
	  LCD_WRITE_STRING("first operand: ");
	  LCD_WRITE_COMMAND(0xC0);
	  
	 
	  for (i=0 ; i<16 ; i++)
	  {
		  
		   first_operand[i] = GET_PRESSED();
		   
		   if (first_operand[i] == '=')
		   {
		      goto oper;
		   }
		   
		   size1++;
		   
		   LCD_WRITE_DATA(first_operand[i]);
		    
	  }
	  
	   _delay_ms(5000);
	  
	  oper:
	 
	  LCD_CLEAR();
	  _delay_ms(400);
	  
	  LCD_WRITE_STRING("operator: ");
	  LCD_WRITE_COMMAND(0xC0);
	  key2 = GET_PRESSED();
	  LCD_WRITE_DATA(key2);
	  _delay_ms(7000);
	  
	  LCD_CLEAR();
	  _delay_ms(400);
	  
	  LCD_WRITE_STRING("second operand: ");
	  LCD_WRITE_COMMAND(0xC0);
	 
	  for (i=0 ; i<16 ; i++)
	  {
		  
		  second_operand[i] = GET_PRESSED();
		  
		  if (second_operand[i] == '=')
		  {
			  goto calc;
		  }
		  
		  size2++;
		  
		  LCD_WRITE_DATA(second_operand[i]);
		  
	  }  
	  
	  _delay_ms(9000);
	 
	 calc:
	 
	
	//if (GET_PRESSED() == '=')
	//{
		
		 LCD_CLEAR();
		 _delay_ms(300);
	
	 
	 for (i=0 ; i<size1 ; i++)
	 {
		 arr_number_one[i] = charToint(first_operand[i]);
	 }
	 
	 for (i=0 ; i<size2 ; i++)
	 {
		 arr_number_two[i] = charToint(second_operand[i]);
	 }
	 
	 number_one = array_to_num(arr_number_one , 3);
	 number_two = array_to_num(arr_number_two , 3);
	  
	 
	    LCD_CLEAR();
	    _delay_ms(400);
		
		// number_one = charToint(key);
		// number_two = charToint(key3);
	   
	   if((strcmp(key2 , op1)) == 0)
	   {
		   res = number_one + number_two;
	   }	    
	   else if ((strcmp(key2 , op2)) == 0)
	   {
		   res = number_one - number_two;
	   }
	   else if ((strcmp(key2 , op3)) == 0)
	   {
		   res = number_one * number_two;	   		   
	   }
	   else if ((strcmp(key2 , op4)) == 0)
	   {
	       res = number_one / number_two;
	   }
	   else
	   {
	      LCD_WRITE_STRING("karim");
	   }
	   
	  //}	      
	  /*
	  LCD_WRITE_STRING(first_operand);
	  LCD_WRITE_DATA(key2);
	  LCD_WRITE_STRING(second_operand);
	  LCD_WRITE_CHAR('=');   
		   
	  _delay_ms(300);
	  LCD_WRITE_NUMBER(res);
	  _delay_ms(300);
	   
	  if (GET_PRESSED() == 'c')
	  {
		  LCD_CLEAR();
		  _delay_ms(300);
	  }  
		*/   




/*
	
	LCD_WRITE_STRING("first operand: ");
	LCD_WRITE_COMMAND(0xC0);
	key = GET_PRESSED();
	LCD_WRITE_DATA(key);
	_delay_ms(7000);
	
	LCD_CLEAR();
	_delay_ms(400);
	
	LCD_WRITE_STRING("operator: ");
	LCD_WRITE_COMMAND(0xC0);
	key2 = GET_PRESSED();
	LCD_WRITE_DATA(key2);
	_delay_ms(7000);
	
	LCD_CLEAR();
	_delay_ms(400);
	
	LCD_WRITE_STRING("second operand: ");
	LCD_WRITE_COMMAND(0xC0);
	key3 = GET_PRESSED();
	LCD_WRITE_DATA(key3);
	_delay_ms(7000);
	
	
	
	if (GET_PRESSED() == '=')
	{
		
		LCD_CLEAR();
		_delay_ms(400);
		
		number_one = charToint(key);
		number_two = charToint(key3);
		
		if((strcmp(key2 , op1)) == 0)
		{
			res = number_one + number_two;
		}
		else if ((strcmp(key2 , op2)) == 0)
		{
			res = number_one - number_two;
		}
		else if ((strcmp(key2 , op3)) == 0)
		{
			res = number_one * number_two;
		}
		else if ((strcmp(key2 , op4)) == 0)
		{
			res = number_one / number_two;
		}
		else
		{
			LCD_WRITE_STRING("karim");
		}
		
		LCD_WRITE_DATA(key);
		LCD_WRITE_DATA(key2);
		LCD_WRITE_DATA(key3);
		LCD_WRITE_CHAR('=');
		
		_delay_ms(300);
		LCD_WRITE_NUMBER(res);
		_delay_ms(300);
		
		if (GET_PRESSED() == 'c')
		{
			LCD_CLEAR();
			_delay_ms(300);
		}
		
	}
	
*/









     












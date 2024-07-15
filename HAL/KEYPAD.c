/*
 * KEYPAD.c
 *
 * Created: 1/24/2021 1:19:10 AM
 *  Author: karim hassan
 */ 

#include "KEYPAD.h"
#include "Gpio.h"
#include "util/delay.h"
#include <string.h>

#define SIZE 2
#define SIZE2 2



int result[2];

int first[2];
int second[2];

uchar8 first_operand[2];
uchar8 second_operand[2];


/*******calculator array*******/
/*
uchar8 keypad_array[4][4] =
{
	{'7' , '8' , '9' , '^'},
	
	{'4' , '5' , '6' , 'x'},
		
	{'1' , '2' , '3' , '-'},
		
	{'c' , '0' , '=' , '+'}	
};
*/


/******phone array******/
uchar8 keypad_array[4][4] =
{
  {'1' , '2' , '3'},
	
  {'4' , '5' , '6'},
	
  {'7' , '8' , '9'},
	
  {'*' , '0' , '#'}
};





void KEYPAD_INIT()
{
	
  if(KEYPAD_TYPE == KEYPAD3X3)
  {
	
	initialize_pin(keypadrow0_port , keypadrow0_pin , INPUT);
	initialize_pin(keypadrow1_port , keypadrow1_pin , INPUT);
	initialize_pin(keypadrow2_port , keypadrow2_pin , INPUT);
	
	initialize_pin(keypadcolumn0_port , keypadcolumn0_pin , OUTPUT);
	initialize_pin(keypadcolumn1_port , keypadcolumn1_pin , OUTPUT);
	initialize_pin(keypadcolumn2_port , keypadcolumn2_pin , OUTPUT);
	
	gpio_set_pullup(keypadrow0_port , keypadrow0_pin);
	gpio_set_pullup(keypadrow1_port , keypadrow1_pin);
	gpio_set_pullup(keypadrow2_port , keypadrow2_pin);

  }	
  else if(KEYPAD_TYPE == KEYPAD3X4)
  {
	
	initialize_pin(keypadrow0_port , keypadrow0_pin , INPUT);
	initialize_pin(keypadrow1_port , keypadrow1_pin , INPUT);
	initialize_pin(keypadrow2_port , keypadrow2_pin , INPUT);
	initialize_pin(keypadrow3_port , keypadrow3_pin , INPUT);
	
	initialize_pin(keypadcolumn0_port , keypadcolumn0_pin , OUTPUT);
	initialize_pin(keypadcolumn1_port , keypadcolumn1_pin , OUTPUT);
	initialize_pin(keypadcolumn2_port , keypadcolumn2_pin , OUTPUT);
	
	gpio_set_pullup(keypadrow0_port , keypadrow0_pin);
	gpio_set_pullup(keypadrow1_port , keypadrow1_pin);
	gpio_set_pullup(keypadrow2_port , keypadrow2_pin);
	gpio_set_pullup(keypadrow3_port , keypadrow3_pin);
	
   }
   else if(KEYPAD_TYPE == KEYPAD4X4)
   {
	
	initialize_pin(keypadrow0_port , keypadrow0_pin , INPUT);
	initialize_pin(keypadrow1_port , keypadrow1_pin , INPUT);
	initialize_pin(keypadrow2_port , keypadrow2_pin , INPUT);
	initialize_pin(keypadrow3_port , keypadrow3_pin , INPUT);
	
	initialize_pin(keypadcolumn0_port , keypadcolumn0_pin , OUTPUT);
	initialize_pin(keypadcolumn1_port , keypadcolumn1_pin , OUTPUT);
	initialize_pin(keypadcolumn2_port , keypadcolumn2_pin , OUTPUT);
	initialize_pin(keypadcolumn3_port , keypadcolumn3_pin , OUTPUT);
	
	gpio_set_pullup(keypadrow0_port , keypadrow0_pin);
	gpio_set_pullup(keypadrow1_port , keypadrow1_pin);
	gpio_set_pullup(keypadrow2_port , keypadrow2_pin);
	gpio_set_pullup(keypadrow3_port , keypadrow3_pin);
	
   }
   else
   {
   
   }	
	
		
}





static void SET_COLUMN()
{
	
	if (KEYPAD_TYPE == KEYPAD4X4)
	{
		io_write_pin(keypadcolumn0_port , keypadcolumn0_pin , HIGH);
		io_write_pin(keypadcolumn1_port , keypadcolumn1_pin , HIGH);
		io_write_pin(keypadcolumn2_port , keypadcolumn2_pin , HIGH);
		io_write_pin(keypadcolumn3_port , keypadcolumn3_pin , HIGH);
	}
	else if (KEYPAD_TYPE == KEYPAD3X4)
	{
		io_write_pin(keypadcolumn0_port , keypadcolumn0_pin , HIGH);
		io_write_pin(keypadcolumn1_port , keypadcolumn1_pin , HIGH);
		io_write_pin(keypadcolumn2_port , keypadcolumn2_pin , HIGH);
	}
	else
	{
		io_write_pin(keypadcolumn0_port , keypadcolumn0_pin , HIGH);
		io_write_pin(keypadcolumn1_port , keypadcolumn1_pin , HIGH);
		io_write_pin(keypadcolumn2_port , keypadcolumn2_pin , HIGH);
	}
	
	
}





static void CLEAR_COLUMN(uchar8 col_num)
{
	
	if (KEYPAD_TYPE == KEYPAD4X4)
	{
		
		switch(col_num)
		{
			
			case 0:
			     io_write_pin(keypadcolumn0_port , keypadcolumn0_pin , LOW);
				 break;
				 
			case 1:
			     io_write_pin(keypadcolumn1_port , keypadcolumn1_pin , LOW);
				 break;
				 
			case 2:
			     io_write_pin(keypadcolumn2_port , keypadcolumn2_pin , LOW);
				 break;
				 
			case 3:
			     io_write_pin(keypadcolumn3_port , keypadcolumn3_pin , LOW);
			     break;
			
		}
		
	}
	else if (KEYPAD_TYPE == KEYPAD3X4)
	{
		
		switch(col_num)
		{
			
			case 0:
			io_write_pin(keypadcolumn0_port , keypadcolumn0_pin , LOW);
			break;
			
			case 1:
			io_write_pin(keypadcolumn1_port , keypadcolumn1_pin , LOW);
			break;
			
			case 2:
			io_write_pin(keypadcolumn2_port , keypadcolumn2_pin , LOW);
			break;
			
		}
		
	}
	else if (KEYPAD_TYPE == KEYPAD3X3)
	{
		
		switch(col_num)
		{
			
			case 0:
			io_write_pin(keypadcolumn0_port , keypadcolumn0_pin , LOW);
			break;
			
			case 1:
			io_write_pin(keypadcolumn1_port , keypadcolumn1_pin , LOW);
			break;
			
			case 2:
			io_write_pin(keypadcolumn2_port , keypadcolumn2_pin , LOW);
			break;
			
		}
		
	}
	else
	{
		
	}
	
}





static uchar8 GET_ROW_VALUE()
{
	
	uchar8 row_value = 0;
	
	if (KEYPAD_TYPE == KEYPAD4X4)
	{
		row_value  = read_pin(keypadrow0_port , keypadrow0_pin);
		row_value |= read_pin(keypadrow1_port , keypadrow1_pin)<<1;
		row_value |= read_pin(keypadrow2_port , keypadrow2_pin)<<2;
		row_value |= read_pin(keypadrow3_port , keypadrow3_pin)<<3;
	}
	else if (KEYPAD_TYPE == KEYPAD3X4)
	{
		row_value  = read_pin(keypadrow0_port , keypadrow0_pin);
		row_value |= read_pin(keypadrow1_port , keypadrow1_pin)<<1;
		row_value |= read_pin(keypadrow2_port , keypadrow2_pin)<<2;
	}
	else if (KEYPAD_TYPE == KEYPAD3X3)
	{
		row_value  = read_pin(keypadrow0_port , keypadrow0_pin);
		row_value |= read_pin(keypadrow1_port , keypadrow1_pin)<<1;
		row_value |= read_pin(keypadrow2_port , keypadrow2_pin)<<2;
	}
	else
	{
		
	}
	
	return row_value;
	
}





static uchar8 KEYPAD_GET_CHAR()
{
	
	uchar8 row = 0;
	uchar8 column = 0;
	uchar8 key = 0;
	
	for(column = 0 ; column < COL_NUM ; column++)
	{
		
		SET_COLUMN();           //1111
		CLEAR_COLUMN(column);   //0(1110)  1(1101)  2(1011)  3(0111)
		
		_delay_ms(10);  
		 
        row = GET_ROW_VALUE();
		
		if (row != NOT_PRESSED)
		{
			while(GET_ROW_VALUE() != (NOT_PRESSED));
			break;
		}
        		
	}
	
	
	if (column == COL_NUM)
	{
		key = 0;
	}
	else
	{
		
		switch(row)
		{
			
			case 0b00001110:
			     row = 0;
				 break;
				 
			case 0b00001101:
			     row = 1;
				 break;
				 
			case 0b00001011:
			     row = 2;
				 break;
				 
			case 0b00000111:
			     row = 3;
				 break;
		}
	    
		key = keypad_array[row][column];	
	}
	
	return key;
}



uchar8 GET_PRESSED()
{
	
	uchar8 key = 0;
	
	do 
	{
		
		key = KEYPAD_GET_CHAR();
		
	} while (key == 0);
	
	return key;
	
}



int charToint(char a)
{
	char *p = &a;
	
	int k = atoi(p);
	
	return k;
}




int string_compare(char str1[], char str2[])
{
	
	int ctr = 0;
	int flag = 0;

   for (ctr=0 ; ctr<6 ; ctr++)
   {
	   
	   if(str1[ctr] == str2[ctr])
	   {
		   
		   if(str1[ctr]=='\0' || str2[ctr]=='\0')
		   break;
		   
		   flag = 0; 
		   
		   if (str2[ctr] == '#' && (str2[0] != '1' || str2[1] != '9' || str2[2] != '0' || str2[3] != '7' || str2[4] != '*') )
		   {
			   flag = 1;//wrong password
		   }
		   
	   }
	   else
	   {
		   flag = 1;
	   }
	   
   }
   
   if (flag == 0)
   {
	   return 0;
   }
   else
   {
       return 1;
   }
	

}






/*
void get_result(uchar8 first_operand[SIZE2] , uchar8 second_operand[SIZE2])
{
	
	int i;
	int z;
	int number;
	
	//uchar8 res[SIZE];
	
	
	while (first_operand[i] < SIZE2)
	{
		
		first_operand[i] = GET_PRESSED();
		
		switch(first_operand[i])
		{
			
		  case '+':
		         for (z=0 ; first_operand[z] != '+' ; z++)
		         {
					 number = charToint(first_operand[z]);
					 first[z] = number;
		         }
			     for (z=0 ; second_operand[z] != '=' ; z++)
			     {
					 number = charToint(second_operand[z]);
					 second[z] = number;
			     }
			    	
				 result[z] = first[z] + second[z];
				 for (z=0 ; z<SIZE ; z++)
				 {
					 LCD_WRITE_NUMBER(result[z]);
				 }
			     break;
				
				
				
		  case '-':
		       for (z=0 ; first_operand[z]!='-' ; z++)
		       {
			       number = charToint(first_operand[z]);
			       first[z] = number;
		       }
		       for (z=0 ; second_operand[z]!='=' ; z++)
		       {
			       number = charToint(second_operand[z]);
			       second[z] = number;
		       }
			
			   result[z] = first[z] - second[z];
			   for (z=0 ; z<SIZE ; z++)
			   {
				   LCD_WRITE_NUMBER(result[z]);
			   }
			   break;
		
		
		  case '/':
		       for (z=0 ; first_operand[z]!='/' ; z++)
		       {
			       number = charToint(first_operand[z]);
			       first[z] = number;
		       }
		       for (z=0 ; second_operand[z]!='=' ; z++)
		       {
			       number = charToint(second_operand[z]);
			       second[z] = number;
		       }
		       	   
		       result[z] = first[z] / second[z];
			   for (z=0 ; z<SIZE ; z++)
			   {
				   LCD_WRITE_NUMBER(result[z]);
			   }
			   break;
		
		
		
		  case 'x':
			    for (z=0 ; z<SIZE2 ; z++)
			    {
				    number = charToint(first_operand[z]);
				    first[z] = number;
			    }
			    for (z=0 ; z<SIZE2 ; z++)
			    {
				    number = charToint(second_operand[z]);
				    second[z] = number;
			    } 
				result[z] = first[z] * second[z];
				
				for (z=0 ; z<SIZE ; z++)
				{
					LCD_WRITE_NUMBER(result[z]);
				}
				
			    break;	
		}		
	
		 
		 
		
		i++;	
		
	}
	
	
}


/*
void convert_chars_to_integers()
{
	
	int i;
	int number;
	
	for (i=0 ; i<15 ; i++)
	{
		sscanf(first_operand[i] , "%d" , &number);
		first[i] = number;
	}
	
	for (i=0 ; i<15 ; i++)
	{
		sscanf(second_operand[i] , "%d" , &number);
		second[i] = number;
	}
	
}
*/


/*
 int Arithmetic_operation(uchar8 key)
 {
	 
	int i;
	 
	convert_chars_to_integers(first_operand[15] , second_operand[15]);
	key = GET_PRESSED();
	 
	for (i=0 ; i<15 ; i++)
	{
		 
		 switch(key)
		 {
			 
			 case '+':
			 result[i] = first[i] + second[i];
			 break;
			 
			 case '-':
			 result[i] = first[i] - second[i];
			 break;
			 
			 case '/':
			 result[i] = first[i] / second[i];
			 break;
			 
			 case 'x':
			 result[i] = first[i] * second[i];
			 break;
			 
			 case '%':
			 result[i] = first[i] % second[i];
			 break;
			 
		 }
		 
	}
	
	for (i=0 ; i<15 ; i++)
	{
		return result[i];
	}

	 
 }
*/


/*
 void display_result_on_LCD(uchar8 key)
 {
	 
	char *res;
	int i;
    
	for (i=0 ; i<30 ; i++)
	{
		
		 i = Arithmetic_operation(key);
		 
		 sprintf(res , "%d" , i);
		 
		 LCD_WRITE_COMMAND(0xC0);//force cursor to begin from second line
		 _delay_ms(100);
		 
		 LCD_WRITE_CHAR(res);
		 
	}
		 
	
	 
 }
 */



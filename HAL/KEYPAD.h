/*
 * KEYPAD.h
 *
 * Created: 1/24/2021 1:18:50 AM
 *  Author: karim hassan
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Gpio.h"
#include "standard types.h"
#include "util/delay.h"

#define SIZE 2
#define SIZE2 2


/**********configration menu***********/
#define KEYPAD_TYPE KEYPAD4X4

#define COL_NUM     4

#define NOT_PRESSED 0x0f

/*********rows********/
#define keypadrow0_port GPIO_C
#define keypadrow0_pin  PIN_0

#define keypadrow1_port GPIO_C
#define keypadrow1_pin  PIN_1

#define keypadrow2_port GPIO_C
#define keypadrow2_pin  PIN_2

#define keypadrow3_port GPIO_C
#define keypadrow3_pin  PIN_3


/*********columns**********/
#define keypadcolumn0_port GPIO_C
#define keypadcolumn0_pin  PIN_4

#define keypadcolumn1_port GPIO_C
#define keypadcolumn1_pin  PIN_5

#define keypadcolumn2_port GPIO_C
#define keypadcolumn2_pin  PIN_6

#define keypadcolumn3_port GPIO_C
#define keypadcolumn3_pin  PIN_7


#define KEYPAD4X4 0
#define KEYPAD3X3 1
#define KEYPAD3X4 2


/*****PROTOTYPES*****/

void KEYPAD_INIT();

static void SET_COLUMN();

static void CLEAR_COLUMN(uchar8 col_num);

static uchar8 GET_ROW_VALUE();

static uchar8 KEYPAD_GET_CHAR();

uchar8 GET_PRESSED();

int charToint(char a);


/*******calculator*******/
/*
void convert_chars_to_integers();

int Arithmetic_operation(uchar8 key);

void display_result_on_LCD(uchar8 key);
*/
void get_result(uchar8 first_operand[SIZE2] , uchar8 second_operand[SIZE2]);


/*****global variables*****/

extern int result[SIZE];

extern int first[SIZE2];
extern int second[SIZE2];

extern uchar8 first_operand[SIZE2];
extern uchar8 second_operand[SIZE2];

extern uchar8 keypad_array[4][4];


#endif /* KEYPAD_H_ */

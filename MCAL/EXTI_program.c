#include <stdlib.h>
#include "utils.h"
#include "standard types.h"

#include "Gpio.h"

#include "EXTI_interface.h"
#include "EXTI_registers.h"
#include "EXTI_config.h"


int flag = 0;


/*Global pointers*/
void (*Global_ptr_to_INT0func)(void) = NULL;
void (*Global_ptr_to_INT1func)(void) = NULL;
void (*Global_ptr_to_INT2func)(void) = NULL;




void MEXTI_voidINT0init(void)
{
	
	initialize_pin(GPIO_D , PIN_2 , INPUT);
	io_write_pin(GPIO_D , PIN_2 , HIGH);//input pull up

	/*interrupt sense control for INT0*/
	switch(INT0_SENSE)
	{
	case raising_Edge:
		SET_BIT(MCUCR , ISC01);
		SET_BIT(MCUCR , ISC00);
		break;

	case falling_Edge:
		SET_BIT(MCUCR , ISC01);
		CLEAR_BIT(MCUCR , ISC00);
		break;

	case low_level:
		CLEAR_BIT(MCUCR , ISC01);
		CLEAR_BIT(MCUCR , ISC00);
		break;

	case any_change:
		CLEAR_BIT(MCUCR , ISC01);
	    SET_BIT(MCUCR , ISC00);
	    break;

	}

	/*peripheral interrupt enable for INT0*/
	SET_BIT(GICR , GICR_INT0);


}





void MEXTI_voidINT1init(void)
{
	
	
	initialize_pin(GPIO_D , PIN_3 , INPUT);
	io_write_pin(GPIO_D , PIN_3 , HIGH);//input pull up

	/*interrupt sense control for INT1*/
		switch(INT1_SENSE)
		{
		case raising_Edge:
			SET_BIT(MCUCR , ISC11);
			SET_BIT(MCUCR , ISC10);
			break;

		case falling_Edge:
			SET_BIT(MCUCR , ISC11);
			CLEAR_BIT(MCUCR , ISC10);
			break;

		case low_level:
			CLEAR_BIT(MCUCR , ISC11);
			CLEAR_BIT(MCUCR , ISC10);
			break;

		case any_change:
			CLEAR_BIT(MCUCR , ISC11);
		    SET_BIT(MCUCR , ISC10);
		    break;

		}

		/*peripheral interrupt enable for INT1*/
		SET_BIT(GICR , GICR_INT1);



}






void MEXTI_voidINT2init(void)
{

    initialize_pin(GPIO_B , PIN_2 , INPUT);
    io_write_pin(GPIO_B , PIN_2 , HIGH);
	
	switch(INT2_SENSE)
	{
		case raising_Edge:
		SET_BIT(MCUCR , ISC2);
		break;

		case falling_Edge:
		CLEAR_BIT(MCUCR , ISC2);
		break;
	}

	/*peripheral interrupt enable for INT2*/
	SET_BIT(GICR , GICR_INT2);

}





void MGIE_voidEnable(void)
{

  SET_BIT(SREG , SREG_I);

}






void MGIE_voidDisable(void)
{

  CLEAR_BIT(SREG , SREG_I);

}





void INI0_set_call_back(void (*Local_ptr_to_INT0func)(void))
{
	Global_ptr_to_INT0func = Local_ptr_to_INT0func;
}




void INT1_set_call_back(void (*Local_ptr_to_INT1func)(void))
{
	
	Global_ptr_to_INT1func = Local_ptr_to_INT1func;
}





void INT2_set_call_back(void (*Local_ptr_to_INT2func)(void))
{
	Global_ptr_to_INT2func = Local_ptr_to_INT2func;
}




 void __vector_1(void) __attribute__((signal));
 void __vector_1(void)
 {
	 Global_ptr_to_INT0func();
 }





void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	Global_ptr_to_INT1func();
}





void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	Global_ptr_to_INT2func();
}




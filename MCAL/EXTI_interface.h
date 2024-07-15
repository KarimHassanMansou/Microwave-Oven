#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


#define any_change    3
#define low_level     2
#define raising_Edge  1
#define falling_Edge  0


/*initialization*/
void MEXTI_voidINT0init(void);
void MEXTI_voidINT1init(void);
void MEXTI_voidINT2init(void);

/*call back functions*/
void INI0_set_call_back(void (*Local_ptr_to_INT0func)(void));
void INI1_set_call_back(void (*Local_ptr_to_INT1func)(void));
void INI2_set_call_back(void (*Local_ptr_to_INT2func)(void));


/*global interrupt*/
void MGIE_voidEnable(void);
void MGIE_voidDisable(void);


#endif

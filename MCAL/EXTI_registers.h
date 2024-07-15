#ifndef EXTI_REGISTERS_H_
#define EXTI_REGISTERS_H_


#define SREG        *((volatile uchar8*) 0x5F)
#define SREG_I      7


#define GICR        *((volatile uchar8*) 0x5B)
#define GICR_INT0   6
#define GICR_INT1   7
#define GICR_INT2   5


#define MCUCR        *((volatile uchar8*) 0x55)
#define ISC11        3
#define ISC10        2
#define ISC01        1
#define ISC00        0


#define MCUCSR       *((volatile uchar8*) 0x54)
#define ISC2         6


/*read only in interrupt state*/
#define GIFR        *((volatile uchar8*) 0x5A)


#endif

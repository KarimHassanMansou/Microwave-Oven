/*
 * utils.h
 *
 * Created: 1/15/2021 2:59:41 AM
 *  Author: karim hassan
 */ 


#ifndef UTILS_H_
#define UTILS_H_

/*        MACROS FOR PIN         */
#define PIN_WRITE(reg,pin,data)			(reg)=(reg&(~(1<<pin)))|(data<<pin)
#define GET_PIN(reg,pin)         		((reg>>pin) & 0x01)
#define TOG_PIN(reg,pin)				reg ^= (1<<(pin))
#define SET_BIT(Reg,bit)				Reg |= (1<<bit)
#define CLEAR_BIT(Reg,bit)				Reg = (Reg&(~(1<<bit)))



/*         MACROS TO PORT        */
#define InitPort(CONTROL, DIRECTION)		((CONTROL) = (DIRECTION)?(~GPIO_LOW):(GPIO_LOW))
#define WRITE_PORT(PORT, DATA)				((PORT) = (DATA))
#define PORT_MASK(reg,val)                (reg)|=(val)
#define PORT_CLEAR_MASK(reg,val)          (reg)&=~(val)

#define ReadPort(PORT)					 (PORT)
#define SET_REG(Reg)					Reg=0xFF
#define CLEAR_REG(Reg)					Reg=0x00
#define TOOGLE_REG(Reg)					Reg^=0xFF


/*        LOWER NIBBLE 0-3        */
#define GET_LOWER(reg)                         (reg)&0x0f
#define LOWER_NIBBLE_HIGH(reg)                 reg=((reg&0xf0)|0x0f)
#define LOWER_NIBBLE_VALUE(reg,data)         reg=(reg&0xF0)|data&0X0F



/*        HIGHER NIBBLE 4-8        */
#define GET_HIGHER(reg)                                 (reg)&(0xF0)
#define HIGHER_NIBBLE_HIGH(reg)                         (reg)=((reg&0x0f)|(0xf0))
#define HIGHER_NIBBLE_VALUE(reg,data)                   (reg)=(reg&0x0f)|(data&0XF0)


#endif /* UTILS_H_ */
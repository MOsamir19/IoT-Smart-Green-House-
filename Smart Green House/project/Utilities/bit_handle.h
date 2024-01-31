/*
 * bit_handle.h
 *
 * Created: 8/10/2020 
 *  Author: Smart Greenhouse
 */ 

#ifndef BIT_HANDLE_H_
#define BIT_HANDLE_H_

/* set , clear , toggle a single bit*/

#define  SETBIT(REG,PIN_NO)    REG |= (1<<(PIN_NO))
#define  CLEARBIT(REG,PIN_NO)    REG &= ~(1<<(PIN_NO))
#define  TOGGLEBIT(REG,PIN_NO)    REG ^= (1<<(PIN_NO))

/* set , clear , toggle a group of bits*/

#define  SETBITS(REG,PINS_NO)    REG |= (PINS_NO)
#define  CLEARBITS(REG,PINS_NO)    REG &= ~(PINS_NO)
#define  TOGGLEBITS(REG,PINS_NO)    REG ^= (PINS_NO)

/* set , clear , toggle ALL bits*/

#define  SET_ALL_BITS(REG)      REG = (0xFF)
#define  CLEAR_ALL_BITS(REG)    REG = (0x00)
#define  TOGGLE_ALL_BITS(REG)   REG^= (0xFF)

/* reading a bit */

#define  readbit(REG,PIN_NO)     ((REG>>(PIN_NO)) & 0x01)

#endif /* BIT_HANDLE_H_ */
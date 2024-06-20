/*
 * Bit_math.h
 *
 *  Created on: May 8, 2024
 *      Author: Abdo Halem
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(reg, bit_pos)   	(reg |= (0x01 << bit_pos))
#define CLEAR_BIT(reg, bit_pos) 	(reg &= ~(0x01 << bit_pos))
#define TOGGLE_BIT(reg, bit_pos) 	(reg ^= (0x01 << bit_pos))
#define READ_BIT(reg, bit_pos) 		((reg >> bit_pos) & 0x01)

#endif /* BIT_MATH_H_ */

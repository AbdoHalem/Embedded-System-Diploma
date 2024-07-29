/*
 * GPIO.h
 *
 *  Created on: Jul 23, 2024
 *      Author: Abdo Halem
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "stm32f103x6.h"

//------------------------------------
// Config Structure
typedef struct{
	uint16_t GPIO_PinNumber;	// Specifies the GPIO pins to be configured.
								// This parameter must be set based on @ref GPIO_PINS_define
	uint8_t GPIO_MODE;			// Specifies the operating mode for the selected pin.
								// This parameter must be set based on @ref GPIO_MODE_define
	uint8_t GPIO_OUTPUT_SPEED;	// Specifies the speed for the selected pin.
								// This parameter must be set based on @ref GPIO_SPEED_define
}GPIO_PinConfig_t;

//--------------------------------------
// Macros Configuration References
//--------------------------------------
/* @ref GPIO_PINS_define */
// It actually gives the Bit position
#define GPIO_PIN_0			((uint16_t)0x0001)		/* Pin 0 is selected */
#define GPIO_PIN_1			((uint16_t)0x0002)		/* Pin 1 is selected */
#define GPIO_PIN_2			((uint16_t)0x0004)		/* Pin 2 is selected */
#define GPIO_PIN_3			((uint16_t)0x0008)		/* Pin 3 is selected */
#define GPIO_PIN_4			((uint16_t)0x0010)		/* Pin 4 is selected */
#define GPIO_PIN_5			((uint16_t)0x0020)		/* Pin 5 is selected */
#define GPIO_PIN_6			((uint16_t)0x0040)		/* Pin 6 is selected */
#define GPIO_PIN_7			((uint16_t)0x0080)		/* Pin 7 is selected */
#define GPIO_PIN_8			((uint16_t)0x0100)		/* Pin 8 is selected */
#define GPIO_PIN_9			((uint16_t)0x0200)		/* Pin 9 is selected */
#define GPIO_PIN_10			((uint16_t)0x0400)		/* Pin 10 is selected */
#define GPIO_PIN_11			((uint16_t)0x0800)		/* Pin 11 is selected */
#define GPIO_PIN_12			((uint16_t)0x1000)		/* Pin 12 is selected */
#define GPIO_PIN_13			((uint16_t)0x2000)		/* Pin 13 is selected */
#define GPIO_PIN_14			((uint16_t)0x4000)		/* Pin 14 is selected */
#define GPIO_PIN_15			((uint16_t)0x8000)		/* Pin 15 is selected */
#define GPIO_PIN_ALL		((uint16_t)0xFFFF)		/* All pins are selected */

#define GPIO_PIN_MASK		0x0000FFFFu	/* PIN mask for assert test */

/* @ref GPIO_MODE_define */
//In input mode (MODE[1:0]=00):
//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up / pull-down
//3: Reserved
//In output mode (MODE[1:0] > 00):
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function Input
#define GPIO_MODE_ANALOG				0x00000000u
#define GPIO_MODE_INPUT_FLOATING		0x00000001u
#define GPIO_MODE_INPUT_PULL_UP			0x00000002u
#define GPIO_MODE_INPUT_PULL_DOWN		0x00000003u
#define GPIO_MODE_OUTPUT_PUSH_PULL		0x00000004u
#define GPIO_MODE_OUTPUT_OPEN_DRAIN		0x00000005u
#define GPIO_MODE_AF_OUTPUT_PUSH_PULL	0x00000006u
#define GPIO_MODE_AF_OUTPUT_OPEN_DRAIN	0x00000007u
#define GPIO_MODE_AF_INPUT				0x00000008u

/* @ref GPIO_SPEED_define */
//01: Output mode, max speed 10 MHz.
//10: Output mode, max speed 2 MHz.
//11: Output mode, max speed 50 MHz.
#define GPIO_SPEED_10M		0x00000001u
#define GPIO_SPEED_2M		0x00000002u
#define GPIO_SPEED_50M		0x00000003u

/* @ref GPIO_PIN_STATE */
#define GPIO_PIN_HIGH		1
#define GPIO_PIN_LOW		0

/* @ref GPIO_RETURN_LOCK */
#define GPIO_RETURN_LOCK_OK			1
#define GPIO_RETURN_LOCK_ERROR		0

/*
 * =====================================================
 * 			APIs Supported by "MCAL GPIO Driver"
 * =====================================================
 */
void MCAL_GPIO_Init(GPIO_t *GPIOx, GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_t *GPIOx);
uint8_t MCAL_GPIO_ReadPin(GPIO_t *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_t *GPIOx);
void MCAL_GPIO_WritePin(GPIO_t *GPIOx, uint16_t PinNumber, uint8_t value);
void MCAL_GPIO_WritePort(GPIO_t *GPIOx, uint16_t value);
void MCAL_GPIO_TogglePin(GPIO_t *GPIOx, uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin(GPIO_t *GPIOx, uint16_t PinNumber);


#endif /* GPIO_GPIO_H_ */

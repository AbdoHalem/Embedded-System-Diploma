/*
 * GPIO.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Abdo Halem
 */
#include "GPIO.h"

static uint8_t Get_CRLH_Position(uint16_t PinNumber);


/**================================================================
* @Fn	 		- MCAL_GPIO_Init
* @brief 		- Initializes the GPIOx PINy according to the specified parameters in the PinConfig
* @param [in] 	- GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [out] 	- PinConfig: Pointer to a GPIO_PinConfig_t configuration structure
* @retval 		- None
* Note			- stm32f103c6 MCU has GPIO A, B, C, D, E Modules
* 				  but LQFP48 package has only GPIO A,B and part of C,D exported as external PINS from the MCU
*/
void MCAL_GPIO_Init(GPIO_t *GPIOx, GPIO_PinConfig_t *PinConfig){
	// GPIO_CRL configure pins from 0 to 7
	// GPIO_CRH configure pins from 8 to 8
	volatile uint32_t *config_register = NULL;
	uint8_t configs = 0;
	config_register = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &(GPIOx->CRL) : &(GPIOx->CRH);
	// Clear MODEy[1:0] and CNFy[1:0] bits
	(*config_register) &= ~(Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	// If the pin is output
	if((PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PUSH_PULL) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OPEN_DRAIN)
	   || (PinConfig->GPIO_MODE == GPIO_MODE_AF_OUTPUT_PUSH_PULL) || (PinConfig->GPIO_MODE == GPIO_MODE_AF_OUTPUT_OPEN_DRAIN)){
		// Set CNFy[1:0] and MODE[1:0]
		configs = ( (((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_OUTPUT_SPEED)) & 0x0F );
	}
	else{	// If the pin is input
		if((PinConfig->GPIO_MODE == GPIO_MODE_ANALOG) || (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLOATING)){
			// Set CNFy[1:0] and MODE[1:0]
			configs = ( (((PinConfig->GPIO_MODE) << 2) | 0x0) & 0x0F );
		}
		else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT){	// Deal with it as input floating
			// Set CNFy[1:0] and MODE[1:0]
			configs = ( ((GPIO_MODE_INPUT_FLOATING << 2) | 0x0) & 0x0F );
		}
		else{	// PULL UP or PULL DOWN
			configs = ( ((GPIO_MODE_INPUT_PULL_UP << 2) | 0x0) & 0x0F);
			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PULL_UP){
				// Table 20. Port bit configuration table PxODR 1
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else{
				// Table 20. Port bit configuration table PxODR 0
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}
	// Write on CRL or CRH register
	(*config_register) |= ( (configs) << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );
}


/**================================================================
* @Fn	 		- MCAL_GPIO_DeInit
* @brief 		- Resets the GPIO Registers
* @param [in] 	- GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
* @retval 		- None
* Note			- None
*/
void MCAL_GPIO_DeInit(GPIO_t *GPIOx){
	// If there is no reset controller on the MCU write the reset value for each register
	if(GPIOx == GPIOA){
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~((1<<2));
	}
	else if(GPIOx == GPIOB){
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~((1<<3));
	}
	else if(GPIOx == GPIOC){
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~((1<<4));
	}
	else if(GPIOx == GPIOD){
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~((1<<5));
	}
	else if(GPIOx == GPIOE){
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~((1<<6));
	}
}

/**================================================================
* @Fn	 		- MCAL_GPIO_ReadPin
* @brief 		- Read a specific pin
* @param [in] 	- GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	- PinNumber: Pin number according to @ref GPIO_PINS_define
* @retval 		- The input pin value (two values based on @ref GPIO_PIN_STATE)
* Note			- None
*/
uint8_t MCAL_GPIO_ReadPin(GPIO_t *GPIOx, uint16_t PinNumber){
	uint8_t bit_status = 0;
	if( ((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_LOW ){
		bit_status = GPIO_PIN_HIGH;
	}
	else{
		bit_status = GPIO_PIN_LOW;
	}
	return bit_status;
}

/**================================================================
* @Fn	 		- MCAL_GPIO_ReadPort
* @brief 		- Read a specific port
* @param [in] 	- GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
* @retval 		- The input port value
* Note			- None
*/
uint16_t MCAL_GPIO_ReadPort(GPIO_t *GPIOx){
	return ((uint16_t)(GPIOx->IDR));
}

/**================================================================
* @Fn	 		- MCAL_GPIO_WritePin
* @brief 		- Write on a specific input pin
* @param [in] 	- GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	- PinNumber: Pin number according to @ref GPIO_PINS_define
* @param [in] 	- value: Pin value
* @retval 		- None
* Note			- None
*/
void MCAL_GPIO_WritePin(GPIO_t *GPIOx, uint16_t PinNumber, uint8_t value){
	if(value != GPIO_PIN_LOW){
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Set the corresponding ODRx bit
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else{
		//1: Reset the corresponding ODRx bit
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}

/**================================================================
* @Fn	 		- MCAL_GPIO_WritePort
* @brief 		- Write on a specific input port
* @param [in] 	- GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	- PinNumber: Pin number according to @ref GPIO_PINS_define
* @param [in] 	- value: Port value
* @retval 		- None
* Note			- None
*/
void MCAL_GPIO_WritePort(GPIO_t *GPIOx, uint16_t value){
	GPIOx->ODR = (uint32_t)value;
}

/**================================================================
* @Fn	 		- MCAL_GPIO_TogglePin
* @brief 		- Toggle a specific pin
* @param [in] 	- GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	- PinNumber: Pin number according to @ref GPIO_PINS_define
* @retval 		- None
* Note			- None
*/
void MCAL_GPIO_TogglePin(GPIO_t *GPIOx, uint16_t PinNumber){
	GPIOx->ODR ^= (PinNumber);
}

/**================================================================
* @Fn	 		- MCAL_GPIO_LockPin
* @brief 		- The locking mechanism allows the IO configuration to be frozen
* @param [in] 	- GPIOx: Where x can be (A..E depending on device used) to select the GPIO peripheral
* @param [in] 	- PinNumber: Pin number according to @ref GPIO_PINS_define
* @retval 		- OK if pin config is locked or ERROR if pin is not locked (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
* Note			- None
*/
uint8_t MCAL_GPIO_LockPin(GPIO_t *GPIOx, uint16_t PinNumber){
	//	Bit 16 LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	These bits are read write but can only be written when the LCKK bit is 0.
	//	0: Port configuration not locked
	//	1: Port configuration locked.
	volatile uint32_t temp = 1<<16;
	temp |= PinNumber; 			// Set LCKK[16]: Lock key
	GPIOx->LCKR = temp;			// Write 1
	GPIOx->LCKR = PinNumber;	// Write 0
	GPIOx->LCKR = temp;			// Write 1
	temp = GPIOx->LCKR;			// Read 0
	if((uint32_t)(GPIOx->LCKR & (1<<16))){	//Read 1 (this read is optional but confirms that the lock is active)
		return GPIO_RETURN_LOCK_OK;
	}
	else{
		return GPIO_RETURN_LOCK_ERROR;
	}
}



static uint8_t Get_CRLH_Position(uint16_t PinNumber){
	switch(PinNumber){
		case GPIO_PIN_0:
			return 0; break;
		case GPIO_PIN_1:
			return 4; break;
		case GPIO_PIN_2:
			return 8; break;
		case GPIO_PIN_3:
			return 12; break;
		case GPIO_PIN_4:
			return 16; break;
		case GPIO_PIN_5:
			return 20; break;
		case GPIO_PIN_6:
			return 24; break;
		case GPIO_PIN_7:
			return 28; break;
		case GPIO_PIN_8:
			return 0; break;
		case GPIO_PIN_9:
			return 4; break;
		case GPIO_PIN_10:
			return 8; break;
		case GPIO_PIN_11:
			return 12; break;
		case GPIO_PIN_12:
			return 16; break;
		case GPIO_PIN_13:
			return 20; break;
		case GPIO_PIN_14:
			return 24; break;
		case GPIO_PIN_15:
			return 28; break;
		default:
			return 0; break;
	}
}



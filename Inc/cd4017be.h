/*
 * cd4017be.h
 *
 *  Created on: 21 апр. 2019 г.
 *      Author: vasilek
 */

#ifndef CD4017BE_H_
#define CD4017BE_H_

#include "stm32f401xe.h"

/*Init CD4017BE and pins*/
void cd4017be_Init(GPIO_TypeDef *par_line,uint16_t par_pin_DS, uint16_t par_pin_STCP, uint16_t par_pin_SHCP);

/*Set outputs of CD4017BE*/
void cd4017be_WriteByte(uint8_t par_byte);

/*Reset outputs of CD4017BE without using MR-pin*/
void cd4017be_Reset(void);

#endif /* CD4017BE_H_ */

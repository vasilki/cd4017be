/*
 * cd4017be.c
 *
 *  Created on: 21 апр. 2019 г.
 *      Author: vasilek
 */


#include "cd4017be.h"
#include "dwt_stm32_delay.h"
#include "uart.h"

static GPIO_TypeDef *GL_GPIO_LINE;
static uint16_t GL_PIN_DS;
static uint16_t GL_PIN_STCP;
static uint16_t GL_PIN_SHCP;

#define K_DELAY 50
#define K_OUTS 8


void cd4017be_WriteByte(uint8_t par_byte);
void cd4017be_Reset(void);

void cd4017be_Init(GPIO_TypeDef *par_line,uint16_t par_pin_DS, uint16_t par_pin_STCP, uint16_t par_pin_SHCP)
{

	GL_GPIO_LINE = par_line;
  GL_PIN_DS = par_pin_DS;
  GL_PIN_STCP = par_pin_STCP;
  GL_PIN_SHCP = par_pin_SHCP;
  
  /*Reset handle-pins*/
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_DS,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_STCP,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_SHCP,GPIO_PIN_RESET);
	DWT_Delay_us(K_DELAY);
  
  /*Reset outputs pins (because there is not used MR-pin of cd4017be for reset*/
  cd4017be_Reset();
  
  return;
}

void cd4017be_Reset(void)
{
  /*Reset outputs pins (because there is not used MR-pin of cd4017be for reset*/
  cd4017be_WriteByte(0x0);
  DWT_Delay_us(K_DELAY);
  
  return;
}
  
void cd4017be_ResetMR(void)
{
  /*there is not used MR-pin of cd4017be for reset*/

  return;
}

void cd4017be_WriteByte(uint8_t par_byte)
{
  uint32_t loc_count;
  uint8_t loc_bit;
  
  for(loc_count = 0; loc_count < K_OUTS; loc_count++)
  {    
    loc_bit = (par_byte >> (K_OUTS - 1 - loc_count)) & 0x1;
    /*push bits in reverse order*/
    if(loc_bit != 0)
    {
      HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_DS,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_DS,GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_SHCP,GPIO_PIN_SET);
    DWT_Delay_us(K_DELAY);
    HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_SHCP,GPIO_PIN_RESET);
  }
  /*store bits*/
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_STCP,GPIO_PIN_SET);
  DWT_Delay_us(K_DELAY);
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_STCP,GPIO_PIN_RESET);
  DWT_Delay_us(K_DELAY); 
  
  return;
}


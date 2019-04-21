/*
 * cd4017be.c
 *
 *  Created on: 21 апр. 2019 г.
 *      Author: vasilek
 */


#include "cd4017be.h"
#include "dwt_stm32_delay.h"

static GPIO_TypeDef *GL_GPIO_LINE;
static uint16_t GL_PIN_CLOCK;
static uint16_t GL_PIN_EN;
static uint16_t GL_PIN_MR;

#define K_DELAY 10

void cd4017be_Init(GPIO_TypeDef *par_line,uint16_t par_pin_CLOCK, uint16_t par_pin_EN, uint16_t par_pin_MR)
{

  GL_GPIO_LINE = par_line;
  GL_PIN_CLOCK = par_pin_CLOCK;
  GL_PIN_EN = par_pin_EN;
  GL_PIN_MR = par_pin_MR;
  
  /*Reset handle-pins*/
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_CLOCK,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_EN,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_MR,GPIO_PIN_RESET);
  DWT_Delay_us(K_DELAY);
  
  cd4017be_ResetMR();
  
  return;
}

void cd4017be_ResetMR(void)
{
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_MR,GPIO_PIN_SET);
  DWT_Delay_us(K_DELAY);
  HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_MR,GPIO_PIN_RESET);
  DWT_Delay_us(K_DELAY);

  return;
}
  

void cd4017be_Strobbing(uint8_t par_B_front)
{
  static uint8_t loc_B_prev_front = 0;
  
  if(par_B_front != 0)
  {
    HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_EN,GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_CLOCK,GPIO_PIN_SET);
  }

  if(loc_B_prev_front != par_B_front)
  {
    DWT_Delay_us(K_DELAY);
  }
  else
  {
    /*nothing to do*/
  }

  if(par_B_front != 0)
  {
    HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_CLOCK,GPIO_PIN_SET);
    DWT_Delay_us(K_DELAY);
    HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_CLOCK,GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_EN,GPIO_PIN_SET);
    DWT_Delay_us(K_DELAY);
    HAL_GPIO_WritePin(GL_GPIO_LINE,GL_PIN_EN,GPIO_PIN_RESET);
  }

  DWT_Delay_us(K_DELAY);
  loc_B_prev_front = par_B_front;

  return;
}


#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "adc.h"
#include "button_handle.h"
#include "timers.h"
#include "uart.h"
#include "lcd_1602.h"
#include "cd4017be.h"
#include "dwt_stm32_delay.h"

extern UART_HandleTypeDef huart1; /*declared in main.c*/
//extern ADC_HandleTypeDef hadc1; /*declared in main.c*/

static T_LCD_GPIO_Parameters loc_LCD_GPIO_Parameters;

static void main_Init(void);
static void main_heartbeat(void);
  
void main_usercode(void)
{
  unsigned char loc_B_button_state = 0;
  uint8_t loc_buff[20];
  unsigned int loc_time;
  unsigned int loc_time_ms;
  unsigned int loc_time_sec;
  static unsigned int loc_prev_time_ms=0;
  static unsigned int loc_prev_time_sec=0;
  uint8_t loc_srbyte = 1;

  main_Init();

  tim_UpdatePeriod();
  loc_time = tim_GetPeriod();
  loc_time_sec = tim_GetTimeFromStartSEC();
  
  
  /*HeartBeat*/
  main_heartbeat();

  /*Running LED*/
  if(loc_time_sec != loc_prev_time_sec)
  {
 
    cd4017be_Strobbing(loc_srbyte);
  }
  else
  {
    /*nothing to do*/
  }

 
  loc_time_ms = tim_GetTimeFromStartMS();

// if(loc_time_sec != loc_prev_time_sec)
  if(((loc_time_ms % 1000)/100) != ((loc_prev_time_ms % 1000)/100))
  {
    sprintf(loc_buff,"%04d %04d.%01d",loc_time_sec,loc_time_ms/1000,(loc_time_ms % 1000)/100);
    //lcd_ClearLCDScreen();
    lcd_Return();
    lcd_SetCursor(1,0);
    lcd_PrintStr((char*)loc_buff);
    
    UART_PRINTFINTEGER(HAL_RCC_GetSysClockFreq()+1,"DEC")
  }
  else
  {
    /*nothing to do*/
  }

  //loc_adc_val = adc_GetValue(&hadc1);
  button_Processing();
  loc_B_button_state = button_GetButtonState('B',6);
  if(loc_B_button_state != 0)
  {
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
  }

  loc_prev_time_sec = loc_time_sec;
  loc_prev_time_ms = loc_time_ms;
  
  return;
}



void main_Init(void)
{
  static uint8_t loc_B_IsFirstTime = 0;

  if(loc_B_IsFirstTime == 0)
  {
    /*BUTTON init*/
    button_SetActiveButtons('C',13);
    button_SetActiveButtons('B',6);

    /*TIM init*/
    tim_InitTimer();

    /*DWT init*/
    DWT_Delay_Init();
    
    /*UART init*/
    uart_Init(&huart1);
    uart_PrintfBuildVersion(&huart1);

    /*LCD1602 init*/
    loc_LCD_GPIO_Parameters.D7 = GPIO_PIN_9; // PB9
    loc_LCD_GPIO_Parameters.D6 = GPIO_PIN_8; // PB8
    loc_LCD_GPIO_Parameters.D5 = GPIO_PIN_7; // PB7
    loc_LCD_GPIO_Parameters.D4 = GPIO_PIN_6; // PB6
    loc_LCD_GPIO_Parameters.EN = GPIO_PIN_5; // PB5
    loc_LCD_GPIO_Parameters.RS = GPIO_PIN_4; // PB4
    loc_LCD_GPIO_Parameters.pLine = GPIOB;
    lcd_Init(loc_LCD_GPIO_Parameters);
    lcd_ClearLCDScreen();
    lcd_SetCursor(0,0);
    lcd_PrintStr("CD4017BE");

    loc_B_IsFirstTime = 1;
    
    /*CD4017BE init*/
    cd4017be_Init(GPIOC,GPIO_PIN_10,GPIO_PIN_11,GPIO_PIN_12);
    
  }
  else
  {
    /*nothing to do*/
  }


  return;
}


void main_heartbeat(void)
{
  uint32_t loc_time_sec;
  static uint32_t loc_prev_time_sec = 0;
  
  loc_time_sec = tim_GetTimeFromStartSEC();
  
  if(loc_prev_time_sec != loc_time_sec)
  {
    if((loc_time_sec % 2) == 0)
    {
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
    }
    loc_prev_time_sec = loc_time_sec;
  }
  else
  {
    /*nothing to do*/
  }
  
  
  return;
}

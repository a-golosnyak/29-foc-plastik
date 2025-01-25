/**
  ******************************************************************************
  * @file    Led.c
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
	
#include "main.h"
#include "led_module.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/	

#define LEDn	1

GPIO_TypeDef* GPIO_PORT[LEDn] = {	GPIOC };

const uint16_t GPIO_PIN[LEDn] = { 	GPIO_PIN_6 };

LEDs_t LED[LEDn];

/* Exported variables --------------------------------------------------------*/	
/* Private function prototypes -----------------------------------------------*/

//void LED_On(Led_TypeDef Led);
//void LED_Off(Led_TypeDef Led);
//void LED_Toggle(Led_TypeDef Led);
		
/* Private functions ---------------------------------------------------------*/

/**********************************************************************
  * @brief  Leds.
  * @param  None
  * @retval None
   ********************************************************************/
void LED_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	
	/*Configure GPIO pin : PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//-------------------------------------------------------------
/*	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);				//Enable PB3, PB4, PA15
	GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);							//Enable PD0, PD1
*/
	//-------------------------------------------------------------
}

/**********************************************************************
  * @brief  Turn on 1 led
  * @param  None
  * @retval None
   ********************************************************************/
void LED_On(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}
/**********************************************************************
  * @brief  Turn off 1 led
  * @param  None
  * @retval None
   ********************************************************************/
void LED_Off(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];  
}
/**********************************************************************
  * @brief  Toggle 1 led
  * @param  None
  * @retval None
   ********************************************************************/
void LED_Toggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**********************************************************************
  * @brief  Leds control thread
  * @param  None
  * @retval None
  ********************************************************************/
//void LED_Processing(void)
//{
//	static u8 i;
//	
//	for (i = 0; i < LEDn; i++)
//	{
//		if ( (LED[i].Status == SET) && (SystemCounter > LED[i].Counter) )
//		{
//			LED_Off((Led_TypeDef)i);
//			LED[i].Status = RESET;
//		}			
//	}
//}

/**********************************************************************
  * @brief  Torn on led for some time
  * @param  led: Led name
  *	@param  time_on: On time
  * @retval None
  ********************************************************************/
void LED_TurnON(Led_TypeDef led, u32 time_ms)
{
	LED_On(led);
	LED[led].Times = 1;
	LED[led].Counter = SystemCounter + time_ms;
}

/**********************************************************************
  * @brief  Led blinks few times
  * @param  led: Led name
  *	@param  time_on: On time
  *	@param  time_off: Off time
  *	@param  times: How many times to blink
  * @retval None
  ********************************************************************/
void LED_TurnON_Blink(Led_TypeDef led, u16 time_on, u16 time_off, u16 times)
{
	LED_On(led);
	LED[led].Counter = SystemCounter + time_on;
	LED[led].TimeOn = time_on;
	LED[led].TimeOff = time_off;
	LED[led].Times = (times*2)-1;
}

/**********************************************************************
  * @brief  Leds control thread
  * @param  None
  * @retval None
  ********************************************************************/
void LED_Processing(void)
{
	static u8 i;
	
	for (i = 0; i < LEDn; i++)
	{
		if (LED[i].Times != 0)
		{
			if ( (HAL_GPIO_ReadPin(GPIO_PORT[i], GPIO_PIN[i]) == SET) && (SystemCounter > LED[i].Counter) )
			{
				LED_Off((Led_TypeDef)i);
				LED[i].Counter = SystemCounter + LED[i].TimeOff;
				LED[i].Times--;
			}	
			else if ( (HAL_GPIO_ReadPin(GPIO_PORT[i], GPIO_PIN[i]) == RESET) && (SystemCounter > LED[i].Counter) )
			{
				LED_On((Led_TypeDef)i);
				LED[i].Counter = SystemCounter + LED[i].TimeOn;
				LED[i].Times--;
			}
		}		
	}
}











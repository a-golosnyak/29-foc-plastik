/**
  ******************************************************************************
  * @file    workspace.h
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention

  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Workspace_H
#define __Workspace_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Private typedef -----------------------------------------------------------*/

typedef struct
{	
	u32 Counter;
	s16 AdcData;
}WKSPC_t;


typedef enum
{
	NO_ERROR = 0,
	EEPROM_ERROR,
	COMMUNICATION_ERROR,
}Error_e;

typedef struct
{
	u8	NewAdcData	:1;
	u32 Error;
}Flag_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/

extern WKSPC_t	WKSPC;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void WKSPC_Init (void);
void WKSPC_Processing (void);


#endif /*__Workspace_H */



/******************END OF FILE*************************************************/












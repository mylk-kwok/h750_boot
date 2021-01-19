/*
 * boot.c
 *
 *  Created on: Jan 14, 2021
 *      Author: MYLK
 */

#include <stdio.h>
#include "boot.h"
#include "main.h"
#include "w25qxx.h"
#include "quadspi.h"

#define APPLICATION_ADDRESS  (uint32_t)0x90000000
typedef void (*pFunction)(void);
pFunction JumpToApplication;

int boot_entry(void)
{
	int res;

	W25QXX_Init();
	res = W25QXX_MftrDeviceID();
	printf("the id of w25qxx is 0x%x.\r\n",res);
	W25Q_Memory_Mapped_Enable();

    JumpToApplication = (pFunction)(*(__IO uint32_t *)(APPLICATION_ADDRESS + 4));
    __set_MSP(*(__IO uint32_t *)APPLICATION_ADDRESS);

    printf("jump to application!\r\n");
    JumpToApplication();

	return res;
}









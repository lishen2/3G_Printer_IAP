#include <stdio.h>
#include "stm32f10x.h"
#include "utils.h"
#include "ringbuf.h"
#include "usart_io.h"
#include "led.h"
#include "update.h"
#include "platform.h"

typedef void *(*EntryPoint)(void);

int main()
{
	int ret;
	u32 addr;
	EntryPoint ep;

	/* 硬件初始化 */
	HW_CommonInit();
	HW_InitSysTick();

	LED_Init();
	USARTIO_InitUsart1();

	/* 尝试更新固件 */
	ret = UP_TryUpdate();
	if (ret == ERROR_SUCCESS){

		printf("update success\n");

		LED_LightUp();
		delay_ms(3000);
		LED_Shutdown();			
	}

	/* 引导应用程序 */
	addr = 	*((u32*)PLATFORM_FLASH_PROGRAME_START);
	ep = (EntryPoint)(addr | 0x01);
	ep();

	return 0;
}





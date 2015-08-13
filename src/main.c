#include <stdio.h>
#include "stm32f10x.h"
#include "utils.h"
#include "ringbuf.h"
#include "usart_io.h"
#include "led.h"
#include "update.h"

int main()
{
	int ret;

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
    printf("Boot Programme\n");

	return 0;
}





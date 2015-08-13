#include <stdio.h>
#include "stm32f10x.h"
#include "utils.h"

vu32 g_jiffies = 0;

/* 设置寄存器，准备进入休眠状态 */
static inline void PWR_PrepareSleep(u32 SysCtrl_Set)
{
    if (SysCtrl_Set)
        SCB->SCR |= SCB_SCR_SLEEPONEXIT;   // Set SLEEPONEXIT                       
    else
        SCB->SCR &= ~SCB_SCR_SLEEPONEXIT;  // Reset SLEEPONEXIT

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP;        // Clear SLEEPDEEP bit
}

/* 毫秒级延时 */
void delay_ms(int n)
{
	n = n/10;

    PWR_PrepareSleep(0);
    
    n += g_jiffies;
    while(time_after(n, g_jiffies)){
//        __WFI();
    }
    
    return;
}

void HW_InitSysTick(void)
{
    /* Setup SysTick Timer for 10 msec interrupts  */
    if (SysTick_Config(SystemCoreClock / 100)) 
    { 
        /* Capture error */ 
        while (1);
    }  
    /* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00);

    return;
}

void HW_CommonInit(void)
{   
    /* set 2 bit preemptible */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);    

	return;
}

/* 将任意内容转化为ASCII */
void UTILS_ConvByteToASCII(char* inbuf, int inbufsize, char* outbuf, int outbufsize)
{
	unsigned i;

	if (outbufsize >= ((inbufsize<<1) - 1)) {
		for (i = 0; i < inbufsize; ++i){
			outbuf[(i<<1) + 0] = UTILS_Num2Char((inbuf[i] >> 4) & 0x0F);
			outbuf[(i<<1) + 1] = UTILS_Num2Char((inbuf[i] >> 0) & 0x0F);
		}
	}

	return;
}


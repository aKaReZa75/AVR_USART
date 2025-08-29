#include "aKaReZa.h"

extern bool usart_RxFlag;  
extern char usart_RxBuffer[__usart_RxBufferSize];  

int main(void)
{
  alcd_init();
  alcd_puts("Hello, World!");
  usart_Init(Initialize);
  globalInt_Enable;
  usart_Putsln("Hello, World!");
  while(1)
  {
    if(usart_RxFlag) 
    {
      alcd_clear();
      alcd_puts(usart_RxBuffer);  
      usart_Flush(); 
    };

    asm volatile ("nop"); /**< Insert a short delay here to allow the condition to be checked properly */
  };
};

/*
 * In this program, the while loop is very simple, with only an if statement checking for the usart_RxFlag. 
 * Since the clock speed of the microcontroller is high, and the main loop runs extremely fast, the if (usart_RxFlag) 
 * condition may not be triggered as expected, as the usart_RxFlag might not be set before the loop runs again.
 * To solve this issue, we introduce a small delay in the form of a No Operation (NOP) instruction using the line:
 * asm volatile ("nop");
 * The NOP instruction does nothing but takes a single clock cycle to execute. 
 * This short delay ensures that the microcontroller doesn't loop too quickly and gives enough time 
 * for the USART interrupt to set the usart_RxFlag and trigger the if condition.
 * If you add more logic or tasks inside the loop, or if the loop involves more time-consuming operations, 
 * the nop can potentially be removed, as the ISR will have sufficient time to set the usart_RxFlag properly. 
 * In such cases, the condition will be checked correctly, and you no longer need to rely on this short delay.
 */
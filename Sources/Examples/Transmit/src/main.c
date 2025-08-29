#include "aKaReZa.h"

char Buffer[20];
uint16_t Counter = 0;

int main(void)
{
  usart_Init(Initialize);
  usart_Putsln("Hello, World!");
  while(1)
  {
    Counter++;
    sprintf(Buffer, "Counter = %u", Counter);
    usart_Putsln(Buffer);
    delay_ms(500);
  };
};
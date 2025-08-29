#include "aKaReZa.h"

uint8_t Rx_Data = 0;

int main(void)
{
  alcd_init();
  usart_Init(Initialize);
  usart_Putsln("Hello, World!");
  while(1)
  {
    Rx_Data = usart_getChar();
    alcd_putc(Rx_Data);
  };
};
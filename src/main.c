/* Includes ------------------------------------------------------------------*/
#include "main.h"

int main(void)
{
  char *msg = "Hello World!\n\r";

  HAL_Init();
  Init();
  int i = 0;

  HAL_GPIO_WritePin(EN_INNO_GPIO_Port, EN_INNO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(CMD_BAT_GPIO_Port, CMD_BAT_Pin, GPIO_PIN_SET);

  uint8_t c = 0;

  while (1)
  {
      while(c == 0)
        HAL_UART_Receive(&hlpuart1, &c, 1, 0);
      trace_printf("\nBuffer = %c", c);
//    trace_printf("i = %d\n", i);
//    for(int h=0; h<5000000; h++);
//    i++;
  }
}

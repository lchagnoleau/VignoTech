/* Includes ------------------------------------------------------------------*/
#include "main.h"

int main(void)
{
  char *msg = "Hello World!\n\r";

  HAL_Init();
  Init();
  int i = 0;

  while (1)
  {
    trace_printf("i = %d\n", i);
    for(int h=0; h<5000000; h++);
    i++;
  }
}

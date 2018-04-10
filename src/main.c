/* Includes ------------------------------------------------------------------*/
#include "main.h"

int main(void)
{
  HAL_Init();
  Init();

  uint8_t GPS_buffer[100] = {0};
  uint8_t GPS_cmp = 0;
  uint8_t c = 0;
  HAL_StatusTypeDef rx_status;

  while (1)
  {
      while(c != '$')
        {
          rx_status = HAL_UART_Receive(&hlpuart1, &c, 1, 10);
          if(rx_status != HAL_OK)
            trace_printf("\nrx_status = 02X", rx_status);
        }
      GPS_buffer[GPS_cmp++] = c;
      while(c != '\n')
        {
          rx_status = HAL_UART_Receive(&hlpuart1, &c, 1, 10);
          if(rx_status != HAL_OK)
            trace_printf("\nrx_status = 02X", rx_status);
          GPS_buffer[GPS_cmp++] = c;
        }
      GPS_cmp = 0;
      c = 0;

      for(uint8_t i=0; GPS_buffer[i] != '\n'; i++)
        trace_printf("%c", GPS_buffer[i]);
  }
}

/* Includes ------------------------------------------------------------------*/
#include "main.h"

void InitGPS(void)
{
  HAL_GPIO_WritePin(EN_INNO_GPIO_Port, EN_INNO_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(EN_INNO_GPIO_Port, EN_INNO_Pin, GPIO_PIN_SET);
  HAL_Delay(200);

  /* Stop GSV */
  uint8_t stopGSV[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x38};

  /* Stop GLL */
  uint8_t stopGLL[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A};

  /* Stop RMC */
  uint8_t stopRMC[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3F};

  /* Stop GSA */
  uint8_t stopGSA[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x31};

  //GGA and VTG frame every 1 seconds
  uint8_t setGGA[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28};
  uint8_t setVTG[] = {0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x05, 0x4B};

  HAL_UART_Transmit(&hlpuart1, stopGSV, 16, 100);
  HAL_UART_Transmit(&hlpuart1, stopGLL, 16, 100);
  HAL_UART_Transmit(&hlpuart1, stopRMC, 16, 100);
  HAL_UART_Transmit(&hlpuart1, stopGSA, 16, 100);
  HAL_UART_Transmit(&hlpuart1, setGGA, 16, 100);
  HAL_UART_Transmit(&hlpuart1, setVTG, 16, 100);
}

void GetLine(uint8_t *buffer)
{
  uint8_t GPS_cmp = 0;
  uint8_t c = 0;

  LPUART1->CR1 &= 0xFFFE;
  LPUART1->CR1 |= 0x05;

  while(c != '$')
    {
      HAL_UART_Receive(&hlpuart1, &c, 1, 100);
    }
  buffer[GPS_cmp++] = c;
  while(c != '\n')
    {
      HAL_UART_Receive(&hlpuart1, &c, 1, 10);
      buffer[GPS_cmp++] = c;
    }
}

int main(void)
{
  HAL_Init();
  Init();
  InitGPS();

  uint8_t GPS_buffer[100] = {0};

  while(1)
  {
      GetLine(GPS_buffer);
      for(uint8_t i=0; GPS_buffer[i] != '\n'; i++)
        trace_printf("%c", GPS_buffer[i]);
  }
}

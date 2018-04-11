/*
 * gps.c
 *
 *  Created on: 11 avr. 2018
 *      Author: lchagnoleau
 */

#include "gps.h"

uint8_t GPS_GGA[NB_CARAC_CHAINE_GPS] = {0};
uint8_t GPS_VTG[NB_CARAC_CHAINE_GPS] = {0};
uint8_t frame_ready = 0;

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
  HAL_Delay(2000);
}

void GPS_Update_Frames(void)
{
  /* Capture 2 lines to get VGA and VTG frame */

  uint8_t GPS_cmp = 0;
  uint8_t c = 0, linecmp = 0;
  uint8_t buffer[200] = {0};

  LPUART1->CR1 &= 0xFFFE;
  LPUART1->CR1 |= 0x05;

  while(c != '$')
    {
      HAL_UART_Receive(&hlpuart1, &c, 1, 100);
    }
  buffer[GPS_cmp++] = c;
  while(linecmp < 2)
    {
      if(c == '\n') linecmp++;
      HAL_UART_Receive(&hlpuart1, &c, 1, 10);
      buffer[GPS_cmp++] = c;
    }
  /********************************************/

  /* Erase old frames */

  for(uint8_t i=0; i<NB_CARAC_CHAINE_GPS; i++)
    {
      GPS_VTG[i] = 0x00;
      GPS_GGA[i] = 0x00;
    }

  /********************/

  /* Parse the 2 frames */

  uint8_t i = 0, h = 0;
  for(i=0; buffer[i] != '\n'; i++)
    GPS_VTG[i] = buffer[i];
  GPS_VTG[i+1] = '\0';

  for(h=i+1; buffer[h] != '\n'; h++)
    GPS_GGA[h-(i+1)] = buffer[h];
  GPS_GGA[h-i] = '\0';

  /**********************/

  frame_ready = 1;

}







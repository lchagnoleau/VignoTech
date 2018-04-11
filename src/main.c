/* Includes ------------------------------------------------------------------*/
#include "main.h"

int main(void)
{
  HAL_Init();
  Init();
  InitGPS();

  uint8_t GPS_buffer[100] = {0};
  uint8_t length = 0;
  uint8_t i = 0;

  while(1)
  {
    GPS_Update_Frames();

    if(frame_ready)
    {
        frame_ready = 0;
        trace_printf("\nGGA : %s", GPS_GGA);
        trace_printf("\nVTG : %s", GPS_VTG);
    }
  }
}

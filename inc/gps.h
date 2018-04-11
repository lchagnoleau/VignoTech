/*
 * gps.h
 *
 *  Created on: 11 avr. 2018
 *      Author: lchagnoleau
 */

#ifndef GPS_H_
#define GPS_H_

#include "main.h"

#define NB_CARAC_CHAINE_GPS 200

void InitGPS(void);
void GPS_Update_Frames(void);

#endif /* GPS_H_ */

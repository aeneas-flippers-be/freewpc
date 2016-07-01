/*
 * mapmode.h
 *
 *  Created on: 22 jun. 2016
 *      Author: Aeneas Verhe
 */

#ifndef MACHINE_WWAT_MAPMODE_H_
#define MACHINE_WWAT_MAPMODE_H_

//smallx
#define smallx_width 5
#define smallx_height 3
static char smallx_bits[] = {smallx_width, smallx_height,
  0x04, 0x11, 0x04, };

//smallrock
#define smrock_width 5
#define smrock_height 4
static char smrock_bits[] = {smrock_width, smrock_height,
  0x1B, 0x15, 0x16, 0x0E, };

//smallrock
#define smrock2_width 5
#define smrock2_height 4
static char smrock2_bits[] = {smrock2_width, smrock2_height,
  0x11, 0x0E, 0x19, 0x06, };


//bigfoot
#define smcave_width 13
#define smcave_height 6
static char smcave_bits[] = {smcave_width, smcave_height,
  0x03, 0x18, 0xAD, 0x15, 0x76, 0x0D, 0x76, 0x06, 0x76, 0x0D, 0xF8, 0x00, };


#endif /* MACHINE_WWAT_MAPMODE_H_ */

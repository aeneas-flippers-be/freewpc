/*
 * waterfall.h
 *
 *  Created on: 24 jun. 2016
 *      Author: Aeneas Verhe
 */

#ifndef MACHINE_WWAT_WATERFALL_H_
#define MACHINE_WWAT_WATERFALL_H_

//fallraft 1
#define fallraft1_width 7
#define fallraft1_height 5
static char fallraft1_bits[] = {fallraft1_width, fallraft1_height,
  0x6B, 0x40, 0x2A, 0x40, 0x6B, };

//fallraft 2
static char fallraft2_bits[] = {fallraft1_width, fallraft1_height,
  0x75, 0x40, 0x2A, 0x40, 0x75, };

//fallraft left
static char fallraftl_bits[] = {fallraft1_width, fallraft1_height,
  0x75, 0x40, 0x2A, 0x40, 0x6B, };

//fallraft right
static char fallraftr_bits[] = {fallraft1_width, fallraft1_height,
  0x6B, 0x40, 0x2A, 0x40, 0x75, };


#endif /* MACHINE_WWAT_WATERFALL_H_ */

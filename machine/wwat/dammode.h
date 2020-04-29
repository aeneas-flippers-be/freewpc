/*
 * dammode.h
 *
 *  Created on: 27 jun. 2016
 *      Author: Aeneas Verhe
 */

#ifndef MACHINE_WWAT_DAMMODE_H_
#define MACHINE_WWAT_DAMMODE_H_

//beaver1
#define beaver1_width 16
#define beaver1_height 16
static char beaver1_bits[] = {beaver1_width, beaver1_height,
0x80, 0x07, 0x40, 0x08, 0x46, 0x12, 0x49, 0x10, 0x29, 0x08, 0x29, 
0x44, 0x29, 0x78, 0x11, 0x30, 0x11, 0x0c, 0x12, 0x09, 0x14, 
0x1e, 0x18, 0x30, 0xfc, 0x3f, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, };

//beaver2
#define beaver2_width 16
#define beaver2_height 16
static char beaver2_bits[] = {beaver2_width, beaver2_height,
0xe0, 0x01, 0x10, 0x02, 0x48, 0x62, 0x08, 0x92, 0x10, 0x94, 0x22, 0x94, 
0x1e, 0x94, 0x0c, 0x88, 0x30, 0x88, 0x90, 0x48, 0x78, 0x28, 0x0c, 0x18, 
0xfc, 0x3f, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, };



#endif /* MACHINE_WWAT_DAMMODE_H_ */

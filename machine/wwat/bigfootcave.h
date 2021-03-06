/*
 * bigfootcave.h
 *
 *  Created on: 20 jun. 2016
 *      Author: Aeneas Verhe
 */

#ifndef MACHINE_WWAT_BIGFOOTCAVE_H_
#define MACHINE_WWAT_BIGFOOTCAVE_H_


//flashlight
#define bfc_flash_width 16
#define bfc_flash_height 16
static U8 bfc_flash_bits[] = { bfc_flash_width, bfc_flash_height,
0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x80, 0x79, 0xfe, 0x7f, 0xc7, 0xff, 0xff, 0x7f, 0xff, 0xff,
0xfe, 0x7f, 0x00, 0x78, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//key
#define bfc_key_width 16
#define bfc_key_height 16
static U8 bfc_key_bits[] = { bfc_key_width, bfc_key_height,
0x06, 0x00, 0x09, 0x00, 0xf9, 0x7f, 0xf9, 0xc0, 0xf9, 0xff, 0x09, 0x7e, 0x09, 0x7a, 0x06, 0x52, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//map
#define bfc_map_width 16
#define bfc_map_height 16
static U8 bfc_map_bits[] = { bfc_map_width, bfc_map_height,
0xbc, 0xdf, 0xa3, 0xa0, 0x41, 0xd4, 0x59, 0x48, 0x25, 0x40, 0x02, 0x78, 0x29, 0x94, 0x11, 0x8a,
0x2a, 0x8a, 0x01, 0x85, 0x3d, 0xbc, 0xc2, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//camera
#define bfc_cam_width 16
#define bfc_cam_height 16
static U8 bfc_cam_bits[] = { bfc_cam_width, bfc_cam_height,
0x00, 0x00, 0x80, 0x01, 0xc6, 0x03, 0xff, 0xff, 0x01, 0x80, 0x0d, 0xb0, 0x81, 0xb1, 0xc1, 0x83,
0xc1, 0x83, 0x81, 0x81, 0x01, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

//cow
#define bfc_cow_width 16
#define bfc_cow_height 16
static U8 bfc_cow_bits[] = { bfc_cow_width, bfc_cow_height,
0x00, 0x00, 0x02, 0x01, 0x86, 0x01, 0xfc, 0x00, 0x02, 0x01, 0x4b, 0x03, 0x85, 0x02, 0x84, 0x7f,
0xc8, 0xc4, 0xc8, 0x92, 0x30, 0xff, 0x80, 0x61, 0x80, 0x61, 0x80, 0x61, 0x00, 0x00, 0x00, 0x00,
};
 //bigfoot
#define bfc_foot_width 16
#define bfc_foot_height 16
static U8 bfc_foot_bits[] = { bfc_foot_width, bfc_foot_height,
0x2a, 0x00, 0x22, 0x00, 0x2a, 0x00, 0x22, 0x00, 0x2a, 0x00, 0xc2, 0x01, 0x01, 0x6e, 0x01, 0x90,
0x31, 0x90, 0xce, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};



#endif /* MACHINE_WWAT_BIGFOOTCAVE_H_ */

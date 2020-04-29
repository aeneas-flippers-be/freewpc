/*
 * Copyright 2016 Aeneas Verhe
 *
 * This file is part of FreeWPC.
 *
 * FreeWPC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * FreeWPC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FreeWPC; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
RULES:
Shoot bigfoot cave after lighting it to collect items - flashlight, key, camera, map, cow, bigfoot
items can be used in other modes
get camera to spot bigfoot
cow at 20 spots
*/


#include <freewpc.h>
#include <status.h>
#include "bigfootcave.h"

extern U8 caveshots;
extern U8 bigfoot_found;


void cave_award_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 80, 10, "YOU FOUND");

	switch (caveshots)
	{
		case 1:
			font_render_string_center (&font_fixed6, 80, 21, "A FLASHLIGHT");
			bitmap_blit (bfc_flash_bits,  5, 10);
			break;
		case 2:
			font_render_string_center (&font_fixed6, 80, 21, "A KEY");
			bitmap_blit (bfc_key_bits,  5, 10);
			break;
		case 3:
			font_render_string_center (&font_fixed6, 80, 21, "A CAMERA");
			bitmap_blit (bfc_cam_bits,  5, 10);
			break;
		case 5:
			font_render_string_center (&font_fixed6, 80, 21, "A MAP");
			bitmap_blit (bfc_map_bits,  5, 10);
			break;
		case 20:
			font_render_string_center (&font_fixed6, 80, 21, "A COW");
			bitmap_blit (bfc_cow_bits,  5, 10);
			break;
		default:
			font_render_string_center (&font_fixed6, 80, 21, "BIGFOOT");
			bitmap_blit (bfc_foot_bits,  5, 10);
			break;
	}

	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void cave_resetitems (void)
{
	flag_off (FLAG_BFCMAP);
	flag_off (FLAG_BFCKEY);
	flag_off (FLAG_BFCLIGHT);
	flag_off (FLAG_BFCCAMERA);
}

void cave_award (void)
{
	global_flag_off (GLOBAL_FLAG_BIGFOOTLIT);

//	bfh_showface_cw ();
	leff_start (LEFF_FL_CAVE);

	bounded_increment (caveshots, 255);

	deff_start (DEFF_CAVE_AWARD);
	lamp_tristate_off (LM_LIGHT_WHIRLPOOL);
	score (SC_250K);

	switch (caveshots)
	{
		case 1:
			flag_on (FLAG_BFCLIGHT);
			speech_start (SND_HEYFLASHLIGHT, SL_4S);
			break;
		case 2:
			flag_on (FLAG_BFCKEY);
			speech_start (SND_HEYKEY, SL_4S);
			break;
		case 3:
			flag_on (FLAG_BFCCAMERA);
			speech_start (SND_HEYCAMERA, SL_4S);
			break;
		case 5:
			flag_on (FLAG_BFCMAP);
//			global_flag_on (GLOBAL_FLAG_WPOOLLIT);
			speech_start (SND_HEYMAP, SL_4S);
			break;
		case 20:
			speech_start (SND_HEYAWCOW, SL_4S);
			score (SC_250K);
			break;
		default:
			speech_start (SND_CAMERASOUND, SL_2S);
			bounded_increment (bigfoot_found, 255);
			break;
	}
}


CALLSET_ENTRY (bfcave, sw_bigfoot_cave)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;
	
	if (global_flag_test (GLOBAL_FLAG_BIGFOOTLIT))
	{
		cave_award ();
	}
	else
	{
		flasher_pulse (FLASH_BIGFOOT_CAVE_FL);
		score (SC_20K);
	}
}

CALLSET_ENTRY (bfcave, start_ball)
{
	global_flag_off (GLOBAL_FLAG_BIGFOOTLIT);
}

CALLSET_ENTRY (bfcave, start_player)
{
	cave_resetitems ();
	caveshots = 0;
	bigfoot_found = 0;
}


CALLSET_ENTRY (bfcave, status_report)
{
	status_page_init ();
	font_render_string (&font_mono5, 2, 2, "FOUND");

	if (flag_test (FLAG_BFCMAP))
		font_render_string_center (&font_mono5, 64, 8, "MAP");
	if (flag_test (FLAG_BFCKEY))
		font_render_string_center (&font_mono5, 64, 14, "KEY");
	if (flag_test (FLAG_BFCLIGHT))
		font_render_string_center (&font_mono5, 64, 20, "FLASHLIGHT");
	if (flag_test (FLAG_BFCCAMERA))
		font_render_string_center (&font_mono5, 64, 26, "CAMERA");

	status_page_complete ();
}



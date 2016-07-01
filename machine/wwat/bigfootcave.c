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
Shoot bigfoot cave after lighting it to collect items
items can be used in other modes
get camera to spot hotfoot
cow at 20 spots
*/


#include <freewpc.h>
#include "bigfootcave.h"

__local__ U8 caveshots;

void twobank_off (void)
{
	global_flag_off (GLOBAL_FLAG_BIGFOOTTGT1);
	global_flag_off (GLOBAL_FLAG_BIGFOOTTGT2);
	lamp_tristate_off (LM_2BANK_UP);
	lamp_tristate_off (LM_2BANK_LOW);
}


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

	task_pid_t tp = task_find_gid (GID_BIGFOOT);
	if (tp) 
	{
		score (SC_250K);
		font_render_string_center (&font_fixed6, 80, 28, "250K BONUS");
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

	bfh_showface_cw ();
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
			global_flag_on (GLOBAL_FLAG_WPOOLLIT);
			speech_start (SND_HEYMAP, SL_4S);
			break;
		case 20:
			speech_start (SND_HEYAWCOW, SL_4S);
			score (SC_250K);
			break;
		default:
			speech_start (SND_CAMERASOUND, SL_2S);
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
		score (SC_20K);
	}
}


CALLSET_ENTRY (bfcave, start_ball)
{
	global_flag_off (GLOBAL_FLAG_BIGFOOTLIT);	
	twobank_off ();
}

CALLSET_ENTRY (bfcave, start_player)
{
	global_flag_off (GLOBAL_FLAG_BIGFOOTLIT);	
	cave_resetitems ();
	caveshots = 0;
}




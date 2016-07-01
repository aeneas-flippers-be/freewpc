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
hitting 2 white targets qualifies bigfoot cave
scores double in wpch
*/

#include <freewpc.h>
#include "bigfoottgt.h"

void bftgt_deff (void)
{
	dmd_alloc_low_clean ();

	if (global_flag_test (GLOBAL_FLAG_BIGFOOTTGT1))
			bitmap_blit (bfc_footleft2_bits,  1, 5);
	else
			bitmap_blit (bfc_footleft1_bits,  1, 5);

	if (global_flag_test (GLOBAL_FLAG_BIGFOOTTGT2))
			bitmap_blit (bfc_footright2_bits,  110, 5);
	else
			bitmap_blit (bfc_footright1_bits,  110, 5);

	dmd_show_low ();
	task_sleep_sec (2);
	deff_exit ();
}

void bftgt_task (void)
{
	task_sleep_sec (8);
	task_exit ();
}

void bftgt_ok_deff (void)
{
	dmd_alloc_low_clean ();

	bitmap_blit (bfc_footleft2_bits,  1, 5);
	bitmap_blit (bfc_footright2_bits,  110, 5);

	if (global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
	{
		font_render_string_center (&font_fixed6, 64, 10, "2X JACKPOT");
		font_render_string_center (&font_fixed6, 64, 21, "SCORE LIT");
	}
	else
	{
		font_render_string_center (&font_fixed6, 64, 10, "VISIT");
		font_render_string_center (&font_fixed6, 64, 21, "CAVE");
	}

	dmd_show_low ();
	task_sleep_sec (2);
	deff_exit ();
}


void bftgt_reset (void)
{
	global_flag_off (GLOBAL_FLAG_BIGFOOTTGT1);
	global_flag_off (GLOBAL_FLAG_BIGFOOTTGT2);
	lamp_off (LM_2BANK_UP);
	lamp_off (LM_2BANK_LOW);
}

bool bftgt_twobank_checklit (void)
{
	if (global_flag_test (GLOBAL_FLAG_BIGFOOTTGT1) && global_flag_test (GLOBAL_FLAG_BIGFOOTTGT2))
		return TRUE;
	else
		return FALSE;
}

/* check if all 2 are lit */
void bftgt_twobank_check (void)
{
	score (SC_20K);

	if (global_flag_test (GLOBAL_FLAG_BIGFOOTLIT))
		return;

	if (bftgt_twobank_checklit)
	{
		global_flag_on (GLOBAL_FLAG_BIGFOOTLIT);	
		speech_start (SND_BGFT_GR1, SL_2S);
		bftgt_reset ();
	
		deff_start (DEFF_BFTGT_OK);

		if (global_flag_test (GLOBAL_FLAG_RAFTMODE))
		{
			task_create_gid1 (GID_BIGFOOT, bftgt_task);
			bfh_rotate_ccw (2);
		}

//		leff_start (LEFF_BFTG);
	}
	else
		deff_start (DEFF_BFTGT);
}

CALLSET_ENTRY (bftgt, lamp_update)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
	{
		if (global_flag_test (GLOBAL_FLAG_BIGFOOTTGT1))
			lamp_on (LM_2BANK_UP);
		if (global_flag_test (GLOBAL_FLAG_BIGFOOTTGT2))
			lamp_on (LM_2BANK_LOW);
	}
}

CALLSET_ENTRY (bftgt, sw_2bank_up)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
	{
		global_flag_on (GLOBAL_FLAG_BIGFOOTTGT1);	
		bftgt_twobank_check ();
	}
}

CALLSET_ENTRY (bftgt, sw_2bank_low)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
	{
		global_flag_on (GLOBAL_FLAG_BIGFOOTTGT2);	
		bftgt_twobank_check ();
	}
}

CALLSET_ENTRY (bftgt, end_ball)
{
//	deff_stop (DEFF_BFTGT_OK);
//	deff_stop (DEFF_BFTGT);
	task_kill_gid (GID_BIGFOOT);
}

CALLSET_ENTRY (bftgt, start_ball)
{
	bftgt_reset ();
}


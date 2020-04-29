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
BIGFOOTTGT.C
hitting 2 white targets qualifies bigfoot cave and starts cave hurryup
scores double in wpch
*/

#include <freewpc.h>
#include "bigfoottgt.h"

//show feet on dmd
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



/* check if all 2 are lit */
void bftgt_twobank_check (void)
{
	score (SC_20K);

	if (global_flag_test (GLOBAL_FLAG_BIGFOOTLIT))
		return;

	//check if both targets are completed
	if (global_flag_test (GLOBAL_FLAG_BIGFOOTTGT1) && global_flag_test (GLOBAL_FLAG_BIGFOOTTGT2))
	{
		callset_invoke (bigftgt_completed);  //also in mball
	}
	else
		deff_start (DEFF_BFTGT);
}



CALLSET_ENTRY (bftgt, bigftgt_completed)
{
	global_flag_on (GLOBAL_FLAG_BIGFOOTLIT);  //RULE : light bigfoot cave for award after completing two targets
	bftgt_reset ();

	deff_start (DEFF_BFTGT_OK);

	if (global_flag_test (GLOBAL_FLAG_RAFTMODE) && !global_flag_test (GLOBAL_FLAG_MBALL_RUNNING))
	{
		speech_start (SND_BGFT_GR1, SL_2S);  //sound here as another starts in mball.c
//			task_create_gid1 (GID_BIGFOOT, bftgt_task);
		cave_start ();   // RULE : start cave hurryup
//			bfh_rotate_ccw (2);
	}
}

CALLSET_ENTRY (bftgt, raft_lamps_off)
{
	lamp_off (LM_2BANK_UP);
	lamp_off (LM_2BANK_LOW);
}

CALLSET_ENTRY (bftgt, raft_lamps_on)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE))
	{
		if (global_flag_test (GLOBAL_FLAG_BIGFOOTTGT1))
			lamp_on (LM_2BANK_UP);
		if (global_flag_test (GLOBAL_FLAG_BIGFOOTTGT2))
			lamp_on (LM_2BANK_LOW);
	}
}

//target hit
CALLSET_ENTRY (bftgt, sw_2bank_up)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
	{
		global_flag_on (GLOBAL_FLAG_BIGFOOTTGT1);
		lamp_on (LM_2BANK_UP);
		bftgt_twobank_check ();
	}
}

//target hit
CALLSET_ENTRY (bftgt, sw_2bank_low)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
	{
		global_flag_on (GLOBAL_FLAG_BIGFOOTTGT2);
		lamp_on (LM_2BANK_LOW);
		bftgt_twobank_check ();
	}
}

//-ALLSET_ENTRY (bftgt, end_ball, tilt)
//{
//	deff_stop (DEFF_BFTGT_OK);
//	deff_stop (DEFF_BFTGT);
//	task_kill_gid (GID_BIGFOOT);
//}

CALLSET_ENTRY (bftgt, start_ball)
{
	bftgt_reset ();
}


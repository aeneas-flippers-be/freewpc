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
Riverdam mode
Timed mode - 60 seconds - Countdown timer for score
hit all 5 river targets to break dam and score
IDEA continue as long as time is running, move to next dam ?
*/

#include <freewpc.h>
#include <timedmode.h>
//#include <bigfhead.h>
#include "dammode.h"
#include <ballsave.h>


U8 dam_timer;

//bool dam_gothim;

//score_t dam_score;
//score_t dam_scoremin;


void dam_mode_init (void)
{
/*	score_zero (dam_score);
	score_add (dam_score, score_table[SC_20M]);
	score_zero (dam_scoremin);
	score_add (dam_scoremin, score_table[SC_1M]);
	dam_gothim = FALSE;
*/

	global_flag_on (GLOBAL_FLAG_DAM_RUNNING);

	lamps_out ();

	global_flag_off (GLOBAL_FLAG_RIVERR1);
	global_flag_off (GLOBAL_FLAG_RIVERR2);
	global_flag_off (GLOBAL_FLAG_RIVERI);
	global_flag_off (GLOBAL_FLAG_RIVERV);
	global_flag_off (GLOBAL_FLAG_RIVERE);

	lamp_tristate_flash (LM_RIVER_R1);
	lamp_tristate_flash (LM_RIVER_I);
	lamp_tristate_flash (LM_RIVER_V);
	lamp_tristate_flash (LM_RIVER_E);
	lamp_tristate_flash (LM_RIVER_R2);

	ballsave_add_time (3);
//	global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
}

void dam_mode_exit (void)
{
	global_flag_off (GLOBAL_FLAG_DAM_RUNNING);
	global_flag_off (GLOBAL_FLAG_PF_LAMPS_OFF);
	deff_stop (DEFF_DAM_RUNNING);

	global_flag_off (GLOBAL_FLAG_RIVERR1);
	global_flag_off (GLOBAL_FLAG_RIVERR2);
	global_flag_off (GLOBAL_FLAG_RIVERI);
	global_flag_off (GLOBAL_FLAG_RIVERV);
	global_flag_off (GLOBAL_FLAG_RIVERE);

	global_flag_on (GLOBAL_FLAG_RAFTMODE);

//	if (!dam_gothim)
//		speech_start (SND_DANGLOSTANOTHER, SL_4S);
}


void dam_drawdam (void)
{
		if (!global_flag_test (GLOBAL_FLAG_RIVERR1))
			bitmap_blit2 (beaver1_bits,  5, 2);
		if (!global_flag_test (GLOBAL_FLAG_RIVERI))
			bitmap_blit2 (beaver1_bits,  35, 2);
		if (!global_flag_test (GLOBAL_FLAG_RIVERV))
			bitmap_blit2 (beaver1_bits,  64, 2);
		if (!global_flag_test (GLOBAL_FLAG_RIVERE))
			bitmap_blit2 (beaver2_bits,  90, 2);
		if (!global_flag_test (GLOBAL_FLAG_RIVERR2))
			bitmap_blit2 (beaver2_bits,  90, 2);
		sprintf ("%d", dam_timer);
		font_render_string (&font_var5, 2, 2, sprintf_buffer);
}

void dam_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();
		frame_draw (IMG_WATER1);
		dam_drawdam ();
		dmd_show_low ();
		task_sleep (TIME_100MS);

		dmd_alloc_low_clean ();
		frame_draw (IMG_WATER2);
		dam_drawdam ();
		dmd_show_low ();
		task_sleep (TIME_100MS);
	}
}


struct timed_mode_ops dam_mode = {
	DEFAULT_MODE,
	.init = dam_mode_init,
	.exit = dam_mode_exit,
//	.music = MUS_MANOVERB_1,
//	.deff_running = DEFF_DAM_RUNNING,
	.gid = GID_MANO_MODE,
	.prio = PRI_GAME_MODE3,
	.init_timer = 60,
	.timer = &dam_timer,
	.grace_timer = 1,
	.pause = system_timer_pause,
};

void dam_testshot (void)
{
	if (global_flag_test (GLOBAL_FLAG_RIVERR1) && global_flag_test (GLOBAL_FLAG_RIVERR2) && global_flag_test (GLOBAL_FLAG_RIVERI)
		&& global_flag_test (GLOBAL_FLAG_RIVERV) && global_flag_test (GLOBAL_FLAG_RIVERE))
	{
		//todo 
		//eff_start (DEFF_DAM_OK);
		timed_mode_end (&dam_mode);
	}
}

void dam_shotmade (U8 shot)
{
	score (SC_1M);

	timed_mode_add (&dam_mode, 5);
	

	switch (shot)
	{
		case 1:
			global_flag_on (GLOBAL_FLAG_RIVERR1);
			lamp_tristate_on (LM_RIVER_R1);
			break;
		case 2:
			global_flag_on (GLOBAL_FLAG_RIVERI);
			lamp_tristate_on (LM_RIVER_I);
			break;
		case 3:
			global_flag_on (GLOBAL_FLAG_RIVERV);
			lamp_tristate_on (LM_RIVER_V);
			break;
		case 4:
			global_flag_on (GLOBAL_FLAG_RIVERE);
			lamp_tristate_on (LM_RIVER_E);
			break;
		case 5:
			global_flag_on (GLOBAL_FLAG_RIVERR2);
			lamp_tristate_on (LM_RIVER_R2);
			break;
	}
	dam_testshot ();
}


void dam_start (void)
{
	global_flag_off (GLOBAL_FLAG_RAFTMODE);

//	speech_start (SND_MANOVERB, SL_3S);

	timed_mode_begin (&dam_mode);
}



CALLSET_ENTRY (dam, sw_river_r1)
{
	if (global_flag_test (GLOBAL_FLAG_DAM_RUNNING) && !global_flag_test (GLOBAL_FLAG_RIVERR1))
		dam_shotmade (1);
}

CALLSET_ENTRY (dam, sw_river_i)
{
	if (global_flag_test (GLOBAL_FLAG_DAM_RUNNING) && !global_flag_test (GLOBAL_FLAG_RIVERR1))
		dam_shotmade (2);
}

CALLSET_ENTRY (dam, sw_river_v)
{
	if (global_flag_test (GLOBAL_FLAG_DAM_RUNNING) && !global_flag_test (GLOBAL_FLAG_RIVERR1))
		dam_shotmade (3);
}

CALLSET_ENTRY (dam, sw_river_e)
{
	if (global_flag_test (GLOBAL_FLAG_DAM_RUNNING) && !global_flag_test (GLOBAL_FLAG_RIVERR1))
		dam_shotmade (4);
}

CALLSET_ENTRY (dam, sw_river_r2)
{
	if (global_flag_test (GLOBAL_FLAG_DAM_RUNNING) && !global_flag_test (GLOBAL_FLAG_RIVERR1))
		dam_shotmade (5);
}

CALLSET_ENTRY (dam, display_update)
{
	if (timed_mode_running_p (&dam_mode))
	{
		deff_start_bg (DEFF_DAM_RUNNING, 0);
	}
}

CALLSET_ENTRY (dam, music_refresh)
{
	if (timed_mode_running_p (&dam_mode))
	{
		music_request (MUS_MANOVERB_1, PRI_GAME_MODE1 +3);
	}
}

CALLSET_ENTRY (dam, end_ball)
{
	if (timed_mode_running_p (&dam_mode))
		timed_mode_end (&dam_mode);
}

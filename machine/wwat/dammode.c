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

lit inlanes dont work in this mode
*/

#include <freewpc.h>
#include <timedmode.h>
//#include <bigfhead.h>
#include "dammode.h"
#include <ballsave.h>

#define DAM_MODE_TIME 60

U8 dam_timer;

extern bool rivtarget1;
extern bool rivtarget2;
extern bool rivtarget3;
extern bool rivtarget4;
extern bool rivtarget5;


void dam_mode_init (void)
{
	global_flag_on (GLOBAL_FLAG_DAM_RUNNING);
	river_off ();

	rivtarget1 = FALSE;
	rivtarget2 = FALSE;
	rivtarget3 = FALSE;
	rivtarget4 = FALSE;
	rivtarget5 = FALSE;

	lamp_tristate_flash (LM_RIVER_R1);
	lamp_tristate_flash (LM_RIVER_I);
	lamp_tristate_flash (LM_RIVER_V);
	lamp_tristate_flash (LM_RIVER_E);
	lamp_tristate_flash (LM_RIVER_R2);

	ballsave_add_time (3);
}

void dam_mode_exit (void)
{
	deff_stop (DEFF_DAM_RUNNING);
//	river_off ();
	lamp_tristate_off (LM_RIVER_R1);
	lamp_tristate_off (LM_RIVER_I);
	lamp_tristate_off (LM_RIVER_V);
	lamp_tristate_off (LM_RIVER_E);
	lamp_tristate_off (LM_RIVER_R2);

//	raftmode_on ();
	global_flag_off (GLOBAL_FLAG_DAM_RUNNING);
	river_lamps_on ();
}


void dam_drawdam (void)
{
		sprintf ("%d", dam_timer);
		font_render_string (&font_var5, 2, 2, sprintf_buffer);

		if (!rivtarget1)
			bitmap_blit (beaver1_bits,  8, 6);
		if (!rivtarget2)
			bitmap_blit (beaver1_bits,  32, 6);
		if (!rivtarget3)
			bitmap_blit (beaver1_bits,  56, 6);
		if (!rivtarget4)
			bitmap_blit (beaver2_bits,  80, 6);
		if (!rivtarget5)
			bitmap_blit (beaver2_bits,  104, 6);
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
	.init_timer = DAM_MODE_TIME,
	.timer = &dam_timer,
	.grace_timer = 0,
	.pause = system_timer_pause,
};

void dam_testshot (void)
{
	if (rivtarget1 && rivtarget2 && rivtarget3 && rivtarget4 && rivtarget5)
	{
		deff_start (DEFF_DAM_OK);
		score (SC_10M);
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
			rivtarget1 = TRUE;
			lamp_tristate_off (LM_RIVER_R1);
			break;
		case 2:
			rivtarget2 = TRUE;
			lamp_tristate_off (LM_RIVER_I);
			break;
		case 3:
			rivtarget3 = TRUE;
			lamp_tristate_off (LM_RIVER_V);
			break;
		case 4:
			rivtarget4 = TRUE;
			lamp_tristate_off (LM_RIVER_E);
			break;
		case 5:
			rivtarget5 = TRUE;
			lamp_tristate_off (LM_RIVER_R2);
			break;
	}
	dam_testshot ();
}


void dam_start (void)
{
//	raftmode_off ();

//	speech_start (SND_MANOVERB, SL_3S);

	timed_mode_begin (&dam_mode);
}



CALLSET_ENTRY (dam, sw_river_r1)
{
	if (timed_mode_running_p (&dam_mode) && !rivtarget1)
		dam_shotmade (1);
}

CALLSET_ENTRY (dam, sw_river_i)
{
	if (timed_mode_running_p (&dam_mode) && !rivtarget2)
		dam_shotmade (2);
}

CALLSET_ENTRY (dam, sw_river_v)
{
	if (timed_mode_running_p (&dam_mode) && !rivtarget3)
		dam_shotmade (3);
}

CALLSET_ENTRY (dam, sw_river_e)
{
	if (timed_mode_running_p (&dam_mode) && !rivtarget4)
		dam_shotmade (4);
}

CALLSET_ENTRY (dam, sw_river_r2)
{
	if (timed_mode_running_p (&dam_mode) && !rivtarget5)
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

CALLSET_ENTRY (dam, end_ball, tilt)
{
	if (timed_mode_running_p (&dam_mode))
		timed_mode_end (&dam_mode);
}

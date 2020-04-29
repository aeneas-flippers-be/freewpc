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
WP mode Man Overboard  - started in whirlpool
Timed mode - 20 seconds - Countdown timer for score
Shoot 1 random hazard
Change with original game : go dark unless you've found the flashlight
*/

#include <freewpc.h>
#include <timedmode.h>
#include <bigfhead.h>
#include "wpmanoverb.h"

#define WPMANO_MODE_TIME 20


U8 wpmano_timer;
U8 wpmano_randomhz;

bool wpmano_gothim;

score_t wpmano_score;


void wpmano_score_task (void)
{
	task_sleep_sec (1);
	while (score_compare (wpmano_score, score_table[SC_1M]) > 0)
	{
		score_sub (wpmano_score, score_table[SC_195110]);
		task_sleep (TIME_200MS);
	}
	score_copy (wpmano_score, score_table[SC_1M]);
	task_exit ();
}


void wpmano_mode_init (void)
{
	if (flag_test (FLAG_BFCLIGHT))
	{
		switch (wpmano_randomhz)
		{
			case 1:
				lamp_tristate_flash (LM_HZ_BOULDER_GARDEN);
				break;
			case 2:
				lamp_tristate_flash (LM_HZ_SPINE_CHILLER);
				break;
			case 3:
				lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
				break;
			case 4:
				lamp_tristate_flash (LM_HZ_DISDROP);
				break;
			case 5:
				lamp_tristate_flash (LM_HZ_BOOM_BEND);
				break;
			case 6:
				lamp_tristate_flash (LM_HZ_INSANITY_FALLS);
				break;
			case 7:
				lamp_tristate_flash (LM_HZ_BIGFOOT_BLUFF);
				break;
		}
	} 

//	while (deff_get_active() != DEFF_WPMANO_RUNNING)
//	{
//		task_sleep (TIME_100MS);
//	}

	task_sleep (TIME_200MS);
	global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
}

void wpmano_mode_exit (void)
{
	task_kill_gid (GID_MANO);
	lamp_tristate_off (LM_BD_MAN_OVERBD);
	raft_hz_lamps_tri_off ();

	deff_stop (DEFF_WPMANO_RUNNING);

	raftmode_on ();

	if (!wpmano_gothim)
		speech_start (SND_DANGLOSTANOTHER, SL_4S);
}

void wpmano_rendertext (void)
{
		font_render_string_center (&font_var5, 80, 5, "MAN OVERBOARD");
		sprintf_score (wpmano_score);
		font_render_string_center (&font_fixed6, 80, 16, sprintf_buffer);

		if (flag_test (FLAG_BFCLIGHT))
			font_render_string_right (&font_var5, 120, 27, "SHOOT FLASHING HAZARD");
		else
			font_render_string_right (&font_var5, 120, 27, "FIND HIM     ");

		sprintf ("%d", wpmano_timer);
		font_render_string (&font_var5, 2, 2, sprintf_buffer);
		font_render_string_right (&font_var5, 126, 2, sprintf_buffer);
}

void wpmano_running_deff (void)
{
	task_create_gid1 (GID_MANO, wpmano_score_task);
	for (;;)
	{
		dmd_alloc_low_clean ();
		bitmap_blit (mano1_bits,  1, 5);
		wpmano_rendertext ();
		dmd_show_low ();
		task_sleep (TIME_200MS);

		dmd_alloc_low_clean ();
		bitmap_blit (mano2_bits,  1, 5);
		wpmano_rendertext ();
		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}

void wpmano_total_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "MAN SAVED");
	sprintf_score (wpmano_score);
	font_render_string_center (&font_mono5, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (2);
	deff_exit ();
}

struct timed_mode_ops wpmano_mode = {
	DEFAULT_MODE,
	.init = wpmano_mode_init,
	.exit = wpmano_mode_exit,
	.music = MUS_MANOVERB_1,
	.deff_running = DEFF_WPMANO_RUNNING,
	.gid = GID_MANO_MODE,
	.prio = PRI_GAME_MODE3,
	.init_timer = WPMANO_MODE_TIME,
	.timer = &wpmano_timer,
	.grace_timer = 0,
	.pause = system_timer_pause,
};


void wpmano_shotmade (U8 shot)
{
	if (shot == wpmano_randomhz)   //correct shot made
	{
		task_kill_gid (GID_MANO);
		wpmano_gothim = TRUE;
		timed_mode_end (&wpmano_mode);
		score_long (wpmano_score);
		deff_start (DEFF_WPMANO_TOTAL);
	}
	else  //shot not made
	{
		if (flag_test (FLAG_BFCLIGHT))  //flashlight found
		{
			if (shot < wpmano_randomhz)
				speech_start (SND_GRABONTOHIM, SL_3S);
			else
				speech_start (SND_GETHOLDOFHIM, SL_3S);
		}
		else  //dark mode
		{
			if (shot < wpmano_randomhz)
				speech_start (SND_RIGHTRIGHT, SL_3S);
			else
				speech_start (SND_LEFTLEFT, SL_3S);
		}
	}
}



void wpman_start (void)
{
	raftmode_off ();

	speech_start (SND_MANOVERB, SL_3S);

	score_copy (wpmano_score, score_table[SC_20M]);
	wpmano_gothim = FALSE;

	lamp_tristate_flash (LM_BD_MAN_OVERBD);
	
	if (flag_test (FLAG_BFCLIGHT))
		wpmano_randomhz = random_scaled(6) +1;
	else
		wpmano_randomhz = random_scaled(4) + 1;

	if (wpmano_randomhz < 4)
		bigfhead_go_front_ccw ();
	else
		bigfhead_go_front_cw ();

	deff_start_sync (DEFF_WPMANO_INTRO);

	timed_mode_begin (&wpmano_mode);
}

//void wpman_stop (void)
//{
//	timed_mode_end (&wpmano_mode);
//}



CALLSET_ENTRY (wpmano, left_ramp_made)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (2);
	}
}

//ALLSET_ENTRY (wpmano, dev_lock_enter)
/*{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (3);
	}
}
*/

CALLSET_ENTRY (wpmano, sw_disas_drop_main)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (4);
	}
}

CALLSET_ENTRY (wpmano, sw_rapids_main_ramp)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (6);
	}
}

CALLSET_ENTRY (wpmano, sw_canyon_main)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (7);
	}
}

CALLSET_ENTRY (wpmano, left_loop_made)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (1);
	}
}

CALLSET_ENTRY (wpmano, right_loop_made)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (5);
	}
}

CALLSET_ENTRY (wpmano, display_update)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		deff_start_bg (DEFF_WPMANO_RUNNING, 0);
	}
}

CALLSET_ENTRY (wpmano, music_refresh)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		music_request (MUS_MANOVERB_1, PRI_GAME_MODE1 +3);
	}
}

CALLSET_ENTRY (wpmano, end_ball, tilt)
{
	if (timed_mode_running_p (&wpmano_mode))
		timed_mode_end (&wpmano_mode);
}

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
WP mode Man Overboard
Timed mode - 30 seconds - Countdown timer for score
Shoot 1 random hazard

Change with original game : go dark unless you've found the flashlight
*/
#include <freewpc.h>
#include <timedmode.h>
#include <bigfhead.h>
#include "wpmanoverb.h"


U8 wpmano_timer;
U8 wpmano_randomhz;

bool wpmano_gothim;

score_t wpmano_score;
score_t wpmano_scoremin;


void wpmano_mode_init (void)
{
	score_zero (wpmano_score);
	score_add (wpmano_score, score_table[SC_20M]);
	score_zero (wpmano_scoremin);
	score_add (wpmano_scoremin, score_table[SC_1M]);

	wpmano_gothim = FALSE;

	global_flag_on (GLOBAL_FLAG_WPMANO_RUNNING);

	lamps_out ();
	lamp_tristate_flash (LM_BD_MAN_OVERBD);


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
	global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
}

void wpmano_mode_exit (void)
{
	global_flag_off (GLOBAL_FLAG_WPMANO_RUNNING);
	global_flag_off (GLOBAL_FLAG_PF_LAMPS_OFF);
	lamp_tristate_off (LM_BD_MAN_OVERBD);
	lamplist_apply (LAMPLIST_HAZARDS, lamp_off);
	deff_stop (DEFF_WPMANO_RUNNING);

	global_flag_on (GLOBAL_FLAG_RAFTMODE);

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

		if (score_compare (wpmano_score, wpmano_scoremin) < 0)
		{
			score_zero (wpmano_score);
			score_add (wpmano_score, score_table[SC_1M]);
		}
		else
			score_sub (wpmano_score, score_table[SC_20K]);

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
	.init_timer = 20,
	.timer = &wpmano_timer,
	.grace_timer = 1,
	.pause = system_timer_pause,
};


void wpmano_shotmade (U8 shot)
{
	if (shot == wpmano_randomhz)
	{
		wpmano_gothim = TRUE;
		timed_mode_end (&wpmano_mode);
		score_long (wpmano_score);
		deff_start (DEFF_WPMANO_TOTAL);
	}
	else
	{
		if (flag_test (FLAG_BFCLIGHT))
		{
			if (shot < wpmano_randomhz)
				speech_start (SND_GRABONTOHIM, SL_3S);
			else
				speech_start (SND_GETHOLDOFHIM, SL_3S);
		}
		else
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
	global_flag_off (GLOBAL_FLAG_RAFTMODE);

	speech_start (SND_MANOVERB, SL_3S);

	if (flag_test (FLAG_BFCLIGHT))
		wpmano_randomhz = random_scaled(6) +1;
	else
		wpmano_randomhz = random_scaled(4) + 1;

	if (wpmano_randomhz < 4)
		bigfhead_go_ccw_front ();
	else
		bigfhead_go_cw_front ();

	timed_mode_begin (&wpmano_mode);
}

void wpman_stop (void)
{
	timed_mode_end (&wpmano_mode);
}



CALLSET_ENTRY (wpmano, left_ramp_made)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (2);
	}
}

CALLSET_ENTRY (wpmano, dev_lock_enter)
{
	if (timed_mode_running_p (&wpmano_mode))
	{
		wpmano_shotmade (3);
	}
}

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

CALLSET_ENTRY (wpmano, end_ball)
{
	if (timed_mode_running_p (&wpmano_mode))
		timed_mode_end (&wpmano_mode);
}

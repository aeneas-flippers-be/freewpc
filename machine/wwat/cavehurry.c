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
Cave hurryup
Timed mode - 30 seconds - Countdown timer for score  - was 20 seconds before
Shoot cave in 30 seconds after hitting both bigfoot targets for extra score
*/

#include <freewpc.h>

#define CAVHRY_MODE_TIME 30

U8 cave_timer;

score_t cave_score;


void cave_stop (void)
{
	task_kill_gid (GID_CAVEH);
	task_kill_gid (GID_CAVETIMER);
	global_flag_off (GLOBAL_FLAG_CAVEHRY_RUNNING);
}

void cave_timer_task (void)
{
	for (cave_timer = CAVHRY_MODE_TIME; cave_timer > 0; cave_timer--)
	{
		task_sleep_sec (1);
	}
	cave_stop ();
	task_exit ();
}

void cave_score_task (void)
{
	task_sleep_sec (2);
	while (score_compare (cave_score, score_table[SC_250K]) > 0)
	{
		score_sub (cave_score, score_table[SC_25K]);
		task_sleep (TIME_400MS);  //was 200ms
	}
	score_copy (cave_score, score_table[SC_250K]);
	task_exit ();
}



void cave_scored_deff (void)
{
		dmd_alloc_low_clean ();
		font_render_string_center (&font_var5, 64, 5, "CAVE HURRY UP");
		sprintf_score (cave_score);
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		dmd_show_low ();
		task_sleep_sec (1);
		deff_exit ();
}

void cave_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();
		font_render_string_center (&font_var5, 64, 5, "CAVE HURRY UP");
		sprintf_score (cave_score);
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);

		sprintf ("%d", cave_timer);
		font_render_string (&font_var5, 2, 2, sprintf_buffer);
		font_render_string_right (&font_var5, 126, 2, sprintf_buffer);
		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}


void cave_start (void)
{
	score_copy (cave_score, score_table[SC_1M]);
	global_flag_on (GLOBAL_FLAG_CAVEHRY_RUNNING);
	task_create_gid1 (GID_CAVETIMER, cave_timer_task);
	task_create_gid1 (GID_CAVEH, cave_score_task);
}

CALLSET_ENTRY (cavehry, sw_canyon_main)
{
	if (global_flag_test (GLOBAL_FLAG_CAVEHRY_RUNNING))
	{
		task_kill_gid (GID_CAVEH);
		sound_start (ST_SAMPLE, SND_OK_7, SL_4S, PRI_GAME_QUICK3);
		score_long (cave_score);
		deff_start (DEFF_CAVE_SCORED);
		cave_stop ();   //turn off global flag
	}
}

CALLSET_ENTRY (cavehry, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_CAVEHRY_RUNNING))
	{
		deff_start_bg (DEFF_CAVE_RUNNING, 0);
	}
}

CALLSET_ENTRY (cavehry, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_CAVEHRY_RUNNING))
	{
		music_request (MUS_HURRY_MODE9, PRI_GAME_MODE3);
	}
}

CALLSET_ENTRY (cavehry, end_ball, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_CAVEHRY_RUNNING))
		cave_stop ();
}

CALLSET_ENTRY (cavehry, start_ball)
{
	global_flag_off (GLOBAL_FLAG_CAVEHRY_RUNNING);
}

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
 * Boulderbash mode
 * 30 seconds jets score 50k x times mode played

 
 */

#include <freewpc.h>

#define BASH_MODE_TIME 30


U8 bash_timer;
__local__ U8 bash_counter;

U8 bash_jethits;
score_t bash_score;

void bash_stop (void)
{
	global_flag_off (GLOBAL_FLAG_BBASH_RUNNING);
	deff_stop (DEFF_BASH_RUNNING);
	task_kill_gid (GID_BASHTIMER);

	if (bash_jethits > 0)
	{
		score_mul (bash_score, bash_jethits);
		score_long (bash_score);
		deff_start (DEFF_BASH_END);
	}
}

void bash_mode_init (void)
{
	speech_start (SND_ITSABOULDERBASH, SL_4S);
	bounded_increment (bash_counter, 255);
	bash_jethits = 0;
	score_zero (bash_score);

	score_add (bash_score, score_table[SC_50K]);
	score_mul (bash_score, bash_counter);
//	score_add (bash_score, score_table[SC_250K]);
}

void bash_end_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 6, "BASH TOTAL");
	sprintf_score (bash_score);
	font_render_string_center (&font_fixed10, 64, 24, sprintf_buffer);
	dmd_show_low ();	
	task_sleep_sec (1);
	deff_exit ();
}

void bash_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();

		font_render_string_center (&font_fixed6, 64, 5, "BOULDER BASH");
		font_render_string_center (&font_fixed6, 64, 16, "HIT JETS");
		sprintf ("%d", bash_timer);
		font_render_string (&font_var5, 2, 2, sprintf_buffer);
		font_render_string_right (&font_var5, 126, 2, sprintf_buffer);

		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}

void bash_timer_task (void)
{
	for (bash_timer = BASH_MODE_TIME; bash_timer > 0; bash_timer--)
	{
		task_sleep_sec (1);
	}
	bash_stop ();
	task_exit ();
}


void bash_start (void)
{
	global_flag_on (GLOBAL_FLAG_BBASH_RUNNING);
	task_create_gid1 (GID_BASHTIMER, bash_timer_task);
	global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);	//let ball kickout from mine
}


CALLSET_ENTRY (bash, sw_jet)
{
	if (global_flag_test (GLOBAL_FLAG_BBASH_RUNNING))
	{
		bounded_increment (bash_jethits, 255);
	}
}

CALLSET_ENTRY (bash, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_BBASH_RUNNING))
		bash_stop ();
}

CALLSET_ENTRY (bash, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_BBASH_RUNNING))
	{
		music_request (MUS_HURRYMODE2, PRI_GAME_MODE3);
	}
}

CALLSET_ENTRY (bash, end_ball, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_BBASH_RUNNING))
		bash_stop ();
}

CALLSET_ENTRY (bash, start_player)
{
	bash_counter = 0;
}

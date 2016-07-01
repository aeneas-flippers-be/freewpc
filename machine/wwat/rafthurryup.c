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
Raft hurryup
when increasing a raft start a hurryup bonus on river letters
*/

#include <freewpc.h>
#include <timedmode.h>


U8 hurry_timer;
__local__ U8 hurry_counter;
score_t hurry_score;



void hurry_task (void)
{
	task_sleep_sec (2);
	lamp_tristate_off (LM_RIVER_R1);
	task_sleep_sec (2);
	lamp_tristate_off (LM_RIVER_I);
	task_sleep_sec (2);
	lamp_tristate_off (LM_RIVER_V);
	task_sleep_sec (2);
	lamp_tristate_off (LM_RIVER_E);
	task_sleep_sec (2);
	task_exit ();
}


void hurry_mode_init (void)
{
	score_zero (hurry_score);
	score_add (hurry_score, score_table[SC_1M]);
	score_mul (hurry_score, hurry_counter + 1);

	global_flag_on (GLOBAL_FLAG_HURRY_RUNNING);
	lamp_tristate_on (LM_RIVER_R1);
	lamp_tristate_on (LM_RIVER_I);
	lamp_tristate_on (LM_RIVER_V);
	lamp_tristate_on (LM_RIVER_E);
	lamp_tristate_on (LM_RIVER_R2);
	task_create_gid1 (GID_HURRY, hurry_task);
}

void hurry_mode_exit (void)
{
	task_kill_gid (GID_HURRY);
	lamp_tristate_off (LM_RIVER_R1);
	lamp_tristate_off (LM_RIVER_I);
	lamp_tristate_off (LM_RIVER_V);
	lamp_tristate_off (LM_RIVER_E);
	lamp_tristate_off (LM_RIVER_R2);
	global_flag_off (GLOBAL_FLAG_HURRY_RUNNING);
}

void hurry_scored_deff (void)
{
	dmd_alloc_low_clean ();
	sprintf ("HURRY UP %d", hurry_counter);
	font_render_string_center (&font_fixed6, 64, 10, sprintf_buffer);
	sprintf_score (hurry_score);
	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (2);
	deff_exit ();

}


void hurry_running_deff (void)
{
	score_t hurry_scoresub;
	score_t hurry_scoremin;

	score_zero (hurry_scoremin);
	score_add (hurry_scoremin, score_table[SC_250K]);

	score_zero (hurry_scoresub);
	score_add (hurry_scoresub, score_table[SC_20K]);
	score_mul (hurry_scoresub, hurry_counter + 1);


	for (;;)
	{
		dmd_alloc_low_clean ();

		font_render_string_center (&font_var5, 80, 5, "RIVER HURRY UP");
		sprintf_score (hurry_score);
		font_render_string_center (&font_fixed6, 80, 16, sprintf_buffer);
		sprintf ("%d", hurry_timer);
		font_render_string (&font_var5, 2, 2, sprintf_buffer);
		font_render_string_right (&font_var5, 126, 2, sprintf_buffer);

		if (score_compare (hurry_score, hurry_scoremin) < 0)
		{
			score_zero (hurry_score);
			score_add (hurry_score, score_table[SC_250K]);
		}
		else
			score_sub (hurry_score, hurry_scoresub);

		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}


struct timed_mode_ops hurry_mode = {
	DEFAULT_MODE,
	.init = hurry_mode_init,
	.exit = hurry_mode_exit,
//	.music = MUS_MANOVERB_1,
	.deff_running = DEFF_HURRY_RUNNING,
	.gid = GID_HURRY_MODE,
	.prio = PRI_GAME_MODE4,
	.init_timer = 10,
	.timer = &hurry_timer,
	.grace_timer = 0,
	.pause = system_timer_pause,
};

void hurry_scored (void)
{
	task_kill_gid (GID_HURRY);
	score_long (hurry_score);
	bounded_increment (hurry_counter, 255);
	deff_start (DEFF_HURRY_SCORED);
	sound_send(SND_WWYAHOO5);
	timed_mode_end (&hurry_mode);
}

void hurry_start (void)
{
	timed_mode_begin (&hurry_mode);
}

void hurry_stop (void)
{
	if (timed_mode_running_p (&hurry_mode))
		timed_mode_end (&hurry_mode);
}





CALLSET_ENTRY (hurry, sw_river_r1)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) && lamp_test (LM_RIVER_R1))
	{
		hurry_scored ();
	}
}

CALLSET_ENTRY (hurry, sw_river_i)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) && lamp_test (LM_RIVER_I))
	{
		hurry_scored ();
	}
}

CALLSET_ENTRY (hurry, sw_river_v)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) && lamp_test (LM_RIVER_V))
	{
		hurry_scored ();
	}
}

CALLSET_ENTRY (hurry, sw_river_e)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) && lamp_test (LM_RIVER_E))
	{
		hurry_scored ();
	}
}

CALLSET_ENTRY (hurry, sw_river_r2)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) && lamp_test (LM_RIVER_R2))
	{
		hurry_scored ();
	}
}







CALLSET_ENTRY (hurry, display_update)
{
	if (timed_mode_running_p (&hurry_mode))
	{
		deff_start_bg (DEFF_HURRY_RUNNING, 0);
	}
}

CALLSET_ENTRY (hurry, music_refresh)
{
	if (timed_mode_running_p (&hurry_mode))
	{
		music_request (MUS_HURMODE_RELOCK2, PRI_GAME_MODE1 +3);
	}
}

CALLSET_ENTRY (hurry, end_ball)
{
	if (timed_mode_running_p (&hurry_mode))
		timed_mode_end (&hurry_mode);
}

CALLSET_ENTRY (hurry, start_ball)
{
	global_flag_off (GLOBAL_FLAG_HURRY_RUNNING);
}

CALLSET_ENTRY (hurry, start_player)
{
	hurry_counter = 0;
}

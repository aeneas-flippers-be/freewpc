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
River hurryup
starts when increasing a raft - a hurryup bonus on river letters
start with all 5 lettes lit, score of 250k, increases to 1M while targets to shoot decrease one by one every 2 seconds
*/

#include <freewpc.h>

extern U8 hurry_counter; 

U8 hurry_timer;
score_t hurry_score;


void riverhurry_stop (void)
{
	task_kill_gid (GID_HURRY);
	task_kill_gid (GID_HURRYSC);
	lamp_off (LM_RIVER_R1);
	lamp_off (LM_RIVER_I);
	lamp_off (LM_RIVER_V);
	lamp_off (LM_RIVER_E);
	lamp_off (LM_RIVER_R2);
	global_flag_off (GLOBAL_FLAG_HURRY_RUNNING);
	deff_stop (DEFF_HURRY_RUNNING);
	river_lamps_on ();
}



void hurry_score_task (void)
{
	while (score_compare (hurry_score, score_table[SC_1M]) < 0)
	{
		score_add (hurry_score, score_table[SC_20K]);
		task_sleep (TIME_200MS);
	}
	score_copy (hurry_score, score_table[SC_1M]);
	task_exit ();
}

void hurry_task (void)
{
	hurry_timer = 10;
	task_sleep_sec (1);
	hurry_timer--;
	task_sleep_sec (1);
	lamp_off (LM_RIVER_R1);
	hurry_timer--;
	task_sleep_sec (1);
	hurry_timer--;
	task_sleep_sec (1);
	lamp_off (LM_RIVER_I);
	hurry_timer--;
	task_sleep_sec (1);
	hurry_timer--;
	task_sleep_sec (1);
	hurry_timer--;
	lamp_off (LM_RIVER_V);
	task_sleep_sec (1);
	hurry_timer--;
	task_sleep_sec (1);
	lamp_off (LM_RIVER_E);
	hurry_timer--;
	task_sleep_sec (1);
	hurry_timer--;
	task_sleep_sec (1);
	riverhurry_stop ();
	task_exit ();
}


void hurry_scored_deff (void)
{
	dmd_alloc_low_clean ();
	sprintf ("COMPLETED %d", hurry_counter);
	font_render_string_center (&font_fixed6, 64, 10, sprintf_buffer);
	sprintf_score (hurry_score);
	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}


void hurry_running_deff (void)
{
	task_create_gid (GID_HURRY, hurry_task);
	task_create_gid (GID_HURRYSC, hurry_score_task);

	for (;;)
	{
		dmd_alloc_low_clean ();

		if (lamp_test (LM_RIVER_R1)) font_render_string (&font_var5, 6, 2, "R");
		if (lamp_test (LM_RIVER_I)) font_render_string (&font_var5, 6, 8, "I");
		if (lamp_test (LM_RIVER_V)) font_render_string (&font_var5, 6, 14, "V");
		if (lamp_test (LM_RIVER_E)) font_render_string (&font_var5, 6, 20, "E");
		if (lamp_test (LM_RIVER_R2)) font_render_string (&font_var5, 6, 26, "R");

		font_render_string_center (&font_fixed6, 64, 5, "RIVER HURRY UP");
		sprintf_score (hurry_score);
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		sprintf ("%d", hurry_timer);
		font_render_string (&font_var5, 2, 2, sprintf_buffer);
		font_render_string_right (&font_var5, 126, 2, sprintf_buffer);

		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}



void hurry_scored (void)
{
	task_kill_gid (GID_HURRYSC);
	task_kill_gid (GID_HURRY);
	score_long (hurry_score);
	bounded_increment (hurry_counter, 255);
	deff_start (DEFF_HURRY_SCORED);
	sound_start (ST_SAMPLE, SND_WWYAHOO5, SL_4S, PRI_GAME_QUICK3);
	riverhurry_stop ();
}

void riverhurry_start (void)
{
	score_copy (hurry_score, score_table[SC_250K]);
	global_flag_on (GLOBAL_FLAG_HURRY_RUNNING);
	lamp_on (LM_RIVER_R1);
	lamp_on (LM_RIVER_I);
	lamp_on (LM_RIVER_V);
	lamp_on (LM_RIVER_E);
	lamp_on (LM_RIVER_R2);
//	deff_start_bg (DEFF_HURRY_RUNNING, 0);  is started in display_update call
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
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING))
		deff_start_bg (DEFF_HURRY_RUNNING, 0);
}

CALLSET_ENTRY (hurry, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING))
		music_request (MUS_HURMODE_RELOCK2, PRI_GAME_MODE4);
}

CALLSET_ENTRY (hurry, end_ball, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING))
		riverhurry_stop ();
}

CALLSET_ENTRY (hurry, start_ball)
{
	global_flag_off (GLOBAL_FLAG_HURRY_RUNNING);
}

CALLSET_ENTRY (hurry, start_player)
{
	hurry_counter = 0;
}

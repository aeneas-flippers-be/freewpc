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
2 ball mb - shoot hazards for 1M up to 5M each
started from wpoolmodes.c
stops when 1 ball drains
*/

#include <freewpc.h>

extern U8 lock_player_locks_lit;
extern U8 lock_balls_in_devlock;


U8 hz1count;
U8 hz2count;
U8 hz3count;
U8 hz4count;
U8 hz5count;
U8 hz6count;
U8 hz7count;

U8 wp5x_sound_index;

sound_code_t wp5x_sounds[11] = {SND_YIHA, SND_YOW, SND_SCREAM, SND_SCREAM2, SND_YOW2, 
SND_YIHA2, SND_YAW, SND_YIAW, SND_DOG2, SND_MAW, SND_YAW2};



void wp5xpf_stop (void)
{
	global_flag_off (GLOBAL_FLAG_WP5X_RUNNING);
	deff_stop (DEFF_WP5XPF_RUNNING2);

	raft_hz_lamps_tri_off ();
	lamp_tristate_off (LM_BD_5X_PF);

	raftmode_on ();
}


void wp5x_start (void)
{
	raftmode_off ();
	speech_start (SND_5TIMESFUN, SL_3S);

	hz1count = 0;
	hz2count = 0;
	hz3count = 0;
	hz4count = 0;
	hz5count = 0;
	hz6count = 0;
	hz7count = 0;
	wp5x_sound_index = 1;

	lamp_tristate_flash (LM_BD_5X_PF);

	qmball_flash_hz ();

	deff_start_sync (DEFF_WP5X_INTRO);

	global_flag_on (GLOBAL_FLAG_WP5X_RUNNING);


	//same code as WPCHALL.C
	/* new ball from lock unless none available */
	if (lock_balls_in_devlock > 0)
	{
		bounded_increment (lock_player_locks_lit, 3);
		lock_unlockball ();
		task_sleep (TIME_200MS);
	}
	else
	{
		global_flag_on (GLOBAL_FLAG_BALL_AT_PLUNGER);
		sol_request (SOL_BALL_RELEASE);

		while (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER))
		{
			task_sleep (TIME_100MS);
		}
	}
	global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	task_sleep_sec (1);
	set_ball_count (2);
}


void wp5x_jackpot (void)
{
	if (++wp5x_sound_index == 11)
		wp5x_sound_index = 0;
	sound_start (ST_SAMPLE, wp5x_sounds[wp5x_sound_index], SL_4S, PRI_GAME_QUICK3);
	deff_start (DEFF_JACKPOT);
}


CALLSET_ENTRY (wp5x, left_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		bounded_increment (hz1count, 5);
		score_multiple (SC_1M, hz1count);
		if (hz1count == 5)	lamp_tristate_on (LM_HZ_BOULDER_GARDEN);
	}
}

CALLSET_ENTRY (wp5x, left_ramp_made)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		bounded_increment (hz2count, 5);
		score_multiple (SC_1M, hz2count);
		if (hz2count == 5)	lamp_tristate_on (LM_HZ_SPINE_CHILLER);
	}
}

//ALLSET_ENTRY (wp5x, dev_lock_enter)
/*{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		bounded_increment (hz3count, 5);
		score_multiple (SC_1M, hz3count);
		if (hz3count == 5)	lamp_tristate_on (LM_HZ_NO_WAY_OUT);
	}
}
*/


CALLSET_ENTRY (wp5x, sw_disas_drop_main)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		bounded_increment (hz4count, 5);
		score_multiple (SC_1M, hz4count);
		if (hz4count == 5)	lamp_tristate_on (LM_HZ_DISDROP);
	}
}

CALLSET_ENTRY (wp5x, right_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		bounded_increment (hz5count, 5);
		score_multiple (SC_1M, hz5count);
		if (hz5count == 5)	lamp_tristate_on (LM_HZ_BOOM_BEND);
	}
}

CALLSET_ENTRY (wp5x, sw_rapids_main_ramp)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		bounded_increment (hz6count, 5);
		score_multiple (SC_1M, hz6count);
		if (hz6count == 5)	lamp_tristate_on (LM_HZ_INSANITY_FALLS);
	}
}

CALLSET_ENTRY (wp5x, sw_canyon_main)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		bounded_increment (hz7count, 5);
		score_multiple (SC_1M, hz7count);
		if (hz7count == 5)	lamp_tristate_on (LM_HZ_BIGFOOT_BLUFF);
	}
}




CALLSET_ENTRY (wp5x, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		music_request (MUS_FRENZY_2, PRI_GAME_MODE1 +2);
	}
}

CALLSET_ENTRY (wp5x, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		deff_start_bg (DEFF_WP5XPF_RUNNING2, 0);
	}
}

CALLSET_ENTRY (wp5x, end_ball, tilt, single_ball_play)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
		wp5xpf_stop ();
}



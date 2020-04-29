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
Quick multiball
	- started at lost mine as 3rd entry
	- 2-ball mb in which every hazard scores 10k, until all hazards shot then x2 until 100k
	
*/

#include <freewpc.h>
#include <ballsave.h>


extern U8 lock_balls_in_devlock;
extern U8 lock_player_locks_lit;
extern U8 qmb_jp_mul;


void qmball_flash_hz (void)
{
	lamp_tristate_flash (LM_HZ_BOULDER_GARDEN);
	lamp_tristate_flash (LM_HZ_SPINE_CHILLER);
	lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
	lamp_tristate_flash (LM_HZ_DISDROP);
	lamp_tristate_flash (LM_HZ_BOOM_BEND);
	lamp_tristate_flash (LM_HZ_INSANITY_FALLS);
	lamp_tristate_flash (LM_HZ_BIGFOOT_BLUFF);
}


void qmball_jackpot (void)
{

	if (flag_test (FLAG_HZ1LIT) &&	flag_test (FLAG_HZ2LIT)
		&& flag_test (FLAG_HZ3LIT) && flag_test (FLAG_HZ4LIT)
		&& flag_test (FLAG_HZ5LIT) && flag_test (FLAG_HZ6LIT) && flag_test (FLAG_HZ7LIT))
	{
		if (qmb_jp_mul < 10)
		{
			qmb_jp_mul++;
			qmball_flash_hz ();
			raft_hz_reset ();
			deff_start (DEFF_QMB_UP);
		}
	}

	speech_start (SND_JP, SL_2S);
	score_multiple (SC_10K, qmb_jp_mul);
	deff_start (DEFF_JACKPOT);
}

void qmball_stop (void)
{
	global_flag_off (GLOBAL_FLAG_QMBALL_RUNNING);
	deff_stop (DEFF_QMB_RUNNING);

	raft_hz_lamps_tri_off ();

	leff_stop (LEFF_RAFTLOOP);

	raft_hz_reset ();
	raft_next2rafts ();

	raftmode_on ();
}

void qmball_start (void)
{
	raftmode_off ();

	qmb_jp_mul = 1;

	deff_start_sync (DEFF_QMB_INTRO);

	raft_hz_reset ();
	leff_start (LEFF_RAFTLOOP);
	qmball_flash_hz ();

	global_flag_on (GLOBAL_FLAG_QMBALL_RUNNING);

	ballsave_add_time (1);

	//changed as now started from lost mine
	if (device_recount (device_entry (DEVNO_TROUGH)) == 2)
	{
		global_flag_on (GLOBAL_FLAG_BALL_AT_PLUNGER);
		sol_request (SOL_BALL_RELEASE);

		while (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER))
		{
			task_sleep (TIME_100MS);
		}
//		task_sleep (TIME_500MS);
//		global_flag_off (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
		ballsave_add_time (1);
		global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	}
	else
	{
		bounded_increment (lock_player_locks_lit, 3);
		lock_unlockball ();
		task_sleep (TIME_500MS);
		ballsave_add_time (1);
		global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	}
	task_sleep_sec (1);
	set_ball_count (2);

//	device_unlock_ball (device_entry (DEVNO_LOCK));

}

CALLSET_ENTRY (qmball, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
		deff_start_bg (DEFF_QMB_RUNNING, 0);
}

CALLSET_ENTRY (qmball, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
		music_request (MUS_MULTIBALL_2, PRI_GAME_MODE1 + 5);
}


CALLSET_ENTRY (qmball, left_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
	{
		flag_on (FLAG_HZ1LIT);
		lamp_tristate_on (LM_HZ_BOULDER_GARDEN);
		qmball_jackpot ();
	}
}

CALLSET_ENTRY (qmball, left_ramp_made)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
	{
		flag_on (FLAG_HZ2LIT);
		lamp_tristate_on (LM_HZ_SPINE_CHILLER);
		qmball_jackpot ();
	}
}

//ALLSET_ENTRY (qmball, dev_lock_enter)
/*{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
	{
		flag_on (FLAG_HZ3LIT);
		lamp_tristate_on (LM_HZ_NO_WAY_OUT);
		qmball_jackpot ();
	}
}
*/

CALLSET_ENTRY (qmball, sw_disas_drop_main)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
	{
		flag_on (FLAG_HZ4LIT);
		lamp_tristate_on (LM_HZ_DISDROP);
		qmball_jackpot ();
	}
}

CALLSET_ENTRY (qmball, right_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
	{
		flag_on (FLAG_HZ5LIT);
		lamp_tristate_on (LM_HZ_BOOM_BEND);
		qmball_jackpot ();
	}
}

CALLSET_ENTRY (qmball, sw_rapids_main_ramp)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
	{
		flag_on (FLAG_HZ6LIT);
		lamp_tristate_on (LM_HZ_INSANITY_FALLS);
		qmball_jackpot ();
	}
}

CALLSET_ENTRY (qmball, sw_canyon_main)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
	{
		flag_on (FLAG_HZ7LIT);
		lamp_tristate_on (LM_HZ_BIGFOOT_BLUFF);
		qmball_jackpot ();
	}
}

CALLSET_ENTRY (qmball, end_ball, tilt, single_ball_play)
{
	if (global_flag_test (GLOBAL_FLAG_QMBALL_RUNNING))
		qmball_stop ();
}



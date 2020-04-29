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
Rules:
- hit 2 green targets to light locks, then lock 3 balls (in lock.c now)
- start mb by kicking out balls onto mini pf
- spinechiller is jackpot
- extra : 2 bigfoot targets during mb will light 1 bigfoot jp

*/

#include <freewpc.h>


U8 mball_jackpot_level;

bool mball_addjp;
bool mball_bigfootjp;
bool mball_skillock;
bool mball_jpscored;
bool mball_restart_mode;



void mb_jackpot_collected_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "MB JACKPOT");

	printf_millions (mball_jackpot_level * 10);

	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
		printf_millions (20);
	else
		printf_millions (mball_jackpot_level * 10);

	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void mball_score_bfjackpot (void)
{
	mball_bigfootjp = FALSE;
	lamp_tristate_off (LM_UPF_BIGFOOT_JP);
	mball_jpscored = TRUE;
	score (SC_10M);
	speech_start (SND_BF1, SL_3S);
	deff_start (DEFF_BIGFOOT_JACKPOT);
}

void mball_score_jackpot (void)
{
	mball_jpscored = TRUE;
	if (mball_addjp)
		bounded_increment (mball_jackpot_level, 3);

	leff_start (LEFF_FL_PF_RTOL);

	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
	{
		if (mball_jackpot_level == 3)
			speech_start (SND_WEIRD100MIL, SL_3S);
		else
			speech_start (SND_100MIL, SL_3S);

		score_multiple (SC_10M, 2);
	}	
	else
	{
		score_multiple (SC_10M, mball_jackpot_level);
		switch (mball_jackpot_level)
		{
			case 3:
				speech_start (SND_TRIPLE_JP, SL_2S);
				break;
			case 2:
				speech_start (SND_DOUBLE_JP, SL_2S);
				break;
			case 1:
				speech_start (SND_JP, SL_2S);
				break;
		}
	}
	deff_start (DEFF_MB_JACKPOT_COLLECTED);
}


void mball_stop (void)
{
	global_flag_off (GLOBAL_FLAG_MBALL_RUNNING);
	deff_stop (DEFF_MB_RUNNING);

	mball_addjp = FALSE;
	mball_bigfootjp = FALSE;
	mball_restart_mode = FALSE;

	leff_stop (LEFF_RAFTLOOP);
	deff_stop (DEFF_MB_RESTART);

	lamp_tristate_off (LM_UPF_MULTI_JP);
	lamp_tristate_off (LM_UPF_BIGFOOT_JP);

	raftmode_on ();
}

void mball_jptask (void)
{
	task_sleep_sec (2);
	mball_addjp = FALSE;
	if (mball_jackpot_level == 0)
		mball_jackpot_level = 1;
	task_exit ();
}

void mball_start (void)
{
//	raftmode_off ();
	leff_start (LEFF_FL_ALL_PF_LOOP);
	speech_start (SND_WWATER, SL_3S);
	deff_start_sync (DEFF_MB_INTRO);

	mball_jackpot_level = 0;
	mball_bigfootjp = FALSE;
	mball_addjp = TRUE;
	mball_jpscored = FALSE;
	mball_restart_mode = FALSE;

	bftgt_reset ();

	lamp_tristate_on (LM_UPF_MULTI_JP);
	lamp_tristate_off (LM_UPF_BIGFOOT_JP);

	lamp_tristate_flash (LM_2BANK_UP);
	lamp_tristate_flash (LM_2BANK_LOW);


	lock_lamps_off ();
//	lamp_tristate_off (LM_LOCK_1);
//	lamp_tristate_off (LM_LOCK_2);
//	lamp_tristate_off (LM_LOCK_3);
//	lamp_tristate_off (LM_LOCK_LEFT);
//	lamp_tristate_off (LM_LOCK_RIGHT);

	leff_start (LEFF_RAFTLOOP);

//	task_sleep_sec (1);

//	while (deff_get_active() == DEFF_MB_START) 
//	{
//		task_sleep (TIME_100MS);
//	}

	leff_stop (LEFF_FL_ALL_PF_LOOP);
	global_flag_on (GLOBAL_FLAG_MBALL_RUNNING);
	lock_unlockball ();
	task_sleep_sec (1);	
	lock_unlockball ();
	task_sleep_sec (1);	
	lock_unlockball ();
//	set_ball_count (3);

	//player has 3 seconds to shoot jackpot ramp, if he didn't succeed then don't increase jackpot anymore	task_create_gid1 (GID_MBJP, mball_jptask);
}

void mball_relock_task (void)
{
	task_sleep_sec (10);
	mball_restart_mode = FALSE;
	deff_stop (DEFF_MB_RESTART);
	leff_stop (LEFF_SKILLLOCK);
	mball_stop ();
	task_exit ();
}

void mball_relock (void)
{
	mball_restart_mode = TRUE;
	mball_jpscored = TRUE;	//only allow restart once
	leff_start (LEFF_SKILLLOCK);
	task_create_gid1 (GID_RELOCK, mball_relock_task);
}



CALLSET_ENTRY (mball, bigftgt_completed)
{
	if (global_flag_test (GLOBAL_FLAG_MBALL_RUNNING) && !mball_restart_mode)
	{
		mball_bigfootjp = TRUE;
		lamp_tristate_flash (LM_UPF_BIGFOOT_JP);
		speech_start (SND_HEADFORBIGFOOTBLUFF, SL_4S);
	}
}

CALLSET_ENTRY (mball, sw_rapids_main_ramp)
{
	if (global_flag_test (GLOBAL_FLAG_MBALL_RUNNING) && !mball_restart_mode)
	{
		mball_score_jackpot ();
	}
}

CALLSET_ENTRY (mball, sw_canyon_main)
{
	if (global_flag_test (GLOBAL_FLAG_MBALL_RUNNING) && !mball_restart_mode && mball_bigfootjp)
			mball_score_bfjackpot ();
}


//test for relock shot
//ALLSET_ENTRY (mball, dev_lock_enter)
/*
{
	if (global_flag_test (GLOBAL_FLAG_MBALL_RUNNING) && mball_restart_mode)
	{
		task_kill_gid (GID_RELOCK);
//		device_lock_ball (device_entry (DEVNO_LOCK));
		mball_restart_mode = FALSE;
		speech_start (SND_WWGREATSHOT, SL_3S);
		leff_stop (LEFF_SKILLLOCK);
		deff_start (DEFF_MB_RELOCKED);

		//release ball from plunger and wait until it's shot on the playfield
		global_flag_on (GLOBAL_FLAG_BALL_AT_PLUNGER);
		sol_request (SOL_BALL_RELEASE);

		while (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER))
		{
			task_sleep (TIME_100MS);
		}
		task_sleep (TIME_500MS); //wait until kicking ball out
	}
}
*/


CALLSET_ENTRY (mball, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_MBALL_RUNNING))
	{
		if (mball_restart_mode)
			deff_start_bg (DEFF_MB_RESTART, 0);
		else
			deff_start_bg (DEFF_MB_RUNNING, 0);
	}
}

CALLSET_ENTRY (mball, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_MBALL_RUNNING))
	{
		if (mball_restart_mode)
			music_request (MUS_HURMODE_RELOCK1, PRI_GAME_MODE1 + 5);
		else
			music_request (MUS_MULTIBALL, PRI_GAME_MODE1 + 5);
	}
}

CALLSET_ENTRY (mball, single_ball_play)
{
	if (global_flag_test (GLOBAL_FLAG_MBALL_RUNNING))
	{
		if (mball_jpscored)
		{
			mball_stop ();
		}
		else
		{
			mball_relock ();
		}
	}
}

CALLSET_ENTRY (mball, end_ball, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_MBALL_RUNNING))
	{
		mball_stop ();
	}
}



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

/* 2 ball mb frenzy similar to wpchall */

#include <freewpc.h>
//#include <ballsave.h>
//#include <bigfhead.h>


bool gold_hit;
U8 gold_hitcount;
U8 gold_sound_index;

score_t gold_score;
score_t gold_scorebegin;
extern U8 *current_score;
extern U8 lock_locks_lit;


sound_code_t gold_sounds[4] = {SND_PINGBASS1, SND_PINGBASS2, SND_PINGBASS3, SND_PINGBASS1};



void goldrush_lamps_task (void)
{
	lamplist_set_apply_delay (TIME_50MS);
	lamplist_apply (LAMPLIST_GOLDRUSH, lamp_off);
	lamp_on (LM_RIVER_R1);
	for (;;) {
		lamplist_rotate_next (LAMPLIST_GOLDRUSH, lamp_matrix);
		task_sleep (TIME_100MS);
		if (gold_hit)
		{
			gold_hit = FALSE;
			bounded_increment (gold_hitcount, 255);
			task_sleep (TIME_200MS);
		}
	}
//	leff_exit ();
	task_exit ();
}

void gold_stop (void)
{
	global_flag_off (GLOBAL_FLAG_GOLD_RUNNING);
//		global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	global_flag_off (GLOBAL_FLAG_PF_LAMPS_OFF);
	deff_stop (DEFF_GOLD_RUNNING);
	leff_stop (LEFF_GOLDRAFTS);
	task_kill_gid (GID_GOLDLAMPS);

	score_copy (current_score, gold_score);
	score_sub (gold_score, gold_scorebegin);

	deff_start (DEFF_GOLD_TOTAL);
	global_flag_on (GLOBAL_FLAG_RAFTMODE);
}

void gold_start (void)
{
	global_flag_off (GLOBAL_FLAG_RAFTMODE);
	global_flag_on (GLOBAL_FLAG_GOLD_RUNNING);
	speech_start (SND_ITSGOLDRUSH, SL_4S);
	lamps_out ();
	gold_hit = FALSE;
	gold_sound_index = 0;
	task_create_gid1 (GID_GOLDLAMPS, goldrush_lamps_task);
	leff_start (LEFF_GOLDRAFTS);

	score_copy (current_score, gold_scorebegin);

//	ballsave_disable ();

	/* new ball from lock unless none available */
	if (device_recount (device_entry (DEVNO_LOCK)) > 0)
	{
		bounded_increment (lock_locks_lit, 3);
		lock_unlockball ();
		task_sleep (TIME_200MS);
	}
	else
	{
		global_flag_on (GLOBAL_FLAG_BALL_AT_PLUNGER);
		device_unlock_ball (device_entry (DEVNO_TROUGH));
//			sol_request (SOL_BALL_RELEASE);
//			sol_request_async (SOL_BALL_RELEASE);

		while (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER))
		{
			task_sleep (TIME_100MS);
		}
//		global_flag_off (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
//		task_sleep_sec (1);
	}
	global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
}



/*  original
	// first release locked unless none available then on shooterlane
	if (lock_balls_in_lock > 0)
	{
		lock_unlockball ();
		task_sleep (TIME_100MS);
//			task_sleep (TIME_100MS);
	}
	else
	{	
		global_flag_on (GLOBAL_FLAG_BALL_AT_PLUNGER);
		sol_request (SOL_BALL_RELEASE);

//			while (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER))
//			{
//				task_sleep (TIME_100MS);
//			}
	}
//		global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
//		task_sleep_sec (1);
//		set_ball_count (2);
}
*/


void gold_tgthit (void)
{
		gold_hit = TRUE;
		sound_start (ST_SAMPLE, SND_PINGBASSSHORTLOOP, SL_4S, PRI_GAME_QUICK3);
		score (SC_1M);
}

CALLSET_ENTRY (gold, sw_3bank_top)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_3BANK_TOP))
	{
		flasher_pulse (FLASH_WPOOL_ENTER_FL);
		gold_tgthit ();
	}
}

CALLSET_ENTRY (gold, sw_3bank_center)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_3BANK_CENTER))
	{
		flasher_pulse (FLASH_WPOOL_ENTER_FL);
		gold_tgthit ();
	}
}

CALLSET_ENTRY (gold, sw_3bank_bottom)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_3BANK_BOTTOM))
	{
		flasher_pulse (FLASH_WPOOL_ENTER_FL);
		gold_tgthit ();
	}
}

CALLSET_ENTRY (gold, sw_river_r1)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_RIVER_R1))
	{
		flasher_pulse (FLASH_MINE_POPPER_FL);
		gold_tgthit ();
	}
}

CALLSET_ENTRY (gold, sw_river_r2)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_RIVER_R2))
	{
		flasher_pulse (FLASH_MINE_POPPER_FL);
		gold_tgthit ();
	}
}
CALLSET_ENTRY (gold, sw_river_i)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_RIVER_I))
	{
		flasher_pulse (FLASH_MINE_POPPER_FL);
		gold_tgthit ();
	}
}
CALLSET_ENTRY (gold, sw_river_v)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_RIVER_V))
	{
		flasher_pulse (FLASH_MINE_POPPER_FL);
		gold_tgthit ();
	}
}
CALLSET_ENTRY (gold, sw_river_e)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_RIVER_E))
	{
		flasher_pulse (FLASH_MINE_POPPER_FL);
		gold_tgthit ();
	}
}

CALLSET_ENTRY (gold, sw_2bank_up)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_2BANK_UP))
	{
		flasher_pulse (FLASH_WPOOL_ENTER_FL);
		gold_tgthit ();
	}
}

CALLSET_ENTRY (gold, sw_2bank_low)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING) && lamp_test (LM_2BANK_LOW))
	{
		flasher_pulse (FLASH_WPOOL_ENTER_FL);
		gold_tgthit ();
	}
}

CALLSET_ENTRY (gold, any_pf_switch)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING))
	{
		score (SC_25K);

		gold_sound_index++;
		if (gold_sound_index > 3)
			gold_sound_index = 0;
		sound_start (ST_SAMPLE, gold_sounds[gold_sound_index], SL_1S, PRI_GAME_QUICK3);
	}
}

CALLSET_ENTRY (gold, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING))
		deff_start_bg (DEFF_GOLD_RUNNING, 0);
}

CALLSET_ENTRY (gold, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING))
		music_request (MUS_MODE_FRENZY_1, PRI_GAME_MODE1 + 5);
}

CALLSET_ENTRY (gold, single_ball_play)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING))
	{
		gold_stop ();
	}
}

CALLSET_ENTRY (gold, start_ball)
{
	gold_hitcount = 0;
}

CALLSET_ENTRY (gold, end_ball)
{
	if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING))
	{
		gold_stop ();
	}
}


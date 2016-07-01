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
Whirlpool Challenge mode
Rule:
	- 2 ball mb, shoot wpool for jackpot increasing from 1 until 10 mill
	- hit 2 bf tgts to score a double jp
*/

#include <freewpc.h>
//#include <ballsave.h>


extern U8 lock_locks_lit;

U8 wpch_jackpots_made;
U8 wpch_6shots_count;
U8 wpch_6shots_made;
//score_t wpch_score;


void wpch_jackpot (void)
{
	bounded_increment (wpch_jackpots_made, 255);
	wpch_6shots_count++;

	if (global_flag_test (GLOBAL_FLAG_BIGFOOTLIT))
		score_multiple (SC_1M, wpch_jackpots_made *2);
	else
		score_multiple (SC_1M, wpch_jackpots_made);

	if (wpch_6shots_count > 5)
	{
		bounded_increment (wpch_6shots_made, 5);
		wpch_6shots_count = 0;
		score_multiple (SC_20M, wpch_6shots_made);
		deff_start (DEFF_WPCH_JACKPOT6);
	}
	else
		deff_start (DEFF_WPCH_JACKPOT);


	global_flag_off (GLOBAL_FLAG_BIGFOOTLIT);	

	speech_start (SND_BF1, SL_3S);
	leff_start (LEFF_FL_WPOOL);

	switch (wpch_6shots_count)
	{
		case 0:
			leff_stop (LEFF_WPOOLMODE6);
			leff_start (LEFF_WPOOLMODE);
			break;
		case 2:
			leff_stop (LEFF_WPOOLMODE);
			leff_start (LEFF_WPOOLMODE2);
			break;
		case 3:
			leff_stop (LEFF_WPOOLMODE2);
			leff_start (LEFF_WPOOLMODE3);
			break;
		case 5:
			leff_stop (LEFF_WPOOLMODE3);
			leff_start (LEFF_WPOOLMODE6);
			break;
	}
}


void wpch_stop (void)
{
	global_flag_off (GLOBAL_FLAG_BIGFOOTLIT);	
	global_flag_off (GLOBAL_FLAG_WPCH_RUNNING);
	leff_stop (LEFF_WPOOLMODE);
	leff_stop (LEFF_WPOOLMODE2);
	leff_stop (LEFF_WPOOLMODE3);
	leff_stop (LEFF_WPOOLMODE6);
//		global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	global_flag_off (GLOBAL_FLAG_PF_LAMPS_OFF);
	deff_stop (DEFF_WPCH_RUNNING);
	lamp_tristate_off (LM_LIGHT_WHIRLPOOL);
	lamp_tristate_off (LM_UPF_BIGFOOT_JP);
	lamp_tristate_off (LM_BD_WHIRLP_CHALL);
	global_flag_on (GLOBAL_FLAG_RAFTMODE);
}

void wpch_start (void)
{
	global_flag_off (GLOBAL_FLAG_RAFTMODE);
	global_flag_on (GLOBAL_FLAG_WPCH_RUNNING);
	global_flag_on (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	wpch_jackpots_made = 0;
	wpch_6shots_count = 0;
	wpch_6shots_made = 0;

	lamps_out ();

	deff_start (DEFF_WPCH_START);
	speech_start (SND_RIDEWPOOL, SL_3S);

	leff_start (LEFF_WPOOLMODE);


	task_sleep_sec (2);

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




CALLSET_ENTRY (wpch, wpool_enter)
{
	if (global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
	{
		wpch_jackpot ();
	}
}


CALLSET_ENTRY (wpch, lamp_update)
{
	if (global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
	{
		lamp_tristate_flash (LM_LIGHT_WHIRLPOOL);
		lamp_tristate_flash (LM_UPF_BIGFOOT_JP);
		lamp_tristate_flash (LM_BD_WHIRLP_CHALL);
	}
}

CALLSET_ENTRY (wpch, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
		deff_start_bg (DEFF_WPCH_RUNNING, 0);
}

CALLSET_ENTRY (wpch, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
		music_request (MUS_WPOOL_2, PRI_GAME_MODE1 + 5);
}

CALLSET_ENTRY (wpch, single_ball_play)
{
	if (global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
		wpch_stop ();
}

CALLSET_ENTRY (wpch, end_ball)
{
	if (global_flag_test (GLOBAL_FLAG_WPCH_RUNNING))
		wpch_stop ();
}



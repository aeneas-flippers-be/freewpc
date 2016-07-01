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


#include <freewpc.h>

/*  COUNTERS FOR BONUS  */
__local__ U8 shots_falls;
__local__ U8 shots_secretpass;

void lamps_out (void)
{
	global_flag_on (GLOBAL_FLAG_PF_LAMPS_OFF);
	
	lamplist_apply (LAMPLIST_HAZARDS, lamp_off);
	lamplist_apply (LAMPLIST_RAFTS, lamp_off);
	lamplist_apply (LAMPLIST_LOCKSGREEN, lamp_off);
	lamplist_apply (LAMPLIST_BOULDERMODES, lamp_off);
	lamp_tristate_off (LM_2BANK_UP);
	lamp_tristate_off (LM_2BANK_LOW);
	lamplist_apply (LAMPLIST_RIVER, lamp_off);
}


/* ball is shot from plunger onto the playfield, now let other ball eject from lostminepopper or lock */
CALLSET_ENTRY (waitplunge, sw_rapids_main_ramp, sw_rapids_enter, sw_canyon_entrance, sw_bigfoot_cave, sw_canyon_main, sw_right_inlane)
{
	if (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER))
	{
		global_flag_off (GLOBAL_FLAG_BALL_AT_PLUNGER);
		global_flag_off (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
		global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	}
}

/* wait if there's a ball in the shooter lane */
CALLSET_ENTRY (waitplunge, dev_lostmine_kick_attempt)
{
	if (!in_live_game)
		return;

	while (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER) || global_flag_test (GLOBAL_FLAG_HOLD_MINE_KICKOUT))
	{
		task_sleep (TIME_100MS);
	}

	leff_start (LEFF_LOSTMINE_KICK);
	if (!global_flag_test (GLOBAL_FLAG_MBALL_RUNNING))
	{
		sound_start (ST_SAMPLE, SND_WHISTLE, SL_3S, PRI_GAME_QUICK3);
	}
}

/*
 ALLSET_BOOL_ENTRY (waitplunge, dev_lostmine_kick_request)
{
	if (in_live_game && 
		(global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER) || global_flag_test (GLOBAL_FLAG_HOLD_MINE_KICKOUT))
		)
		return FALSE;
	return TRUE;
}
*/


/* wait if there's a ball in the shooter lane */
CALLSET_ENTRY (waitplunge, dev_lock_kick_attempt)
{
	if (!in_live_game)
		return;

	while (global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER) || global_flag_test (GLOBAL_FLAG_HOLD_LOCK_KICKOUT))
	{
		task_sleep (TIME_100MS);
	}

	leff_start (LEFF_LOCK_KICK);
	if (!global_flag_test (GLOBAL_FLAG_MBALL_RUNNING))
	{
		sound_start (ST_SAMPLE, SND_WHISTLE, SL_3S, PRI_GAME_QUICK3);
		task_sleep (TIME_100MS);
	}
}

/*ALLSET_BOOL_ENTRY (waitplunge, dev_lock_kick_request)
{
	if (in_live_game && 
		(global_flag_test (GLOBAL_FLAG_BALL_AT_PLUNGER) || global_flag_test (GLOBAL_FLAG_HOLD_LOCK_KICKOUT))
		)
		return FALSE;
	return TRUE;
}
*/


/* 
shoot left loop, score when it reaches right switch (so goes around) and vice versa 
secret passage stops these timers too
*/
CALLSET_ENTRY (simple, sw_secret_passage)
{
	score (SC_20K);

	free_timer_stop (TIM_LLOOP);
	free_timer_stop (TIM_RLOOP);

	bounded_increment (shots_secretpass, 255);

	callset_invoke (secret_passage_made);
}

CALLSET_ENTRY (simple, sw_left_loop)
{
	if (free_timer_test (TIM_RLOOP))
	{
		free_timer_stop (TIM_RLOOP);
		callset_invoke (right_loop_made);
	}
	else
	{
		free_timer_start (TIM_LLOOP, TIME_3S);
	}
}

CALLSET_ENTRY (simple, sw_right_loop)
{
	if 	(free_timer_test (TIM_LLOOP))
	{
		free_timer_stop (TIM_LLOOP);
		callset_invoke (left_loop_made);
	}
	else
	{
		free_timer_start (TIM_RLOOP, TIME_3S);
	}
}


/*  detect when we go up the ramp or down  */
CALLSET_ENTRY (simple, sw_left_ramp_enter)
{
	if (free_timer_test (TIM_LRAMPDOWN))
	{
		free_timer_stop (TIM_LRAMPDOWN);
		callset_invoke (left_ramp_down);
//		deff_start (DEFF_TESTRAMPDOWN);
	}
	else
	{
		free_timer_start (TIM_LRAMP, TIME_2S);
	}
}

CALLSET_ENTRY (simple, sw_left_ramp_main)
{
	if (free_timer_test (TIM_LRAMP))
	{
		free_timer_stop (TIM_LRAMP);
		callset_invoke (left_ramp_made);
//		deff_start (DEFF_TESTRAMPUP);
	}
	else
	{
		free_timer_start (TIM_LRAMPDOWN, TIME_2S);
	}
}

CALLSET_ENTRY (simple, sw_right_inlane)
{
	if (multi_ball_play ())
		return;

	free_timer_stop (TIM_LRAMPDOWN);
}



CALLSET_ENTRY (simple, left_ramp_down)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE))
		speech_start (SND_SCREAM6, SL_2S);
}

CALLSET_ENTRY (simple, sw_rapids_main_ramp)
{
	bounded_increment (shots_falls, 255);
	speech_start (SND_SCREAM1, SL_2S);
	leff_start (LEFF_FL_ULPF);
}



CALLSET_ENTRY (simple, start_player)
{
	shots_falls = 0;
	shots_secretpass = 0;
	global_flag_on (GLOBAL_FLAG_RAFTMODE);
}

CALLSET_ENTRY (simple, any_pf_switch)
{
	score (SC_10);
}

CALLSET_ENTRY (simple, start_without_credits)
{
	if (!timer_find_gid (GID_START_NO_CREDITS_DEBOUNCE))
	{
		timer_restart_free (GID_START_NO_CREDITS_DEBOUNCE, TIME_5S);
		sound_start (ST_SAMPLE, SND_DOG, SL_3S, PRI_GAME_QUICK3);
	}
}

CALLSET_ENTRY (simple, tilt)
{
	sound_start (ST_SAMPLE, SND_BF_LAUGH, SL_4S, PRI_GAME_QUICK3);
}

CALLSET_ENTRY (simple, tilt_warning)
{
	sound_start (ST_SAMPLE, SND_ALARM, SL_4S, PRI_GAME_QUICK3);
}



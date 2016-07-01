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
Skill shot
	- shoot insanity falls like original
	- shoot bigfoot  (scores same now as insanity)  TODO ? to collect 1 item
	- roll down without other switch and lock 1 ball immediately by shooting lock from right inlane

lock.c has rest of lock skillshot stuff

*/

#include <freewpc.h>
#include <bigfhead.h>

__local__ U8 skill_made;
extern U8 ball_up;


void skill_enable (void)
{
	global_flag_on (GLOBAL_FLAG_SKILL_ENABLED);
	
	if (ball_up == 1)
		deff_start (DEFF_SKILL_RUNNING);

	leff_start (LEFF_SKILLLOCK);

	bigfhead_go_cw_front ();
}

void skill_disable (void)
{
	global_flag_off (GLOBAL_FLAG_SKILL_ENABLED);
	lamp_flash_off (LM_UPF_MULTI_JP);
	lamp_flash_off (LM_UPF_BIGFOOT_JP);
	leff_stop (LEFF_SKILLLOCK);
	deff_stop (DEFF_SKILL_RUNNING);

	bigfhead_go_ccw_back ();
}

void skill_award (void)
{
	free_timer_stop (TIM_SKILL);
	skill_made++;

	speech_start (SND_FEMALE_YEAH2, SL_2S);  //4 not good
	score_multiple (SC_1M, skill_made);

	deff_start (DEFF_SKILL);

	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
		skill_disable ();
}


CALLSET_ENTRY (skill, sw_right_inlane, sw_rapids_enter, sw_canyon_entrance)
{
	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
	{
		free_timer_restart (TIM_SKILL, TIME_3S);
		task_sleep_sec (2);
		skill_disable ();
	}
}

CALLSET_ENTRY (skill, sw_rapids_main_ramp, sw_whirlpool_exit, sw_canyon_main, sw_bigfoot_cave)
{
	if (free_timer_test (TIM_SKILL))
	{
		skill_award ();
	}
}

CALLSET_ENTRY (skill, lamp_update)
{
	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
	{
		lamp_flash_on (LM_UPF_MULTI_JP);
		lamp_flash_on (LM_UPF_BIGFOOT_JP);
	}
}

CALLSET_ENTRY (skill, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
	{
		music_request (MUS_PLUNGER, PRI_GAME_MODE1 +3);
	}
}

CALLSET_ENTRY (skill, start_player)
{
	skill_made = 0;
	skill_enable();
}

CALLSET_ENTRY (skill, serve_ball)
{
	if (multi_ball_play () || !global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	skill_enable();
}

CALLSET_ENTRY (skill, end_ball, stop_game, sw_left_ramp_enter, tilt)
{
	skill_disable();
}

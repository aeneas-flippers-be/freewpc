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
 
/*  TODO NOT FINISHED STILL BUSY ADDING SKILLSHOT LAMP LOOP */

/*
Skill shot

	- shoot insanity falls like original
	- shoot bigfoot  (scores same now as insanity)  TODO ? to collect 1 item

//REMOVED	- roll down without other switch and lock 1 ball immediately by shooting lock from right inlane
lock.c has rest of lock skillshot stuff for quickmb start

*/

#include <freewpc.h>
#include <bigfhead.h>

//extern raft_raftlamps_off (void);

extern U8 skill_ramp_made;  //extern in deffs3.c   holds nr of raft skillshot made
extern U8 skill_bigf_made;  //extern in deffs3.c
extern U8 ball_up;

extern U8 skill_raftnr;  //skill raft made

extern U8 skill_count;  //counter for looping skillshot lamps and score



//loop first 3 raft lamps
void skill_lamp_task (void)
{
	
	for (;;)
	{
		if (skill_raftnr == 0) 
			skill_count = 1;	//always start on first raft or raft last made
		else
			skill_count = skill_raftnr;
		
		raft_raftlamps_off ();
		raft_raftlamps_on (skill_count);		
		task_sleep (TIME_500MS);
		bounded_increment(skill_count, 9);
		raft_raftlamps_off ();
		raft_raftlamps_on (skill_count);		
		task_sleep (TIME_500MS);
		bounded_increment(skill_count, 9);
		raft_raftlamps_off ();
		raft_raftlamps_on (skill_count);		
		task_sleep (TIME_500MS);
	}

	task_exit ();
}


void skill_enable (void)
{
	global_flag_on (GLOBAL_FLAG_SKILL_ENABLED);

	lamp_tristate_flash (LM_UPF_MULTI_JP);
	lamp_tristate_flash (LM_UPF_BIGFOOT_JP);
	
	if (ball_up == 1)
		deff_start (DEFF_SKILL_RUNNING);

	//skillshot raft lamps loop
	lamplist_apply (LAMPLIST_RAFTS, lamp_off);	//disable all lamps
	task_create_gid1 (GID_SKILL, skill_lamp_task);  //start raft lamp loop
	
//	lock_lamps_off ();
//	leff_start (LEFF_SKILLLOCK);

	bigfhead_go_front_cw ();
}

void skill_disable (void)
{
	global_flag_off (GLOBAL_FLAG_SKILL_ENABLED);
	lamp_tristate_off (LM_UPF_MULTI_JP);
	lamp_tristate_off (LM_UPF_BIGFOOT_JP);
//	leff_stop (LEFF_SKILLLOCK);
	deff_stop (DEFF_SKILL_RUNNING);

//	lock_lamp_update ();
	task_kill_gid (GID_SKILL);
	bigfhead_go_back_ccw ();
	raft_raftlamps_off ();
	callset_invoke (raft_lamps_on);
}

void skill_ramp_award (void)
{
	skill_raftnr = skill_count;	//remember for next ball to continue from here

	leff_start (LEFF_FL_MAINRAMP);
	free_timer_stop (TIM_SKILL);

	speech_start (SND_FEMALE_YEAH2, SL_2S);  //4 not good
//	score_multiple (SC_1M, skill_ramp_made);

	if (skill_count == 9)
		score_multiple (SC_1M, 20);
	else
		score_multiple (SC_1M, skill_count * 2);
	
	skill_ramp_made++;
	deff_start (DEFF_SKILL_RAMP);

	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
		skill_disable ();
}

void skill_bigf_award (void)
{
	leff_start (LEFF_FL_BFDIV);
	free_timer_stop (TIM_SKILL);

	speech_start (SND_FEMALE_YEAH2, SL_2S);
	score_multiple (SC_1M, skill_bigf_made);
	skill_bigf_made++;

	deff_start (DEFF_SKILL_BIGF);

	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
		skill_disable ();
}


/*--ALLSET_ENTRY (skill, sw_right_inlane, sw_rapids_enter, sw_canyon_entrance) */
CALLSET_ENTRY (skill, sw_rapids_enter, sw_canyon_entrance)
{
	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
	{
		//2 seconds to make the shot
		free_timer_restart (TIM_SKILL, TIME_2S);
		task_sleep_sec (2);
		skill_disable ();
	}
}

//rapids ramp made, check if were in time
CALLSET_ENTRY (skill, sw_rapids_main_ramp)
{
	if (free_timer_test (TIM_SKILL))
	{
		skill_ramp_award ();
	}
}

//canyon shot made
CALLSET_ENTRY (skill, sw_canyon_main)
{
	if (free_timer_test (TIM_SKILL))
	{
		global_flag_on (GLOBAL_FLAG_BIGFOOTLIT);
		skill_bigf_award ();
	}
}


CALLSET_ENTRY (skill, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
	{
		music_request (MUS_PLUNGER, PRI_GAME_MODE1 +3);
	}
}

//reset counters for each player
CALLSET_ENTRY (skill, start_player)
{
	skill_ramp_made = 1;
	skill_bigf_made = 1;
	skill_raftnr = 0;
}

//enable skill
CALLSET_ENTRY (skill, serve_ball)
{
	if (multi_ball_play () || !global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	skill_enable();
}

//disable skill  - NEW right inlane also stops skill
CALLSET_ENTRY (skill, end_ball, stop_game, sw_left_ramp_enter, sw_right_inlane, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
	{
		skill_disable();
	}
}

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
All lock stuff here

Rules:
- hit 2 green targets to light locks, then lock 3 balls and start 3ball mball.c
//- skillshot can also lock a ball and start qmball.c 2 ball mb
- wetwilly mode started here when raft9 reached

*/

#include <freewpc.h>
#include <status.h>

extern U8 riverclass; 
extern U8 raftnr; //rafts.c

extern U8 lock_player_locks_lit;	//locks lit by current player
extern U8 lock_balls_in_devlock;  //locks.c  balls actually present in physical lock

__local__ U8 lock_player_vlocks_made;	//balls locked by current player, can be more or less than nr of physical balls locked

__local__ U8 player_mballs_played;	//how many times player started multiball

U8 lock_lefthit;	//U8 to count how many times target has been hit
U8 lock_righthit;	//nr to hit increases with nr of mballs played




//void lock_recountlock (void)
//{
//	lock_balls_in_lock = device_recount (device_entry (DEVNO_LOCK));
//}

void hz3_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "NO WAY OUT");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}



void lock_lamp_update (void)
{
//	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE) || free_timer_test (TIM_SKILL) || global_flag_test (GLOBAL_FLAG_SKILL_ENABLED) 

	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE) // || global_flag_test (GLOBAL_FLAG_SKILL_ENABLED) 
		|| global_flag_test (GLOBAL_FLAG_MBALL_RUNNING))
		return;

	if (lock_lefthit > player_mballs_played || lock_player_locks_lit >0)
		lamp_tristate_on (LM_LOCK_LEFT);
	else 
		lamp_tristate_flash (LM_LOCK_LEFT);
	
	if (lock_righthit > player_mballs_played || lock_player_locks_lit >0)
		lamp_tristate_on (LM_LOCK_RIGHT);
	else 
		lamp_tristate_flash (LM_LOCK_RIGHT);

	if (lock_player_vlocks_made == 0 && lock_player_locks_lit == 0)
	{
		lamp_tristate_off (LM_LOCK_1);
		lamp_tristate_off (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_player_vlocks_made == 0 && lock_player_locks_lit == 1)
	{
		lamp_tristate_flash (LM_LOCK_1);
		lamp_tristate_off (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_player_vlocks_made == 0 && lock_player_locks_lit == 2)
	{
		lamp_tristate_flash (LM_LOCK_1);
		lamp_tristate_flash (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_player_vlocks_made == 0 && lock_player_locks_lit == 3)
	{
		lamp_tristate_flash (LM_LOCK_1);
		lamp_tristate_flash (LM_LOCK_2);
		lamp_tristate_flash (LM_LOCK_3);
	}
	else if (lock_player_vlocks_made == 1 && lock_player_locks_lit == 0)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_off (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_player_vlocks_made == 1 && lock_player_locks_lit == 1)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_flash (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_player_vlocks_made == 1 && lock_player_locks_lit > 1)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_flash (LM_LOCK_2);
		lamp_tristate_flash (LM_LOCK_3);
	}
	else if (lock_player_vlocks_made == 2 && lock_player_locks_lit == 0)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_on (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_player_vlocks_made == 2 && lock_player_locks_lit > 0)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_on (LM_LOCK_2);
		lamp_tristate_flash (LM_LOCK_3);
	}
}

//check at start of ball how many balls are physical in lock and give lit locks to compensate
//void lock_recountlit (void)
void lock_compensate_stolenlocks (void)
{
	if (lock_player_vlocks_made > lock_balls_in_devlock)
	{
		lock_player_locks_lit = lock_player_vlocks_made - lock_balls_in_devlock;
	}
	lock_lamp_update ();
}

void lock_unlockball (void) 	//also started from other multiball code
{
	bounded_decrement (lock_balls_in_devlock, 0);
	global_flag_off (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
	device_unlock_ball (device_entry (DEVNO_LOCK));
}

void lock_lockball (void)		//actually lock a ball
{
	bounded_increment (lock_balls_in_devlock, 3);
//	device_lock_ball (device_entry (DEVNO_LOCK));
	device_t *dev = device_entry (DEVNO_LOCK);
	device_lock_ball (dev);
}

bool can_lock_ball (void)	//check if we can lock a ball or release it from devlock
{	
	if ( lock_player_locks_lit > 0
		&& lock_player_vlocks_made < 3
	//	&& global_flag_test (GLOBAL_FLAG_RAFTMODE)
		)
		return TRUE;
	else
		return FALSE;
}


void lock_reset_tgts_hit (void)		//reset counters
{
	lock_lefthit = 0;
	lock_righthit = 0;
}

//game rule : required target hits increase with nr of multiballs played
void lock_check_and_add_locklit (void)	//check if enough target hits to light lock
{
	if (lock_player_locks_lit == 0 && lock_lefthit >  player_mballs_played && lock_righthit >  player_mballs_played)
	{
		lock_player_locks_lit++;
		deff_start (DEFF_LOCK_LIT);
	}
	lock_lamp_update ();
}

void lock_resetlock (void)		//reset lock state at start of player or mball started
{
	lock_player_vlocks_made = 0;
//	lock_max_locks_made = 0;
	lock_player_locks_lit = 0;
	lamp_tristate_off (LM_LOCK_1);
	lamp_tristate_off (LM_LOCK_2);
	lamp_tristate_off (LM_LOCK_3);
	lamp_tristate_off (LM_LOCK_LEFT);
	lamp_tristate_off (LM_LOCK_RIGHT);
	lock_reset_tgts_hit ();
}

void lock_lamps_off (void)		//turn off lamps
{
	lamp_tristate_off (LM_LOCK_LEFT);
	lamp_tristate_off (LM_LOCK_RIGHT);
	lamp_tristate_off (LM_LOCK_1);
	lamp_tristate_off (LM_LOCK_2);
	lamp_tristate_off (LM_LOCK_3);
}

//game rule: decide what mode to start
void lock_devlock_entered (void)	//ball entered lock device
{

	if (raftnr == 9)	//final raft - start wet willy
	{
		raftnr++;
		global_flag_on (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
//		wet_start ();
		callset_invoke (start_wetwilly);
		return;
	}

/*	
//REMOVED : no more quickmb from skillshot as it's too easy
	if (free_timer_test (TIM_SKILL))
	{
		global_flag_on (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
		qmball_start ();
		return;
	}
*/

//	if ( lock_player_locks_lit > 0 && lock_player_vlocks_made < 3)	//player can lock a ball
	if (can_lock_ball ())
	{

//		if (flag_test (FLAG_HZ3LIT) && global_flag_test (GLOBAL_FLAG_RAFTMODE))
//			raft_score_hz3_nowayout (TRUE); 	//moved here from rafts.c  - award raft and then lock ball
//			callset_invoke (raft_score_hz3_nowayout_true);

		bounded_decrement (lock_player_locks_lit, 0);
		bounded_increment (lock_player_vlocks_made, 3);

		if (lock_balls_in_devlock < lock_player_vlocks_made)	//check if we need to physically lock the ball
			lock_lockball ();

		lock_reset_tgts_hit ();

		lock_lamp_update ();

		switch (lock_player_vlocks_made)
		{
			case 1:
				deff_start_sync (DEFF_LOCK_LOCK1);
				break;
			case 2:
				deff_start_sync (DEFF_LOCK_LOCK2);
				break;
//			case 3:		//moved below to start of multiball
//				deff_start_sync (DEFF_LOCK_LOCK3);
//				break;
			default:
				break;
		}

		if (lock_player_vlocks_made == 3)
		{
			lock_resetlock ();
//			while (deff_get_active() == DEFF_LOCK_LOCK3)
//			{
//				task_sleep (TIME_100MS);
//			}

//			if (flag_test (FLAG_WPOOLFINISHED) && flag_test (FLAG_GOLDPLAYED) && flag_test (FLAG_WETFINISHED) 
//					&& riverclass == 6)
//			{
//				wizard_start ();
//				return;
//			}
//			else

//			{
				deff_start_sync (DEFF_LOCK_LOCK3);
				bounded_increment (player_mballs_played, 255);
				mball_start ();
				return;
//			}

		}
	}
	else
	{
		if (flag_test (FLAG_HZ3LIT))
		{
			callset_invoke (raft_score_hz3_nowayout_false);
//			raft_score_hz3_nowayout (FALSE); 	//moved here from rafts.c  - no lock, but award raft
		}
		else
			deff_start (DEFF_HZ3);	//no lock, no hazard award, just proceed and kickout pinball
	}	
	
}


CALLSET_ENTRY (lock, sw_lock_left)		//left lock switch hit
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	bounded_increment (lock_lefthit, 255);
	lock_check_and_add_locklit ();
}

CALLSET_ENTRY (lock, sw_lock_right)		//right lock switch hit
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	bounded_increment (lock_righthit, 255);
	lock_check_and_add_locklit ();
}

CALLSET_ENTRY (lock, dev_lock_enter)		//ball entered in lock device
{
	if (!in_live_game || !global_flag_test (GLOBAL_FLAG_RAFTMODE) || multi_ball_play ())
		return;
	
	lock_devlock_entered ();
}

CALLSET_ENTRY (lock, raft_lamps_off)	//turn off lamps
{
	lock_lamps_off ();
}

CALLSET_ENTRY (lock, raft_lamps_on)		//turn on lamps
{
	lock_lamp_update ();
}


CALLSET_ENTRY (lock, start_ball)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	lock_compensate_stolenlocks ();
	lock_reset_tgts_hit ();
	lock_lamp_update ();
}

CALLSET_ENTRY (lock, start_player)
{
	player_mballs_played = 0;
	lock_player_locks_lit = 0;
	lock_resetlock ();

//	lock_reset_tgts_hit ();
}

CALLSET_ENTRY (lock, start_game)
{
	lock_balls_in_devlock = 0;
}

CALLSET_ENTRY (lock, end_game)
{
	device_request_empty (device_entry (DEVNO_LOCK));
	lock_balls_in_devlock = 0;
}


CALLSET_ENTRY (lock, status_report)
{
	status_page_init ();
	sprintf ("%d LOCKS LIT", lock_player_locks_lit);
	font_render_string_center (&font_mono5, 64, 10, sprintf_buffer);
	sprintf ("%d BALLS VLOCKED", lock_player_vlocks_made);
	font_render_string_center (&font_mono5, 64, 18, sprintf_buffer);
	sprintf ("%d BALLS IN LOCK", lock_balls_in_devlock);
	font_render_string_center (&font_mono5, 64, 24, sprintf_buffer);

	status_page_complete ();
}


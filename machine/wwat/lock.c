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
- skillshot can also lock a ball and start qmball.c 2 ball mb
- wetwilly mode started here when raft9 reached
*/

#include <freewpc.h>
#include <status.h>

extern U8 riverclass;
extern U8 raftnr;

__local__ U8 lock_locks_lit;	//locks lit by current player
__local__ U8 lock_locks_made;	//locks made by current player, at the moment

__local__ U8 mballs_played;
U8 lock_lefthit;
U8 lock_righthit;



//void lock_recountlock (void)
//{
//	lock_balls_in_lock = device_recount (device_entry (DEVNO_LOCK));
//}


//check at start of ball how many balls are physical in lock and give lit locks to compensate
void lock_recountlit (void)
{
	U8 ballsinlock;
	ballsinlock = device_recount (device_entry (DEVNO_LOCK));
	if (lock_locks_made > ballsinlock)
	{
		lock_locks_lit = lock_locks_lit + lock_locks_made - ballsinlock;
		lock_locks_made = device_recount (device_entry (DEVNO_LOCK));
	}
}

void lock_unlockball (void)
{
	global_flag_off (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
	device_unlock_ball (device_entry (DEVNO_LOCK));
	bounded_decrement (lock_locks_made, 0);
//	bounded_increment (lock_locks_lit, 3);
}

void lock_lockball (void)
{
	bounded_decrement (lock_locks_lit, 0);
	bounded_increment (lock_locks_made, 3);

	// check if we can keep the ball in the physical lock
	if (lock_locks_made == device_recount (device_entry (DEVNO_LOCK)))
		device_lock_ball (device_entry (DEVNO_LOCK));
}

bool can_lock_ball (void)
{	
//	lock_recountlit ();
	if ( lock_locks_lit > 0 
		&& lock_locks_made < 3
		&& global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return TRUE;
	else
		return FALSE;
}

void lock_reset_tgtshit (void)
{
	lock_lefthit = 0;
	lock_righthit = 0;
	lamp_tristate_off (LM_LOCK_LEFT);
	lamp_tristate_off (LM_LOCK_RIGHT);
}

void lock_check_addlock (void)
{
	lock_recountlit ();
	if (lock_lefthit >  mballs_played && lock_righthit >  mballs_played && lock_locks_lit == 0)
	{
		lock_locks_lit++;
		deff_start (DEFF_LOCK_LIT);
	}
}

void lock_resetlock (void)
{
	lock_locks_made = 0;
//	lock_max_locks_made = 0;
	lock_locks_lit = 0;
	lamp_tristate_off (LM_LOCK_1);
	lamp_tristate_off (LM_LOCK_2);
	lamp_tristate_off (LM_LOCK_3);
	lock_reset_tgtshit ();
}




CALLSET_ENTRY (lock, sw_lock_left)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	bounded_increment (lock_lefthit, 255);
	lock_check_addlock ();
}

CALLSET_ENTRY (lock, sw_lock_right)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	bounded_increment (lock_righthit, 255);
	lock_check_addlock ();
}

CALLSET_ENTRY (lock, dev_lock_enter)
{
	if (!in_live_game || !global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (raftnr == 9)
	{
		raftnr++;
		global_flag_on (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
		wet_start ();
		return;
	}

	if (free_timer_test (TIM_SKILL))
	{
		global_flag_on (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
		device_lock_ball (device_entry (DEVNO_LOCK));
		qmball_start ();
		return;
	}

	if (can_lock_ball ())
	{
		lock_lockball ();

		switch (lock_locks_made)
		{
			case 1:
				deff_start (DEFF_LOCK_LOCK1);
				break;
			case 2:
				deff_start (DEFF_LOCK_LOCK2);
				break;
			case 3:
				deff_start (DEFF_LOCK_LOCK3);
				break;
		}
		lock_reset_tgtshit ();
		task_sleep_sec (2);

		if (lock_locks_made == 3)
		{
			lock_resetlock ();
			while (deff_get_active() == DEFF_LOCK_LOCK3)
			{
				task_sleep (TIME_100MS);
			}

			if (flag_test (FLAG_WPOOLFINISHED) && flag_test (FLAG_GOLDPLAYED) && flag_test (FLAG_WETFINISHED) 
					&& flag_test (FLAG_MAPPLAYED) && riverclass == 6)
			{
				wizard_start ();
			}
			else
			{
				bounded_increment (mballs_played, 5);
				mball_start ();
			}
		}
	}
	else
		deff_start (DEFF_HZ3);
}

CALLSET_ENTRY (lock, lamp_update)
{
	if (global_flag_test (GLOBAL_FLAG_PF_LAMPS_OFF) || !global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (free_timer_test (TIM_SKILL) || 	global_flag_test (GLOBAL_FLAG_SKILL_ENABLED))
		return;

	if (lock_lefthit > mballs_played)
		lamp_tristate_on (LM_LOCK_LEFT);
	else 
		lamp_tristate_flash (LM_LOCK_LEFT);
	
	if (lock_righthit > mballs_played)
		lamp_tristate_on (LM_LOCK_RIGHT);
	else 
		lamp_tristate_flash (LM_LOCK_RIGHT);

	if (lock_locks_made == 0 && lock_locks_lit == 0)
	{
		lamp_tristate_off (LM_LOCK_1);
		lamp_tristate_off (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_locks_made == 0 && lock_locks_lit == 1)
	{
		lamp_tristate_flash (LM_LOCK_1);
		lamp_tristate_off (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_locks_made == 0 && lock_locks_lit == 2)
	{
		lamp_tristate_flash (LM_LOCK_1);
		lamp_tristate_flash (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_locks_made == 0 && lock_locks_lit == 3)
	{
		lamp_tristate_flash (LM_LOCK_1);
		lamp_tristate_flash (LM_LOCK_2);
		lamp_tristate_flash (LM_LOCK_3);
	}
	else if (lock_locks_made == 1 && lock_locks_lit == 0)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_off (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_locks_made == 1 && lock_locks_lit == 1)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_flash (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_locks_made == 1 && lock_locks_lit > 1)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_flash (LM_LOCK_2);
		lamp_tristate_flash (LM_LOCK_3);
	}
	else if (lock_locks_made == 2 && lock_locks_lit == 0)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_on (LM_LOCK_2);
		lamp_tristate_off (LM_LOCK_3);
	}
	else if (lock_locks_made == 2 && lock_locks_lit > 0)
	{
		lamp_tristate_on (LM_LOCK_1);
		lamp_tristate_on (LM_LOCK_2);
		lamp_tristate_flash (LM_LOCK_3);
	}
}

CALLSET_ENTRY (lock, start_ball)
{
	lock_recountlit ();
	lock_reset_tgtshit ();
}

CALLSET_ENTRY (lock, start_player)
{
	mballs_played = 0;
	lock_resetlock ();
}

CALLSET_ENTRY (lock, end_game, amode_start)
{
	device_request_empty (device_entry (DEVNO_LOCK));
}


CALLSET_ENTRY (lock, status_report)
{
	status_page_init ();
	sprintf ("%d LOCKS LIT", lock_locks_lit);
	font_render_string_center (&font_mono5, 64, 10, sprintf_buffer);
	sprintf ("%d BALLS LOCKED", lock_locks_made);
	font_render_string_center (&font_mono5, 64, 18, sprintf_buffer);
//	sprintf ("%d BALLS IN LOCK", lock_balls_in_lock);
//	font_render_string_center (&font_mono5, 64, 22, sprintf_buffer);

	status_page_complete ();
}


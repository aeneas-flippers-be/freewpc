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

RULES shoot lost mine scoop

//start GOLDRUSH at 2 lost mine shots or when key is already collected
//start QUICK MB at 4 lost mine shots 

*/

 
#include <freewpc.h>
#include <status.h>

extern U8 lostmine_nrshot;

__local__ U8 lostmine_nrshotgold;

U8 wpool_balls_entered;	//how many pinballs fell in wpool exit opto switch and will roll to lostmine exit


//RULES   here we define what gets started
void lostmine_shot (void)
{
	global_flag_on (GLOBAL_FLAG_HOLD_MINE_KICKOUT);	//wait ball to kickout
	score (SC_250K);
	bounded_increment (lostmine_nrshot, 255);
	bounded_increment (lostmine_nrshotgold, 3);
	
	deff_start (DEFF_LOSTMINE);

	//RULES
	if (lostmine_nrshotgold == 1)
	{
		speech_start (SND_WHICHWAYGO, SL_3S);
		task_sleep_sec (2);
		bash_start ();
	}
	else if (lostmine_nrshotgold == 2)
	{
		flag_on (FLAG_GOLDPLAYED);  //checked for in lock.c to start wizard mode
		gold_start ();	
	}
	else if (lostmine_nrshotgold == 3)
	{
		lostmine_nrshotgold = 0;
		qmball_start ();
	}
}


/*	OLD CODE BELOW
	if (!flag_test (FLAG_BFCLIGHT))
	{
		speech_start (SND_ANYBODYLIGHT, SL_4S);
		task_sleep_sec (2);
	}
	else if (!flag_test (FLAG_BFCKEY))
	{
		speech_start (SND_GOTFLASHLIGHT, SL_2S);
		task_sleep_sec (2);
		speech_start (SND_THISDOORLOCKED, SL_3S);
	} 
	else if (lostmine_nrshot < 2 || lostmine_nrshotgold < 3)
	{
		if (lostmine_nrshot < 2)
		{
			speech_start (SND_WHICHWAYGO, SL_3S);
			task_sleep_sec (2);
		}
		bash_start ();
	}
	else 
	{
//		if (!flag_test (FLAG_GOLDPLAYED) || lostmine_nrshotgold = 3)
//		{
			speech_start (SND_THISDOORLOCKED, SL_3S);
			task_sleep_sec (2);
			speech_start (SND_TRYTHISKEY, SL_2S);
			task_sleep_sec (1);
			flag_on (FLAG_GOLDPLAYED);
			lostmine_nrshotgold = 0;
			gold_start ();
//		}
	}

//	global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
*/


CALLSET_ENTRY (lostmine, dev_lostmine_enter)
{
	if (!in_live_game || !global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

//	if (!free_timer_test (TIM_WPOOL))
	if (wpool_balls_entered == 0)
	{
		lostmine_shot ();
	}
	else
	{
		bounded_decrement(wpool_balls_entered, 0);		
	}
}

CALLSET_ENTRY (lostmine, sw_whirlpool_exit)
{
	bounded_increment(wpool_balls_entered, 255);
//	free_timer_restart (TIM_WPOOL, TIME_4S);
}

CALLSET_ENTRY (lostmine, start_ball)
{
	wpool_balls_entered = 0;
}

CALLSET_ENTRY (lostmine, start_player)
{
	lostmine_nrshot = 0;
	lostmine_nrshotgold = 0;
}

CALLSET_ENTRY (lostmine, status_report)
{
	status_page_init ();
	sprintf ("%d LOST MINE SHOTS", lostmine_nrshot);
	font_render_string_center (&font_mono5, 64, 10, sprintf_buffer);
/*	
	sprintf ("%d BALLS LOCKED", mball_locks_made);
	font_render_string_center (&font_mono5, 64, 21, sprintf_buffer);
*/
	status_page_complete ();
}

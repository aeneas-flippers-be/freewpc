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
	kickback - lit at start of game
	lit again by hitting 3 red targets

lamp:
12: kickback, red
switch:
25: Left outlane, ingame

*/

#include <freewpc.h>
#include <kickback_driver.h>



void kickback_enable (void)
{
	kickback_driver_enable();
	lamp_tristate_on (LM_KICKBACK); 
	task_sleep (TIME_100MS);
	lamp_tristate_off (LM_KICKBACK); 
	task_sleep (TIME_100MS);
	lamp_tristate_on (LM_KICKBACK); 
	flag_on (FLAG_KICKBACKLIT);
}

void kickback_disable (void)
{
	flag_off (FLAG_KICKBACKLIT);
	lamp_tristate_off (LM_KICKBACK); 
	kickback_driver_disable();
}

void kickback_finish (void)
{
	task_sleep_sec (3);
	kickback_disable ();
	task_exit ();
}

CALLSET_ENTRY (kickback, sw_kickback)
{
	if (flag_test (FLAG_KICKBACKLIT))
	{
		speech_start (SND_FEMALE_YEAH6, SL_2S);
		task_recreate_gid (GID_KICKBACK_FINISH, kickback_finish);
		deff_start (DEFF_KICKBACK);
	}
	else
	{
		sound_send (SND_DANGLOSTANOTHER);
//		speech_start (SND_DANGLOSTANOTHER, SL_4S);
	}
}

CALLSET_ENTRY (kickback, lamp_update)
{
	if (flag_test (FLAG_KICKBACKLIT))
		lamp_tristate_on (LM_KICKBACK); 
}

CALLSET_ENTRY (kickback, start_player)
{
	kickback_enable ();
}

CALLSET_ENTRY (kickback, start_ball)
{
	if (flag_test (FLAG_KICKBACKLIT))
	{
		kickback_enable ();
	}
	else
	{
		kickback_disable ();
	}
}

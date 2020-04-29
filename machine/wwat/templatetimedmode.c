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
template with minimum to implement a timed mode
*/

#include <freewpc.h>
#include <timedmode.h>

#define TEMP_MODE_TIME 20

U8 templ_timer;

void templ_mode_init (void)
{
}

void templ_mode_exit (void)
{
	deff_stop (DEFF_TEMPL_RUNNING);
}

void templ_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();
//fontrendersomething
		dmd_show_low ();
		task_sleep (TIME_100MS);
	}
}

struct timed_mode_ops templ_mode = {
	DEFAULT_MODE,
	.init = templ_mode_init,
	.exit = templ_mode_exit,
//	.music = MUS_MANOVERB_1,
//	.deff_starting = DEFF_TEMPL_START,
//	.deff_running = DEFF_TEMPL_RUNNING,
//	.deff_ending = DEFF_TEMPL_END,
	.gid = GID_templ_MODE,
	.prio = PRI_GAME_MODE3,
	.init_timer = TEMP_MODE_TIME,
	.timer = &templ_timer,
	.grace_timer = 1,
	.pause = system_timer_pause,
};

CALLSET_ENTRY (templ, display_update)
{
	if (timed_mode_running_p (&templ_mode))
	{
		deff_start_bg (DEFF_TEMPL_RUNNING, 0);
	}
}

CALLSET_ENTRY (templ, music_refresh)
{
	if (timed_mode_running_p (&templ_mode))
	{
//		music_request (MUS_MANOVERB_1, PRI_GAME_MODE1 +3);
	}
}

CALLSET_ENTRY (templ, end_ball, tilt)
{
	if (timed_mode_running_p (&templ_mode))
		timed_mode_end (&templ_mode);
}

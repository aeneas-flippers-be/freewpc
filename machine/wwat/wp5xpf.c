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
Timed mode - 30 seconds everything scores 5x more
started from wpoolmodes.c
*/

#include <freewpc.h>
#include <timedmode.h>

U8 pf_mult_timer;


void wp5xpf_mode_exit (void)
{
	score_multiplier_set (1);
	deff_stop (DEFF_WP5XPF_RUNNING);
	global_flag_off (GLOBAL_FLAG_WP5X_RUNNING);
}

struct timed_mode_ops pf5x_mode = {
	DEFAULT_MODE,
	.exit = wp5xpf_mode_exit,
//	.deff_running = DEFF_WP5XPF_RUNNING,
	.prio = PRI_GAME_MODE5,
	.gid = GID_PF5X_MODE,
	.timer = &pf_mult_timer,
	.init_timer = 30,
	.grace_timer = 1,
	.pause = system_timer_pause,
};

void wp5x_start (void)
{
	score_multiplier_set (5);
	speech_start (SND_5TIMESFUN, SL_3S);
	global_flag_on (GLOBAL_FLAG_WP5X_RUNNING);
	timed_mode_begin (&pf5x_mode);
}

CALLSET_ENTRY (wp5x, music_refresh)
{
	if (timed_mode_running_p (&pf5x_mode))
	{
		music_request (MUS_FRENZY_2, PRI_GAME_MODE1 +2);
	}
}

CALLSET_ENTRY (wp5x, display_update)
{
	if (timed_mode_running_p (&pf5x_mode))
	{
		deff_start_bg (DEFF_WP5XPF_RUNNING, 0);
	}
}

CALLSET_ENTRY (wp5x, end_ball, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
		timed_mode_end (&pf5x_mode);
}



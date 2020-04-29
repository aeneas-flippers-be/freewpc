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
instructions for bigfoot head - can move forward, backward, rotate
*/


#include <freewpc.h>
#include <bigfhead.h>

U8 bfh_turnsccw;
U8 bfh_turnscw;


/* turn face to front, wait, turn back */
void bfh_showface_cw_task (void)
{
	bigfhead_go_front_cw ();
	task_sleep_sec (3);
	bigfhead_go_back_ccw ();
	task_exit ();
}

void bfh_showface_cw (void)
{
	if (!task_find_gid (GID_BFHEAD))
		task_create_gid (GID_BFHEAD, bfh_showface_cw_task);
}

/* turn face to front, wait, turn back */
void bfh_showface_ccw_task (void)
{
	bigfhead_go_front_ccw ();
	task_sleep_sec (3);
	bigfhead_go_back_cw ();
	task_exit ();
}

void bfh_showface_ccw (void)
{
	if (!task_find_gid (GID_BFHEAD))
		task_create_gid (GID_BFHEAD, bfh_showface_ccw_task);
}

void bfh_rotate_ccw (U8 nrturns)
{
	bfh_turnsccw = nrturns;
	bigfhead_go_front_ccw ();
}

void bfh_rotate_cw (U8 nrturns)
{
	bfh_turnscw = nrturns;
	bigfhead_go_front_cw ();
}

CALLSET_ENTRY (bfhead, sw_bfhead_back)
{
	if (bfh_turnsccw > 0)
	{
		bigfhead_go_front_ccw ();
	}
	if (bfh_turnscw > 0)
	{
		bigfhead_go_front_cw ();
	}
}

CALLSET_ENTRY (bfhead, sw_bfhead_front)
{
	if (bfh_turnsccw > 0)
	{
		bigfhead_go_back_ccw ();
		bfh_turnsccw--;
	}
	if (bfh_turnscw > 0)
	{
		bigfhead_go_back_cw ();
		bfh_turnscw--;
	}
}

CALLSET_ENTRY (bfhead, start_ball)
{
	bfh_turnsccw = 0;
	bfh_turnscw = 0;
}

CALLSET_ENTRY (bfhead, tilt, end_game, end_ball)
{
	task_kill_gid (GID_BFHEAD);
	bfh_turnsccw = 0;
	bfh_turnscw = 0;
//	bigfhead_go_back_cw ();
}


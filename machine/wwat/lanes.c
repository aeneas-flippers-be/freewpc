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
lamps
13: left outlane, white
14: left inlane, red
15: right inlane, red
16: right outlane, white

sw
25: Kickback, ingame => sw_left_outlane
26: Left inlane, ingame
27: Right inlane, ingame
28: Right outlane, ingame

*/

#include <freewpc.h>


CALLSET_ENTRY (lanes, sw_left_button)
{
	if (in_game)
		lamplist_rotate_previous (LAMPLIST_LANES, lamp_matrix);
}

CALLSET_ENTRY (lanes, sw_right_button)
{
	if (in_game)
		lamplist_rotate_next (LAMPLIST_LANES, lamp_matrix);
}


CALLSET_ENTRY (lanes, sw_kickback)
{
	if (lamp_test (LM_LEFT_OUTLANE))
		score (SC_250K);
}

CALLSET_ENTRY (lanes, sw_right_outlane)
{
	if (lamp_test (LM_RIGHT_OUTLANE))
		score (SC_250K);

	sound_start (ST_SAMPLE, SND_BAD_1, SL_4S, PRI_GAME_QUICK3);
}

CALLSET_ENTRY (lanes, sw_left_inlane)
{
	if (lamp_test (LM_LEFT_INLANE))
	{
		score (SC_250K);
		callset_invoke (spot_river_letter);
	}
}

CALLSET_ENTRY (lanes, sw_right_inlane)
{
	if (lamp_test (LM_RIGHT_INLANE))
	{
		score (SC_250K);
		callset_invoke (spot_river_letter);
	}
}

CALLSET_ENTRY (lanes, start_ball)
{
	lamplist_apply (LAMPLIST_LANES, lamp_off);
	lamp_on (LM_LEFT_OUTLANE);
}


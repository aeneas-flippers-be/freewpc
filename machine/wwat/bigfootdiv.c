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
Handle bigfoot diverter

if whirlpool mode qualified => divert, red light on
no wp qual but bigfoot qual => don't divert, red light flashing
nothing qual => no light, no divert

enable div solenoid and disable after 3 seconds / tilt/endball/.. make sure to always disable !

lamp:
55: light whirlpool, red

switch:
48: canyon entrance, ingame
57: canyon main, ingame, opto
58: bigfoot cave, ingame
62: whirlpool exit, ingame, opto

*/

#include <freewpc.h>
#include <bigfdiv.h>
//#include <bigfhead.h>


void bfdiv_divert (void)
{
	bigfdiv_start ();
	bfh_showface_ccw ();
	leff_start (LEFF_FL_BIGFOOT);
	callset_invoke (wpool_enter);
}


CALLSET_ENTRY (bfdiv, lamp_update)
{
//	if (multi_ball_play ())
//		return;

	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (global_flag_test (GLOBAL_FLAG_WPOOLLIT) || flag_test (FLAG_DAM_LIT))
		lamp_tristate_on (LM_LIGHT_WHIRLPOOL);
	else if (global_flag_test (GLOBAL_FLAG_BIGFOOTLIT))
		lamp_tristate_flash (LM_LIGHT_WHIRLPOOL);
	else
		lamp_tristate_off (LM_LIGHT_WHIRLPOOL);
}

CALLSET_ENTRY (bfdiv, sw_canyon_entrance)
{
	if (global_flag_test (GLOBAL_FLAG_WPCH_RUNNING) || global_flag_test (GLOBAL_FLAG_WPOOLLIT))
	{
		bfdiv_divert ();
	}
}

CALLSET_ENTRY (bfdiv, tilt, end_game, end_ball)
{
	bigfdiv_stop ();
}



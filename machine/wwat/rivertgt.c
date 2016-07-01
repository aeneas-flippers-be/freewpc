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
Spell river by hitting blue targets
lit inlanes spot next available river letter
Light whirlpool when river is spelled

lamps:
21: river r1, blue
22: river i, blue
23: river v, blue
24: river e, blue
25: river r2, blue
LAMPLIST_RIVER

sw:
31: River R2, ingame, standup
32: River E, ingame, standup
33: River V, ingame, standup
34: River I, ingame, standup
35: River R1, ingame, standup
*/

#include <freewpc.h>


void river_off (void)
{
	global_flag_off (GLOBAL_FLAG_RIVERR1);
	global_flag_off (GLOBAL_FLAG_RIVERR2);
	global_flag_off (GLOBAL_FLAG_RIVERI);
	global_flag_off (GLOBAL_FLAG_RIVERV);
	global_flag_off (GLOBAL_FLAG_RIVERE);
	lamp_tristate_off (LM_RIVER_R1);
	lamp_tristate_off (LM_RIVER_R2);
	lamp_tristate_off (LM_RIVER_I);
	lamp_tristate_off (LM_RIVER_V);
	lamp_tristate_off (LM_RIVER_E);
}

void river_check (void)
{
	score (SC_20K);

	if (global_flag_test (GLOBAL_FLAG_RIVERR1) && global_flag_test (GLOBAL_FLAG_RIVERR2) && global_flag_test (GLOBAL_FLAG_RIVERI)
		&& global_flag_test (GLOBAL_FLAG_RIVERV) && global_flag_test (GLOBAL_FLAG_RIVERE))
	{
		global_flag_on (GLOBAL_FLAG_WPOOLLIT);
		
		lamplist_apply (LAMPLIST_RIVER, lamp_off);
		task_sleep (TIME_100MS);
		lamplist_apply (LAMPLIST_RIVER, lamp_on);
		task_sleep (TIME_100MS);
		lamplist_apply (LAMPLIST_RIVER, lamp_off);
		sound_start (ST_SAMPLE, SND_OK_2, SL_3S, PRI_GAME_QUICK3);
		deff_start (DEFF_RIVER_COMPLETE);
		river_off ();
	}
	else
		deff_start (DEFF_RIVERLETTER);
}

CALLSET_ENTRY (rivertgt, lamp_update)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) || global_flag_test (GLOBAL_FLAG_PF_LAMPS_OFF) || !global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (global_flag_test (GLOBAL_FLAG_RIVERR1))
		lamp_tristate_on (LM_RIVER_R1);
	if (global_flag_test (GLOBAL_FLAG_RIVERR2))
		lamp_tristate_on (LM_RIVER_R2);
	if (global_flag_test (GLOBAL_FLAG_RIVERI))
		lamp_tristate_on (LM_RIVER_I);
	if (global_flag_test (GLOBAL_FLAG_RIVERV))
		lamp_tristate_on (LM_RIVER_V);
	if (global_flag_test (GLOBAL_FLAG_RIVERE))
		lamp_tristate_on (LM_RIVER_E);
}

CALLSET_ENTRY (rivertgt, spot_river_letter)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_HURRY_RUNNING))
		return;

//	sound_start (ST_SAMPLE, SND_SPLASH_6, SL_3S, PRI_GAME_QUICK3);

	if (!global_flag_test (GLOBAL_FLAG_RIVERR1))
		callset_invoke (sw_river_r1);
	else if (!global_flag_test (GLOBAL_FLAG_RIVERI))
		callset_invoke (sw_river_i);
	else if (!global_flag_test (GLOBAL_FLAG_RIVERV))
		callset_invoke (sw_river_v);
	else if (!global_flag_test (GLOBAL_FLAG_RIVERE))
		callset_invoke (sw_river_e);
	else if (!global_flag_test (GLOBAL_FLAG_RIVERR2))
		callset_invoke (sw_river_r2);
}

CALLSET_ENTRY (rivertgt, sw_river_r1)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) || !global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_RIVERR1))
		return;

	global_flag_on (GLOBAL_FLAG_RIVERR1);
	lamp_tristate_on (LM_RIVER_R1);
	river_check ();
}

CALLSET_ENTRY (rivertgt, sw_river_r2)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) || !global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_RIVERR2))
		return;

	global_flag_on (GLOBAL_FLAG_RIVERR2);
	lamp_tristate_on (LM_RIVER_R2);
	river_check ();
}

CALLSET_ENTRY (rivertgt, sw_river_i)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) || !global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_RIVERI))
		return;

	global_flag_on (GLOBAL_FLAG_RIVERI);
	lamp_tristate_on (LM_RIVER_I);
	river_check ();
}

CALLSET_ENTRY (rivertgt, sw_river_v)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) || !global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_RIVERV))
		return;

	global_flag_on (GLOBAL_FLAG_RIVERV);
	lamp_tristate_on (LM_RIVER_V);
	river_check ();
}

CALLSET_ENTRY (rivertgt, sw_river_e)
{
	if (global_flag_test (GLOBAL_FLAG_HURRY_RUNNING) || !global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_RIVERE))
		return;

	global_flag_on (GLOBAL_FLAG_RIVERE);
	lamp_tristate_on (LM_RIVER_E);
	river_check ();
}

CALLSET_ENTRY (rivertgt, start_ball)
{
	river_off ();
}


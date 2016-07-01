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
multimillion on left ramp
	- only during single ball
	- shooting left ramp and letting ball go down to right inlane lights timer for multimillion
	- shooting left ramp again scores mm, increases with additional shots
	- disabled when shooting a ramp on upf
	- sound on first time right inlane when multimill starts

lamp:
34: ramp mil, red
switches:
46: left ramp enter, ingame
66: left ramp main, ingame, opto
27: Right inlane, ingame
47: rapids enter, ingame
48: canyon entrance, ingame

#define SND_OOHMULTIMILL	0x017A
	#define SND_WAYTOGO			0x017B
	#define SND_OOH				0x017C
	#define SND_MULTIMILL		0x017D
*/

#include <freewpc.h>

U8 mmil_count;


void mmil_jackpot (void)
{
	bounded_increment (mmil_count, 5);

//	score_multiple (SC_1M, mmil_count);

	if (mmil_count < 5)
		speech_start (SND_OOH, SL_2S);
	else 
		speech_start (SND_WAYTOGO, SL_3S);

	deff_start (DEFF_MMILCOLLECTED);
}


CALLSET_ENTRY (mmil, left_ramp_made)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (free_timer_test (TIM_MULTIMILL))
	{
		mmil_jackpot ();
		free_timer_stop (TIM_MULTIMILL);
	}
	else
	{
		mmil_count = 0;
		speech_start (SND_MULTIMILL, SL_3S);
	}
	free_timer_start (TIM_MULTIMILL, TIME_4S);
}

CALLSET_ENTRY (mmil, lamp_update)
{
	if (free_timer_test (TIM_MULTIMILL))
		lamp_on (LM_RAMP_MIL);
	else
		lamp_off (LM_RAMP_MIL);
}

CALLSET_ENTRY (mmil, start_ball)
{
	mmil_count = 0;
}

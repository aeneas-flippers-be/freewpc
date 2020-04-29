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
hitting ANY 3 red targets at middle right of playfield lights kickback
if kickback is already lit then score (250K)
not available in goldrush or wizard mode
*/

#include <freewpc.h>

//let there be light
void redtgt_lamp_update (void)
{
	if (global_flag_test (GLOBAL_FLAG_REDTGT1))
		lamp_on (LM_3BANK_TOP);
	if (global_flag_test (GLOBAL_FLAG_REDTGT2))
		lamp_on (LM_3BANK_CENTER);
	if (global_flag_test (GLOBAL_FLAG_REDTGT3))
		lamp_on (LM_3BANK_BOTTOM);
}

void redtgt_off (void)
{
	global_flag_off (GLOBAL_FLAG_REDTGT1);
	global_flag_off (GLOBAL_FLAG_REDTGT2);
	global_flag_off (GLOBAL_FLAG_REDTGT3);
	lamp_off (LM_3BANK_TOP);
	lamp_off (LM_3BANK_CENTER);
	lamp_off (LM_3BANK_BOTTOM);
}

/* check if all 3 are lit */
void redtgt_check (void)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE))
	{
		redtgt_lamp_update ();
//		wpm_next_award ();
	}

	score (SC_20K);

	if (global_flag_test (GLOBAL_FLAG_REDTGT1) && global_flag_test (GLOBAL_FLAG_REDTGT2) && global_flag_test (GLOBAL_FLAG_REDTGT3))
	{
		redtgt_off ();

		if (!flag_test (FLAG_KICKBACKLIT))
		{
			kickback_enable ();  //RULE : enable kickback
			if (global_flag_test (GLOBAL_FLAG_RAFTMODE))
				deff_start (DEFF_KICKBACK_LIT);
		}
		else
		{
			score (SC_250K);	//score when kickback is already lit
		}
	}
}

/*  light next unlit target */
void redtgt_addtgt (void)
{
	if (!global_flag_test (GLOBAL_FLAG_REDTGT1))
	{
		global_flag_on (GLOBAL_FLAG_REDTGT1);
//		lamp_tristate_on (LM_3BANK_TOP);
	}
	else if (!global_flag_test (GLOBAL_FLAG_REDTGT2))
	{
		global_flag_on (GLOBAL_FLAG_REDTGT2);
//		lamp_tristate_on (LM_3BANK_CENTER);
	}
	else if (!global_flag_test (GLOBAL_FLAG_REDTGT3))
	{
		global_flag_on (GLOBAL_FLAG_REDTGT3);
//		lamp_tristate_on (LM_3BANK_BOTTOM);
	}

	redtgt_check ();  //check all 3 lit
}



CALLSET_ENTRY (redtgt, raft_lamps_off)
{
	lamp_off (LM_3BANK_TOP);
	lamp_off (LM_3BANK_CENTER);
	lamp_off (LM_3BANK_BOTTOM);
}

CALLSET_ENTRY (redtgt, raft_lamps_on)
{
	redtgt_lamp_update ();
}


CALLSET_ENTRY (redtgt, sw_3bank_top, sw_3bank_center, sw_3bank_bottom)
{
	redtgt_addtgt ();
}

CALLSET_ENTRY (redtgt, start_ball)
{
	redtgt_off ();
}



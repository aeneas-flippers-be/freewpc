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
hitting 3 red targets lights kickback
if kickback already lit then light something else

*/

#include <freewpc.h>


void redtgt_off (void)
{
	global_flag_off (GLOBAL_FLAG_REDTGT1);	
	global_flag_off (GLOBAL_FLAG_REDTGT2);	
	global_flag_off (GLOBAL_FLAG_REDTGT3);	
	lamp_tristate_off (LM_3BANK_TOP);
	lamp_tristate_off (LM_3BANK_CENTER);
	lamp_tristate_off (LM_3BANK_BOTTOM);
}

/* check if all 3 are lit */
void redtgt_check (void)
{
	if (global_flag_test (GLOBAL_FLAG_RAFTMODE))
		wpm_next_award ();

	score (SC_20K);

	if (global_flag_test (GLOBAL_FLAG_REDTGT1) && global_flag_test (GLOBAL_FLAG_REDTGT2) && global_flag_test (GLOBAL_FLAG_REDTGT3))
	{
		redtgt_off ();
		if (!flag_test (FLAG_KICKBACKLIT))
		{
			kickback_enable ();
			deff_start (DEFF_REDTGT_KICKBACK);
		}
		else
		{
//			if (global_flag_test (GLOBAL_FLAG_RAFTMODE))
//				wpm_next_award ();
//				raft_award_hazard ();
//			else
				score (SC_250K);
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

	redtgt_check ();
}

CALLSET_ENTRY (redtgt, lamp_update)
{
	if (global_flag_test (GLOBAL_FLAG_PF_LAMPS_OFF))
		return;

	if (global_flag_test (GLOBAL_FLAG_REDTGT1))
		lamp_tristate_on (LM_3BANK_TOP);
	if (global_flag_test (GLOBAL_FLAG_REDTGT2))
		lamp_tristate_on (LM_3BANK_CENTER);
	if (global_flag_test (GLOBAL_FLAG_REDTGT3))
		lamp_tristate_on (LM_3BANK_BOTTOM);
}


CALLSET_ENTRY (redtgt, sw_3bank_top, sw_3bank_center, sw_3bank_bottom)
{
/*	wpm_next_award (); */
	redtgt_addtgt ();
}

CALLSET_ENTRY (redtgt, start_ball)
{
	redtgt_off ();
}



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
lamps:
18: 6x multi, white
37: 2x multi, white
38: 3x multi, white
47: 4x multi, white
48: 5x multi, white
Rivclass: 2x multi, 3x multi, 4x multi, 5x multi, 6x multi

Show riverclass status. Goes up by jetbumper hits. Used as bonus multi x.
*/

#include <freewpc.h>


__local__ U8 riverclass;



void rivcl_reset (void)
{
	riverclass = 1;
	lamplist_apply (LAMPLIST_RIVCLASS, lamp_off);
}

void rivcl_increase_class (void)
{
	score (SC_20K);

	if (riverclass < 6)
	{
		riverclass++;

		deff_start (DEFF_RIVERCLASS);
		switch (riverclass)
		{
			case 2:
				speech_start (SND_CLASS2RIVER, SL_3S);
				break;
			case 3:
				speech_start (SND_CLASS3RIVER, SL_3S);
				break;
			case 4:
				speech_start (SND_CLASS4RIVER, SL_3S);
				break;
			case 5:
				speech_start (SND_CLASS5RIVER, SL_3S);
				break;
			case 6:
				speech_start (SND_CLASS6RIVER, SL_4S);
				break;
		}
	}
}

CALLSET_ENTRY (rivcl, lamp_update)
{
	switch (riverclass)
	{
		case 6:
			lamp_tristate_on (LM_6X_MULTI);
		case 5:
			lamp_tristate_on (LM_5X_MULTI);
		case 4:
			lamp_tristate_on (LM_4X_MULTI);
		case 3:
			lamp_tristate_on (LM_3X_MULTI);
		case 2:
			lamp_tristate_on (LM_2X_MULTI);
			break;
	}
/*	if (riverclass > 1)
		lamp_tristate_on (LM_2X_MULTI);
	if (riverclass > 2)
		lamp_tristate_on (LM_3X_MULTI);
	if (riverclass > 3)
		lamp_tristate_on (LM_4X_MULTI);
	if (riverclass > 4)
		lamp_tristate_on (LM_5X_MULTI);
	if (riverclass == 6)
		lamp_tristate_on (LM_6X_MULTI);
*/
}

CALLSET_ENTRY (rivcl, start_ball)
{
	lamplist_apply (LAMPLIST_RIVCLASS, lamp_off);
}

CALLSET_ENTRY (rivcl, start_player)
{
	rivcl_reset ();
}

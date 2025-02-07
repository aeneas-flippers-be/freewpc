/*
 * Copyright 2010 by Dominic Clifton <me@dominicclifton.name>
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

#include <freewpc.h>



/* Crypt / Asylum can be shot from front or from behind frop target */

CALLSET_ENTRY (asylum_shot, sw_drop_score)
{
	free_timer_start (TIM_ASYLUM_BEHIND, TIME_2S);
}

CALLSET_ENTRY (asylum_shot, dev_crypt_popper_enter)
{
	if (free_timer_test (TIM_ASYLUM_BEHIND))
	{
		free_timer_stop (TIM_ASYLUM_BEHIND);
		callset_invoke (asylum_behind_drop_shot);
	}
	else
	{
		callset_invoke (asylum_front_shot);
	}
}

/* Castle popper / Altar /Rats  can be shot from front or from hole top left */
CALLSET_ENTRY (altar_shot, sw_mystery_hole)
{
		free_timer_start (TIM_ALTAR_BEHIND, TIME_3S);
}

CALLSET_ENTRY (altar_shot, dev_castle_popper_enter)
{
	if (free_timer_test (TIM_ALTAR_BEHIND))
	{
		free_timer_stop (TIM_ALTAR_BEHIND);
		callset_invoke (altar_from_hole_shot);
	}
	else
	{
		callset_invoke (altar_front_shot);
	}
}



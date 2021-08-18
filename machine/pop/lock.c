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
All lock stuff here

Rules:
- hit 2  targets to light locks, then lock 3 balls and start 3ball mball

Lamps
65: left cheek, red
66: right cheek, red
31: lockjaw
48: rescue olive

Switches
61: left cheek, standup, ingame
62: right cheek, standup, ingame

TODO unlock 3 balls instead of device empty
TODO handle switches to define coil length

*/

#include <freewpc.h>


CALLSET_ENTRY (lock, dev_lock_enter)		//ball entered in lock device
{
	if (!in_live_game)
		return;

	if (!(lamp_test (LM_LEFT_CHEEK) && lamp_test (LM_RIGHT_CHEEK)))
		return;
	
	lamp_off (LM_LEFT_CHEEK);
	lamp_off (LM_RIGHT_CHEEK);

	device_t *dev = device_entry (DEVNO_LOCK);

	if (device_recount (dev) < 3)
	{
		device_lock_ball (dev);
	}
	else	//3rd ball, start mb
		device_request_empty (dev);	 //TODO change to unlock 3 balls
}


CALLSET_ENTRY (lock, sw_right_cheek)
{
	lamp_on (LM_RIGHT_CHEEK);
}

CALLSET_ENTRY (lock, sw_left_cheek)
{
	lamp_on (LM_LEFT_CHEEK);
}


CALLSET_ENTRY (lock, start_player)
{
	lamp_off (LM_LEFT_CHEEK);
	lamp_off (LM_LEFT_CHEEK);
	lamp_off (LM_LOCKJAW);
}




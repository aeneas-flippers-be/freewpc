/*
 * Copyright 2016 by Aeneas Verhe
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

/* always disable gate and magnet to be sure we don't forget */
CALLSET_ENTRY (magnet, sw_magnet_left)
{
	sol_disable (SOL_LEFT_GATE);
	sol_disable (SOL_MIST_MAGNET);
}

CALLSET_ENTRY (magnet, sw_magnet_right)
{
	sol_disable (SOL_RIGHT_GATE);
	sol_disable (SOL_MIST_MAGNET);
}


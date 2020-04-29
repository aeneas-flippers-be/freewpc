/*
 * Copyright 2006, 2007, 2008, 2010 by Brian Dominy <brian@oddchange.com>
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



void printf_millions (U8 n)
{
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
		sprintf ("%d,000,000", n *5);
	else
		sprintf ("%d,000,000", n);
}

void kickback_deff (void)
{
	U8 i;
	U8 x;
	x = 20;

	for (i = 0; i < 10; i++)
	{
		dmd_alloc_low_clean ();
		frame_draw (IMG_WATER1);
		font_render_string_center (&font_fixed10, x, 16, "RAFT SAVED");
		dmd_show_low ();
		task_sleep (TIME_100MS);

		x = x+2;
		dmd_alloc_low_clean ();
		frame_draw (IMG_WATER2);
		font_render_string_center (&font_fixed10, x, 16, "RAFT SAVED");
		dmd_show_low ();
		task_sleep (TIME_100MS);
		x = x+2;
	}
	deff_exit ();
}

void kickback_lit_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "KICKBACK ON");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}


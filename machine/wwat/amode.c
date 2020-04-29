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
 
 Attract mode DEFF
 
  */
#include <freewpc.h>


CALLSET_ENTRY (bigfoot_amode, amode_page)
{

	dmd_alloc_pair ();
	frame_draw (IMG_BFOOTLOGO);
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show2 ();
	task_sleep_sec (2);

	dmd_alloc_low_clean ();
	font_render_string_center (&font_var5, 64, 5, "BIGFOOT");
	font_render_string_center (&font_var5, 64, 12, "NEW GAME RULES");
	font_render_string_center (&font_var5, 64, 19, "DESIGNED BY");
	font_render_string_center (&font_var5, 64, 26, "AENEAS VERHE");
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show_low ();
	task_sleep_sec (1);

	dmd_alloc_pair ();
	frame_draw (IMG_FLIPLOGO);
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show2 ();
	task_sleep_sec (2);

	dmd_alloc_pair ();
	frame_draw (IMG_BFOOTLOGO);
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show2 ();
	task_sleep_sec (2);

	dmd_alloc_low_clean ();
	font_render_string_center (&font_var5, 64, 5, "PROGRAMMED IN");
	font_render_string_center (&font_var5, 64, 12, "FREEWPC AND");
	font_render_string_center (&font_var5, 64, 19, "RELEASED UNDER THE GNU");
	font_render_string_center (&font_var5, 64, 26, "GENERAL PUBLIC LICENSE.");
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show_low ();
	task_sleep_sec (1);

	dmd_alloc_low_clean ();
	font_render_string_center (&font_var5, 64, 5, "THANKS TO");
	font_render_string_center (&font_var5, 64, 12, "BCD");
	font_render_string_center (&font_var5, 64, 19, "JAMES C");
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show_low ();
	task_sleep_sec (1);

	dmd_alloc_low_clean ();
	font_render_string_center (&font_var5, 64, 5, "THANKS TO");
	font_render_string_center (&font_var5, 64, 12, "URBANLEDGE");
	font_render_string_center (&font_var5, 64, 19, "TOXIE");
	font_render_string_center (&font_var5, 64, 26, "FLUPPER1");
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show_low ();
	task_sleep_sec (1);

	dmd_alloc_pair ();
	frame_draw (IMG_BFOOTLOGO);
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show2 ();
	task_sleep_sec (2);

}

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
DELETED FROM CODE - DO NOT USE ANYMORE

mapmode search bigfoot
- qualified when map award given in cave, start in whirlpool

3-4-5-6-7 positions     
120 pixels /7 = 17 pixels wide 5 high each path
 */

#include <freewpc.h>
//#include <bigfhead.h>
#include "mapmode.h"


U8 map_shotcount;
U8 map_currentpos;
U8 map_goalpos;

void map_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean();
		frame_draw (IMG_MAPMODE);
		bitmap_blit (smcave_bits, (map_goalpos * 17 + 5) ,2);

		if (map_shotcount > 0)
		{
			bitmap_blit (smallx_bits, (map_currentpos * 17 + 5) , 120-(map_shotcount*5));
		}

		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}


void map_start (void)
{
	raftmode_off ();
//	bigfhead_go_front_cw ();
	speech_start (SND_WHICHWAYGO, SL_3S);
	deff_start_sync (DEFF_MAP_INTRO);
	task_sleep_sec (1);

	map_shotcount = 0;
	map_currentpos = 6;  // start in center

	map_goalpos = random_scaled(5) +1;  //rigged so we don't take extreme left or right corner

	lamplist_apply (LAMPLIST_HAZARDS, lamp_off);

	lamp_tristate_flash (LM_HZ_BOULDER_GARDEN);
	lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
	lamp_tristate_flash (LM_HZ_BOOM_BEND);

	flag_on (FLAG_MAPPLAYED);


//	task_sleep_sec (2);
	speech_start (SND_HERESMAP, SL_3S);
	task_sleep_sec (2);
	global_flag_on (GLOBAL_FLAG_MAP_RUNNING);
	speech_start (SND_HEADFORBLINKENLIGHT, SL_4S);
	task_sleep_sec (1);
//	global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
}

void map_stop (void)
{
	deff_stop (DEFF_MAP_RUNNING);

	lamp_tristate_off (LM_HZ_BOULDER_GARDEN);
	lamp_tristate_off (LM_HZ_NO_WAY_OUT);
	lamp_tristate_off (LM_HZ_BOOM_BEND);

//	bigfhead_go_back_cw ();

	global_flag_off (GLOBAL_FLAG_MAP_RUNNING);
	raftmode_on ();
}


void map_shotmade (U8 shot)
{
	U8 map_diff;
	map_shotcount++;
	if (shot == 1)
	{
		map_currentpos--;
//		bigfhead_bump_cw ();

	}
	else if (shot == 5)
	{
		map_currentpos++;
//		bigfhead_bump_ccw ();
	} 
	else if (shot == 3)
	{
		map_currentpos = map_currentpos + random_scaled(1);  //go random left/right
	}

	score_update_request ();

	if (map_shotcount == 5)
	{
		if (map_currentpos == map_goalpos)
		{
			sound_start (ST_SAMPLE, SND_OK_6, SL_3S, PRI_GAME_QUICK3);
			score (SC_1M);
			speech_start (SND_WWGOTHIM, SL_4S);
			task_sleep (TIME_500MS);
			deff_start (DEFF_MAP_FOUND);
		}
		else if (map_currentpos == 1)
		{
			sound_start (ST_SAMPLE, SND_COW, SL_3S, PRI_GAME_QUICK3);
			score (SC_1M);
			task_sleep (TIME_500MS);
			deff_start (DEFF_MAP_COW);
		}
		else
		{
			sound_start (ST_SAMPLE, SND_BAD_2, SL_3S, PRI_GAME_QUICK3);
			task_sleep (TIME_500MS);
		}
		map_stop ();
	}
	else
	{
		if (map_goalpos +1 >= map_currentpos)
		{
			map_diff = map_goalpos +2 - map_currentpos;
			if (map_diff <= 3)
				speech_start (SND_NICEMOVE, SL_3S);
			else
				speech_start (SND_RIGHTRIGHT, SL_3S);
		}
		else
			speech_start (SND_LEFTLEFT, SL_3S);
	}
}




CALLSET_ENTRY (map, left_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_MAP_RUNNING))
	{
		map_shotmade (1);
	}
}

CALLSET_ENTRY (map, dev_lock_enter)
{
	if (global_flag_test (GLOBAL_FLAG_MAP_RUNNING))
	{
		map_shotmade (3);
	}
}

CALLSET_ENTRY (map, sw_disas_drop_main)
{
	if (global_flag_test (GLOBAL_FLAG_MAP_RUNNING))
	{
		if (map_shotcount == 2)
			speech_start (SND_YWDISDROP, SL_4S);
	}
}

CALLSET_ENTRY (map, right_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_MAP_RUNNING))
	{
		map_shotmade (5);
	}
}

CALLSET_ENTRY (map, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_MAP_RUNNING))
		deff_start_bg (DEFF_MAP_RUNNING, 0);
}

CALLSET_ENTRY (map, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_MAP_RUNNING))
	{
		switch (map_shotcount)
		{
			case 0:
				music_request (MUS_HURRY_MODE3, PRI_GAME_MODE1 +3);
				break;
			case 1:
				music_request (MUS_HURRY_MODE4, PRI_GAME_MODE1 +3);
				break;
			case 2:
				music_request (MUS_HURRY_MODE5, PRI_GAME_MODE1 +3);
				break;
			case 3:
				music_request (MUS_HURRY_MODE6, PRI_GAME_MODE1 +3);
				break;
			case 4:
				music_request (MUS_HURRY_MODE7, PRI_GAME_MODE1 +3);
				break;
			case 5:
				music_request (MUS_HURRY_MODE8, PRI_GAME_MODE1 +3);
				break;
		}
	}
}


CALLSET_ENTRY (map, start_player)
{
	flag_off (FLAG_MAPPLAYED);	
	global_flag_off (GLOBAL_FLAG_MAP_RUNNING);

//x x x x x x x
// x x x x x x
//  x x x x x 
//   x x x x
//    x x x
}

CALLSET_ENTRY (map, end_ball, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_MAP_RUNNING))
	{
		sound_start (ST_SAMPLE, SND_BAD_2, SL_3S, PRI_GAME_QUICK3);
		map_stop ();
	}
}




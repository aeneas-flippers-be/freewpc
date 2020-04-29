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

/* wet willy wizard mode
wizard mode in 2 steps:
	first shoot 8 timed shots for each raft, similar to man overboard or stiff-o-meter
	when wetwilly reached again all hazards lit, shoot them to unlight and score jackpot

*/

#include <freewpc.h>
#include <timedmode.h>

#define WET_MODE_TIME 20
#define WET_MODE_ADDTIME 5


U8 wet_timer;
U8 wet_jackpot_level;
U8 wet_raftnr;
U8 wet_randomhz;

void wet_lamps_off (void)
{
	lamp_tristate_off (LM_WET_WILLIES);
	lamp_tristate_off (LM_RAFT_8);
	lamp_tristate_off (LM_RAFT_7);
	lamp_tristate_off (LM_RAFT_6);
	lamp_tristate_off (LM_RAFT_5);
	lamp_tristate_off (LM_RAFT_4);
	lamp_tristate_off (LM_RAFT_3);
	lamp_tristate_off (LM_RAFT_2);
	lamp_tristate_off (LM_RAFT_1);

}

void wet_lamp_update (void)
{
	switch (wet_raftnr)
	{
		case 1:
			lamp_tristate_flash (LM_RAFT_1);
			break;
		case 2:
			lamp_tristate_flash (LM_RAFT_2);
			break;
		case 3:
			lamp_tristate_flash (LM_RAFT_3);
			break;
		case 4:
			lamp_tristate_flash (LM_RAFT_4);
			break;
		case 5:
			lamp_tristate_flash (LM_RAFT_5);
			break;
		case 6:
			lamp_tristate_flash (LM_RAFT_6);
			break;
		case 7:
			lamp_tristate_flash (LM_RAFT_7);
			break;
		case 8:
			lamp_tristate_flash (LM_RAFT_8);
			break;
	}

	switch (wet_raftnr)
	{
		case 9:
			lamp_tristate_on (LM_RAFT_8);
		case 8:
			lamp_tristate_on (LM_RAFT_7);
		case 7:
			lamp_tristate_on (LM_RAFT_6);
		case 6:
			lamp_tristate_on (LM_RAFT_5);
		case 5:
			lamp_tristate_on (LM_RAFT_4);
		case 4:
			lamp_tristate_on (LM_RAFT_3);
		case 3:
			lamp_tristate_on (LM_RAFT_2);
		case 2:
			lamp_tristate_on (LM_RAFT_1);
			break;
	}

	if (flag_test (FLAG_HZ1LIT))
		lamp_tristate_on (LM_HZ_BOULDER_GARDEN);
	if (flag_test (FLAG_HZ2LIT))
		lamp_tristate_on (LM_HZ_SPINE_CHILLER);
	if (flag_test (FLAG_HZ3LIT))
		lamp_tristate_on (LM_HZ_NO_WAY_OUT);
	if (flag_test (FLAG_HZ4LIT))
		lamp_tristate_on (LM_HZ_DISDROP);
	if (flag_test (FLAG_HZ5LIT))
		lamp_tristate_on (LM_HZ_BOOM_BEND);
	if (flag_test (FLAG_HZ6LIT))
		lamp_tristate_on (LM_HZ_INSANITY_FALLS);
	if (flag_test (FLAG_HZ7LIT))
		lamp_tristate_on (LM_HZ_BIGFOOT_BLUFF);
}

void wet_jackpot_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "JACKPOT");

	printf_millions (wet_jackpot_level);

	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void wet_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();
		font_render_string_center (&font_var5, 64, 5, "WET WILLY");

//		sprintf_current_score ();
//		font_render_string (&font_var5, 2, 2, sprintf_buffer);

		if (wet_raftnr < 9)
		{
			font_render_string_center (&font_var5, 64, 27, "SHOOT LIT HAZARD");

			sprintf ("%d", wet_timer);
			font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		}
		else
			font_render_string_center (&font_var5, 64, 27, "SHOOT LIT HAZARDS");

		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}


void wet_score_jackpot (void)
{
	score_multiple (SC_1M, wet_jackpot_level);

	if (wet_jackpot_level > 8)
		speech_start (SND_JP, SL_2S);

	deff_start (DEFF_WET_JACKPOT);
	leff_start (LEFF_FL_WETWILLY);
}


void wet_lighthz (void)
{
	switch (wet_randomhz)
	{
		case 1:
			flag_on (FLAG_HZ1LIT);
			break;
		case 2:
			flag_on (FLAG_HZ2LIT);
			break;
		case 3:
			flag_on (FLAG_HZ3LIT);
			break;
		case 4:
			flag_on (FLAG_HZ4LIT);
			break;
		case 5:
			flag_on (FLAG_HZ5LIT);
			break;
		case 6:
			flag_on (FLAG_HZ6LIT);
			break;
		case 7:
			flag_on (FLAG_HZ7LIT);
			break;
	}
	wet_lamp_update ();
}

void wet_nextrandomhz (void)
{
	wet_randomhz = random_scaled(6) +1;
	wet_lighthz ();
}

void wet_mode_init (void)
{
	wet_raftnr = 1;
	wet_jackpot_level = 1;
	wet_nextrandomhz ();
	global_flag_off (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
	leff_start (LEFF_FL_WETWILLY);
//	lock_unlockball ();
}

void wet_mode_exit (void)
{
	global_flag_off (GLOBAL_FLAG_WET_RUNNING);
//	global_flag_off (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
	deff_stop (DEFF_WET_RUNNING);
	lamp_tristate_off (LM_WET_WILLIES);
	wet_lamps_off ();
	raft_reset ();
	raftmode_on ();
}


struct timed_mode_ops wet_mode = {
	DEFAULT_MODE,
	.init = wet_mode_init,
	.exit = wet_mode_exit,
/*	.music = MUS_HURRYUP_MANOVERB, */
/*	.deff_running = DEFF_WET_RUNNING, */
	.gid = GID_ET_MODE,
	.prio = PRI_GAME_MODE5,
	.init_timer = WET_MODE_TIME,
	.timer = &wet_timer,
	.grace_timer = 1,
	.pause = system_timer_pause,
};


void wet_start (void)
{
	raftmode_off ();
	wet_raftnr = 0;
	wet_lamps_off ();
	lamp_tristate_flash (LM_WET_WILLIES);
	deff_start_sync (DEFF_WET_INTRO);
//	task_sleep_sec (2);
	global_flag_on (GLOBAL_FLAG_WET_RUNNING);
	timed_mode_begin (&wet_mode);
}

void wet_lightallhz (void)
{
	flag_on (FLAG_HZ1LIT);
	flag_on (FLAG_HZ2LIT);
	flag_on (FLAG_HZ3LIT);
	flag_on (FLAG_HZ4LIT);
	flag_on (FLAG_HZ5LIT);
	flag_on (FLAG_HZ6LIT);
	flag_on (FLAG_HZ7LIT);
	wet_lamp_update ();
}



void wet_shotmade (U8 wetshot)
{

	switch (wetshot)
	{
		case 1:
			flag_off (FLAG_HZ1LIT);
			lamp_tristate_off (LM_HZ_BOULDER_GARDEN);
			break;
		case 2:
			flag_off (FLAG_HZ2LIT);
			lamp_tristate_off (LM_HZ_SPINE_CHILLER);
			break;
		case 3:
			flag_off (FLAG_HZ3LIT);
			lamp_tristate_off (LM_HZ_NO_WAY_OUT);
			break;
		case 4:
			flag_off (FLAG_HZ4LIT);
			lamp_tristate_off (LM_HZ_DISDROP);
			break;
		case 5:
			flag_off (FLAG_HZ5LIT);
			lamp_tristate_off (LM_HZ_BOOM_BEND);
			break;
		case 6:
			flag_off (FLAG_HZ6LIT);
			lamp_tristate_off (LM_HZ_INSANITY_FALLS);
			break;
		case 7:
			flag_off (FLAG_HZ7LIT);
			lamp_tristate_off (LM_HZ_BIGFOOT_BLUFF);
			break;
	}
	wet_score_jackpot ();

	if (wet_raftnr < 7)  /* timed mode shots, lights go out */
	{
		timed_mode_add (&wet_mode, WET_MODE_ADDTIME);
		bounded_increment (wet_raftnr, 9);
		wet_jackpot_level = wet_raftnr;
		wet_nextrandomhz ();
	}
	else if (wet_raftnr == 7)  /* shot 8 is always lock */
	{
		timed_mode_add (&wet_mode, WET_MODE_ADDTIME);
		wet_raftnr = 9;
		wet_jackpot_level = 9;
		wet_randomhz = 3;
		wet_lighthz ();
	}
	else if (wet_raftnr == 8)  /* hold ball, start new wave */
	{
//		global_flag_on (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
		timed_mode_end (&wet_mode);
		speech_start (SND_IAMWETWILLY, SL_4S);
		wet_jackpot_level = 9;
		wet_lightallhz ();
		wet_raftnr = 9;
//		global_flag_off (GLOBAL_FLAG_HOLD_LOCK_KICKOUT);
	}
	else
	{
		if (!flag_test (FLAG_HZ1LIT) &&	!flag_test (FLAG_HZ2LIT)
			&& !flag_test (FLAG_HZ3LIT) && !flag_test (FLAG_HZ4LIT)
			&& !flag_test (FLAG_HZ5LIT) && 	!flag_test (FLAG_HZ6LIT) && !flag_test (FLAG_HZ7LIT))
		{
			/* score something, restart regular modes */

			flag_on (FLAG_WETFINISHED);
			speech_start (SND_WEIRD1, SL_4S);
			deff_start (DEFF_WET_OK);

			timed_mode_end (&wet_mode);
		}
	}
}


CALLSET_ENTRY (wet, start_wetwilly)
{
	wet_start ();
}


CALLSET_ENTRY (wet, left_ramp_made)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING) && flag_test (FLAG_HZ2LIT))
	{
		speech_start (SND_FEMALE_YEAH2, SL_2S);
		wet_shotmade (2);
	}
}

//ALLSET_ENTRY (wet, dev_lock_enter)
/*{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING) && flag_test (FLAG_HZ3LIT))
	{
		speech_start (SND_FEMALE_YEAH3, SL_2S);
		wet_shotmade (3);
	}
}
*/

CALLSET_ENTRY (wet, sw_disas_drop_main)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING) && flag_test (FLAG_HZ4LIT))
	{
		speech_start (SND_FEMALE_YEAH4, SL_2S);
		wet_shotmade (4);
	}
}

CALLSET_ENTRY (wet, sw_rapids_main_ramp)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING) && flag_test (FLAG_HZ6LIT))
	{
		speech_start (SND_FEMALE_YEAH6, SL_2S);
		wet_shotmade (6);
	}
}

CALLSET_ENTRY (wet, sw_canyon_main)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING) && flag_test (FLAG_HZ7LIT))
	{
		speech_start (SND_FEMALE_YEAH1, SL_2S);
		wet_shotmade (7);
	}
}

CALLSET_ENTRY (wet, left_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING) && flag_test (FLAG_HZ1LIT))
	{
		speech_start (SND_FEMALE_YEAH1, SL_2S);
		wet_shotmade (1);
	}
}

CALLSET_ENTRY (wet, right_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING) && flag_test (FLAG_HZ5LIT))
	{
		speech_start (SND_FEMALE_YEAH5, SL_2S);
		wet_shotmade (5);
	}
}

/*
--ALLSET_ENTRY (wet, dev_lostmine_enter)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING) && !free_timer_test (TIM_WPOOL))
	{
		speech_start (SND_HOWDYFOLKS, SL_2S);
	}
}
*/

CALLSET_ENTRY (wet, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING))
		deff_start_bg (DEFF_WET_RUNNING, 0);
}

CALLSET_ENTRY (wet, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING))
	{
		switch (wet_raftnr)
		{
			case 0:
			case 1:
				music_request (MUS_RAFT1_2, PRI_GAME_MODE1 +8);
				break;
			case 2:
				music_request (MUS_RAFT2_2, PRI_GAME_MODE1 +8);
				break;
			case 3:
				music_request (MUS_RAFT3_2, PRI_GAME_MODE1 +8);
				break;
			case 4:
				music_request (MUS_RAFT4_2, PRI_GAME_MODE1 +8);
				break;
			case 5:
				music_request (MUS_RAFT5_2, PRI_GAME_MODE1 +8);
				break;
			case 6:
				music_request (MUS_RAFT6_2, PRI_GAME_MODE1 +8);
				break;
			case 7:
				music_request (MUS_RAFT7_2, PRI_GAME_MODE1 +8);
				break;
			case 8:
				music_request (MUS_RAFT8_2, PRI_GAME_MODE1 +8);
				break;
			default:
				music_request (MUS_RAFT9_2, PRI_GAME_MODE1 +8);
				break;
		}
	}
}

CALLSET_ENTRY (wet, end_ball)
{
	if (global_flag_test (GLOBAL_FLAG_WET_RUNNING))
	{
		timed_mode_end (&wet_mode);
		deff_start (DEFF_WET_NOK);
		serve_ball ();
	}
}


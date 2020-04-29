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
NOT USED ANYMORE DOES NOT WORK
RULES: this is a bit similar to manoverboard/mapmode
waterfall is shown on dmd, shooting left hazards moves you left, shooting right hzs moves you right
- get to the edge of the river in time

fall at 115 pix

*/

#include <freewpc.h>
#include "waterfall.h"


U8 fall_positionx;
U8 fall_positiony;
U8 fall_moveup;
U8 fall_movedown;

score_t fall_score;

sound_code_t fall_sounds[5] = {SND_SPLASH_1, SND_SPLASH_2, SND_SPLASH_3, SND_SPLASH_4, SND_SPLASH_5};


void fall_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_pair_clean ();
		frame_draw (IMG_FALL2);
		bitmap_blit (fallraft1_bits, fall_positionx, fall_positiony);

		sprintf_score (fall_score);
		font_render_string_left (&font_mono5, 2, 27, sprintf_buffer);

		dmd_show2 ();
		task_sleep (TIME_200MS);
		task_sleep (TIME_50MS);

		dmd_alloc_pair_clean ();
		frame_draw (IMG_FALL3);

		sprintf_score (fall_score);
		font_render_string_left (&font_mono5, 2, 27, sprintf_buffer);

		if (fall_moveup > 0)
		{
			bitmap_blit (fallraftl_bits, fall_positionx, --fall_positiony);
			fall_moveup--;
		}
		else if (fall_movedown > 0)
		{
			bitmap_blit (fallraftr_bits, fall_positionx, ++fall_positiony);
			fall_movedown--;
		}
		else
			bitmap_blit (fallraft2_bits, fall_positionx, fall_positiony);

		dmd_show2 ();
		task_sleep (TIME_200MS);
		task_sleep (TIME_50MS);
	}
}

void fall_ok_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 4, "RAFT SAVED");
	font_render_string_center (&font_var5, 64, 14, "SHORE REACHED");
	sprintf_score (fall_score);
	font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (2);
	deff_exit ();
}

void fall_shotmade (U8 shot)
{
	if (fall_positiony <= 8) // was ==
		sound_start (ST_SAMPLE, SND_NICEPEDDLPART, SL_3S, PRI_GAME_QUICK3);
	if (fall_positiony >= 21) // was == 
		sound_start (ST_SAMPLE, SND_GOODGOINGPART, SL_3S, PRI_GAME_QUICK3);
	else
		sound_start (ST_SAMPLE, fall_sounds[random_scaled (5)], SL_3S, PRI_GAME_QUICK3);

	fall_positionx++;
	score_sub (fall_score, score_table[SC_20K]);


	switch (shot)
	{
		case 1:
			fall_moveup = 2;
			break;
		case 2:
			fall_moveup = 1;
			break;
		case 4:
			fall_movedown = 1;
			break;
		case 5:
			fall_movedown = 2;
			break;
	}
}

void fall_stop (void)
{
	global_flag_off (GLOBAL_FLAG_FALL_RUNNING);

	task_kill_gid (GID_FALL);
	deff_stop (DEFF_FALL_RUNNING);

	raft_hz_lamps_tri_off ();

	raftmode_on ();
}


void fall_checkend (void)
{
	if (fall_positiony < 6 || fall_positiony > 23)
	{
		task_kill_gid (GID_FALL);
		deff_start (DEFF_FALL_OK);
		score_long (fall_score);
		sound_start (ST_SAMPLE, SND_OKNICE, SL_3S, PRI_GAME_QUICK3);
		fall_stop ();
	}
	else if (fall_positionx > 110)	//off fall
	{
		deff_start (DEFF_FALL_NOK);
		sound_start (ST_SAMPLE, SND_ROCK_WATER, SL_3S, PRI_GAME_QUICK3);
		fall_stop ();
	} 
	else if (fall_positionx == 50)
		sound_start (ST_SAMPLE, SND_DOG1, SL_3S, PRI_GAME_QUICK3);
	else if (fall_positionx == 85)
		sound_start (ST_SAMPLE, SND_WWHELP, SL_3S, PRI_GAME_QUICK3);
	else if (fall_positionx == 105)
		sound_start (ST_SAMPLE, SND_YAWIENER, SL_3S, PRI_GAME_QUICK3);
}

void fall_timer_task (void)
{
	for (;;) 
	{
		task_sleep_sec (1);
		fall_positionx++;
		score_sub (fall_score, score_table[SC_10K]);
		fall_checkend ();
	}
}


void fall_start (void)
{
	raftmode_off ();

	fall_positionx = 5; //was 2
	fall_positiony = 14;
	fall_moveup = 0;
	fall_movedown = 0;

	score_zero (fall_score);
	score_add (fall_score, score_table[SC_10M]);

	global_flag_on (GLOBAL_FLAG_FALL_RUNNING);

	lamp_tristate_flash (LM_HZ_BOULDER_GARDEN);
	lamp_tristate_flash (LM_HZ_SPINE_CHILLER);
	lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
	lamp_tristate_flash (LM_HZ_DISDROP);
	lamp_tristate_flash (LM_HZ_BOOM_BEND);

	task_sleep_sec (2);
	task_create_gid1 (GID_FALL, fall_timer_task);
}



CALLSET_ENTRY (fall, left_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_FALL_RUNNING))
	{
		fall_shotmade (1);
	}
}

CALLSET_ENTRY (fall, left_ramp_made)
{
	if (global_flag_test (GLOBAL_FLAG_FALL_RUNNING))
	{
		fall_shotmade (2);
	}
}

//ALLSET_ENTRY (fall, dev_lock_enter)
/*{
	if (global_flag_test (GLOBAL_FLAG_FALL_RUNNING))
	{
		fall_shotmade (3);
	}
}
*/

CALLSET_ENTRY (fall, sw_disas_drop_main)
{
	if (global_flag_test (GLOBAL_FLAG_FALL_RUNNING))
	{
		fall_shotmade (4);
	}
}

CALLSET_ENTRY (fall, right_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_FALL_RUNNING))
	{
		fall_shotmade (5);
	}
}


CALLSET_ENTRY (fall, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_FALL_RUNNING))
	{
		deff_start_bg (DEFF_FALL_RUNNING, 0);
	}
}

CALLSET_ENTRY (fall, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_FALL_RUNNING))
	{
		music_request (MUS_MANOVERB_2, PRI_GAME_MODE1 +3);
	}
}

CALLSET_ENTRY (fall, end_ball, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_FALL_RUNNING))
	{
		fall_stop ();
	}
}

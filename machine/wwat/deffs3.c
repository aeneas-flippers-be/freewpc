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
//#include "deffs3.h"

extern U8 gold_hitcount;
extern score_t gold_score;

extern U8 wpch_jackpots_made;

extern U8 mmil_count;

extern U8 qmb_jp_mul;

extern U8 riverclass; 

extern U8 shots_falls;

extern U8 skill_ramp_made;
extern U8 skill_bigf_made;
extern U8 skill_count;



//this will take what's in the sprinf_buffer (only 1 line !!!) and flash it
//will not flash what was on the dmd if there were more lines
void flash_and_exit_deff (U8 flash_count, task_ticks_t flash_delay)
{
	dmd_alloc_pair ();
	dmd_clean_page_low ();
	font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
	dmd_show_low ();
	dmd_copy_low_to_high ();
	dmd_invert_page (dmd_low_buffer);
	deff_swap_low_high (flash_count, flash_delay);
	deff_exit ();
}


void extra_ball_deff (void)
{
	sound_start (ST_SAMPLE, SND_EXTRABALL, SL_3S, PRI_GAME_QUICK1);
	sprintf ("EXTRA BALL");
	flash_and_exit_deff (20, TIME_100MS);
}

void extra_ball_lit_deff (void)
{
	sound_start (ST_SAMPLE, SND_EXTRABALL, SL_3S, PRI_GAME_QUICK1);
	sprintf ("EXTRA BALL LIT");
	flash_and_exit_deff (20, TIME_100MS);
}

void riverclass_deff (void)
{
	dmd_alloc_low_clean ();

	sprintf ("RIVERCLASS %d", riverclass);
	font_render_string_center (&font_fixed6, 64, 10, sprintf_buffer);

	sprintf("JETS SCORE %dK", riverclass * 20);
	font_render_string_center (&font_var5, 64, 24, sprintf_buffer);

	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void jackpot_deff (void)
{
	sprintf ("JACKPOT");
	flash_and_exit_deff (20, TIME_100MS);
}

void bigfoot_jackpot_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 12, "BIGFOOT");
	font_render_string_center (&font_fixed6, 64, 22, "JACKPOT");

	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void mb_intro_deff (void)
{
	sprintf ("MULTIBALL");
	flash_and_exit_deff (30, TIME_100MS);
}

void mb_running_deff (void)
{
	for (;;)
	{
		score_update_start ();
		dmd_alloc_pair ();
		dmd_clean_page_low ();
		sprintf_current_score ();
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		font_render_string_center (&font_var5, 64, 27, "SHOOT FALLS");
		dmd_copy_low_to_high ();
		font_render_string_center (&font_fixed6, 64, 4, "MULTIBALL");
		dmd_show_low ();
		do
		{
			task_sleep (TIME_133MS);
			dmd_show_other ();
			task_sleep (TIME_133MS);
			dmd_show_other ();
		} while (!score_update_required ());
	}
}

void mb_restart_deff (void)
{
	for (;;)
	{
		//fixed6 is too big
		dmd_alloc_low_clean ();
		font_render_string_center (&font_var5, 64, 10, "SHOOT NO WAY OUT");
		font_render_string_center (&font_var5, 64, 21, "TO RESTART MB");
		dmd_show_low ();
		task_sleep (TIME_500MS);
	}
//	task_sleep_sec (1);
	deff_exit ();
}

void mb_relocked_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "BALL RELOCKED");
	font_render_string_center (&font_fixed6, 64, 21, "MB RESTART");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}


void lock_lit_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "LOCK IS LIT");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void lock_lock1_deff (void)
{
	dmd_alloc_low_clean ();
//	sprintf ("BALL 1 LOCKED");
//	font_render_string_center (&font_fixed6, 64, 7, sprintf_buffer);
	font_render_string_center (&font_fixed6, 64, 16, "BALL 1 LOCKED");
	dmd_show_low ();
	sound_start (ST_SAMPLE, SND_LOCK_1, SL_1S, PRI_GAME_QUICK3);
	task_sleep_sec (3);
	deff_exit ();
}

void lock_lock2_deff (void)
{
	dmd_alloc_low_clean ();
//	sprintf ("BALL 2 LOCKED");
//	font_render_string_center (&font_fixed6, 64, 7, sprintf_buffer);
	font_render_string_center (&font_fixed6, 64, 16, "BALL 2 LOCKED");
	dmd_show_low ();
	sound_start (ST_SAMPLE, SND_LOCK_2, SL_1S, PRI_GAME_QUICK3);
	task_sleep_sec (3);
	deff_exit ();
}

void lock_lock3_deff (void)
{
	dmd_alloc_low_clean ();
//	sprintf ("BALL 3 LOCKED");
//	font_render_string_center (&font_fixed6, 64, 7, sprintf_buffer);
	font_render_string_center (&font_fixed6, 64, 16, "BALL 3 LOCKED");
	dmd_show_low ();
	sound_start (ST_SAMPLE, SND_LOCK_3, SL_1S, PRI_GAME_QUICK3);
	task_sleep_sec (3);
	deff_exit ();
}

void wpch_intro_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10,"WHIRLPOOL");
	font_render_string_center (&font_fixed6, 64, 21, "CHALLENGE");
	dmd_show_low ();
	task_sleep_sec (2);
	deff_exit ();
}

void wpch_running_deff (void)
{
	for (;;)
	{
		score_update_start ();
		dmd_alloc_pair ();
		dmd_clean_page_low ();
		sprintf_current_score ();
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		font_render_string_center (&font_var5, 64, 27, "SHOOT WHIRLPOOL");
		dmd_copy_low_to_high ();
		font_render_string_center (&font_fixed6, 64, 4, "WPOOL MBALL");
		dmd_show_low ();
		do
		{
			task_sleep (TIME_133MS);
			dmd_show_other ();
			task_sleep (TIME_133MS);
			dmd_show_other ();
		} while (!score_update_required ());
	}
}

void wpch_jackpot_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "JACKPOT");
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
		sprintf("%d MILLION", wpch_jackpots_made * 5);
	else
		sprintf("%d MILLION", wpch_jackpots_made);

	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void wpch_jackpot6_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "FULL");
	font_render_string_center (&font_fixed6, 64, 21, "WHIRLPOOL");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void mmilcollected_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "MULTI MILION");
	if (global_flag_test (GLOBAL_FLAG_WP5X_RUNNING))
		sprintf("%d MILLION", mmil_count * 5);
	else
		sprintf("%d MILLION", mmil_count);
	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void qmb_intro_deff (void)
{
	sound_start (ST_SAMPLE, SND_BOWLINGBALL, SL_3S, PRI_GAME_QUICK1);
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "QUICK MB");
	dmd_show_low ();

	task_sleep_sec (1);
	deff_exit ();
}

void qmb_running_deff (void)
{
	for (;;)
	{
		score_update_start ();
		dmd_alloc_pair ();
		dmd_clean_page_low ();
		sprintf_current_score ();
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		sprintf("HAZARDS NOW %dK", qmb_jp_mul * 10);
		font_render_string_center (&font_var5, 64, 27, sprintf_buffer);
		dmd_copy_low_to_high ();
		font_render_string_center (&font_fixed6, 64, 4, "QUICK MB");
		dmd_show_low ();
		do
		{
			task_sleep (TIME_133MS);
			dmd_show_other ();
			task_sleep (TIME_133MS);
			dmd_show_other ();
		} while (!score_update_required ());
	}
}

void qmb_up_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "QUICK MB");
	sprintf("HAZARDS NOW %dK", qmb_jp_mul * 10);
	font_render_string_center (&font_var5, 64, 27, sprintf_buffer);
	dmd_show_low ();

	task_sleep_sec (1);
	deff_exit ();
}


void gold_running_deff (void)
{
	for (;;)
	{
		score_update_start ();
		dmd_alloc_pair ();
		dmd_clean_page_low ();

//		sprintf_current_score ();
		sprintf_score (gold_score);
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		sprintf("%d GOLD HIT", gold_hitcount);
		font_render_string_center (&font_var5, 64, 27, sprintf_buffer);

		dmd_copy_low_to_high ();
		font_render_string_center (&font_fixed6, 64, 4, "GOLDRUSH");
		dmd_show_low ();
		do
		{
			task_sleep (TIME_133MS);
			dmd_show_other ();
			task_sleep (TIME_133MS);
			dmd_show_other ();
		} while (!score_update_required ());
	}
}



void wpm_enter_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "ENTER");
	font_render_string_center (&font_fixed6, 64, 21, "WHIRLPOOL");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void wpm_dirty_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "DIRTY");
	font_render_string_center (&font_fixed6, 64, 21, "POOL");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void wet_qual_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "WET WILLY LIT");
	font_render_string_center (&font_fixed6, 64, 21, "SHOOT LOCK");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void wet_intro_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "WET WILLY");
	dmd_show_low ();
	speech_start (SND_WELCOMEWETWILLYS, SL_4S);
	flash_and_exit_deff (20, TIME_100MS); 
//	task_sleep_sec (3);
//	deff_exit ();
}

void wet_ok_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "WET WILLY");
	font_render_string_center (&font_fixed6, 64, 21, "COMPLETED");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void wet_nok_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "WET WILLY");
	font_render_string_center (&font_fixed6, 64, 21, "FAILED");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void lostmine_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "LOST MINE");
	font_render_string_center (&font_fixed6, 64, 21, "FOUND");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}


void wp5xpf_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();
		font_render_string_center (&font_var5, 64, 5, "5X SCORE");
		sprintf_current_score ();
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}


void wp5xpf_running2_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();
		font_render_string_center (&font_var5, 64, 5, "COLLECT HAZARDS");
		sprintf_current_score ();
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		font_render_string_center (&font_var5, 64, 24, "UP TO 5M EACH");
		dmd_show_low ();
		task_sleep (TIME_200MS);
	}
}

void riverletter_deff (void)
{

	dmd_alloc_pair ();
	dmd_clean_page_low ();
	font_render_string_center (&font_fixed10, 32, 12, "R");
	font_render_string_center (&font_fixed10, 48, 12, "I");
	font_render_string_center (&font_fixed10, 64, 12, "V");
	font_render_string_center (&font_fixed10, 80, 12, "E");
	font_render_string_center (&font_fixed10, 96, 12, "R");
	dmd_flip_low_high ();

	dmd_clean_page_low ();
	if (global_flag_test (GLOBAL_FLAG_RIVERR1))
		font_render_string_center (&font_fixed10, 32, 12, "R");
	if (global_flag_test (GLOBAL_FLAG_RIVERI))
		font_render_string_center (&font_fixed10, 48, 12, "I");
	if (global_flag_test (GLOBAL_FLAG_RIVERV))
		font_render_string_center (&font_fixed10, 64, 12, "V");
	if (global_flag_test (GLOBAL_FLAG_RIVERE))
		font_render_string_center (&font_fixed10, 80, 12, "E");
	if (global_flag_test (GLOBAL_FLAG_RIVERR2))
		font_render_string_center (&font_fixed10, 96, 12, "R");

	dmd_flip_low_high ();
	dmd_show2 ();
	task_sleep_sec (2);
	deff_exit ();
}

void river_complete_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "RIVER COMPLETE");
	font_render_string_center (&font_fixed6, 64, 21, "WPOOL LIT");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void combo_drop_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "3 WAY DROP");

	printf_millions (1);
	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void combo_rloop_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "BOULDER LOOP");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void combo3_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "3 WAY COMBO");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void combo4_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "4 WAY COMBO");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void map_intro_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "FIND BIGFOOT");
	font_render_string_center (&font_var5, 64, 21, "MAKE CORRECT SHOTS");
	dmd_show_low ();

	dmd_alloc_pair ();
	frame_draw (IMG_MAPINTRO);
	dmd_sched_transition (&trans_scroll_up_slow);
	dmd_show2 ();

	task_sleep (TIME_200MS);
	deff_exit ();

}

void map_found_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "BIGFOOT FOUND");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void map_cow_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 12, "COW FOUND");
	printf_millions (1);
	font_render_string_center (&font_fixed6, 64, 26, sprintf_buffer);

	dmd_show_low ();
	task_sleep_sec (2);
	deff_exit ();
}

void wiz_intro_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "WIZARD MB");
	dmd_show_low ();
//	task_sleep_sec (1);
//	deff_exit ();
	flash_and_exit_deff (30, TIME_100MS);
}

void wiz_mb_running_deff (void)
{
	for (;;)
	{
		score_update_start ();
		dmd_alloc_pair ();
		dmd_clean_page_low ();
		sprintf_current_score ();
		font_render_string_center (&font_fixed6, 64, 16, sprintf_buffer);
		font_render_string_center (&font_var5, 64, 27, "SHOOT HAZARDS");
		dmd_copy_low_to_high ();
		font_render_string_center (&font_fixed6, 64, 4, "WIZARD MB");
		dmd_show_low ();
		do
		{
			task_sleep (TIME_133MS);
			dmd_show_other ();
			task_sleep (TIME_133MS);
			dmd_show_other ();
		} while (!score_update_required ());
	}
}

void hz1_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "BOULDER GARDEN");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void hz2_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "SPINE CHILLER");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}


void hz4_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "SPINE CHILLER");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void hz5_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "BOOMERANG BEND");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void hz6_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "INSANITY FALLS");
	sprintf ("%d FALLS", shots_falls);
	font_render_string_center (&font_var5, 64, 20, sprintf_buffer);

	//ramp scores 50K * skillshot made
	if (skill_ramp_made > 1)
	{
		sprintf ("%dK", skill_ramp_made *50);
		font_render_string_center (&font_var5, 64, 28, sprintf_buffer);
	}

	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void hz7_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "BIGFOOT");
	if (skill_bigf_made > 1)
	{
		sprintf ("%dK", skill_bigf_made *50);
		font_render_string_center (&font_var5, 64, 28, sprintf_buffer);
	}
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void secret_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "SECRET PASSAGE");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void skill_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();
		font_render_string_center (&font_fixed6, 64, 4, "SKILL SHOT");
		font_render_string_center (&font_var5, 64, 18, "SHOOT UPPER RAMPS");
		font_render_string_center (&font_var5, 64, 26, "FOR JACKPOT");
		dmd_show_low ();
		task_sleep_sec (1);
/*  quickmb removed TODO cleanup
		dmd_alloc_low_clean ();
		font_render_string_center (&font_fixed6, 64, 4, "SKILL SHOT");
		font_render_string_center (&font_var5, 64, 18, "SHOOT NO WAY OUT");
		font_render_string_center (&font_var5, 64, 26, "FOR QUICK MULTIBALL");
		dmd_show_low ();
		task_sleep_sec (1);
*/
		}
}

void skill_ramp_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 4, "SKILL SHOT");
	
	if (skill_count == 9)
		printf_millions (20);
	else
		printf_millions (skill_count * 2);
	
	font_render_string_center (&font_fixed6, 64, 14, sprintf_buffer);
	sprintf ("FALLS NOW %dK", skill_ramp_made *50);
	font_render_string_center (&font_var5, 64, 24, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void skill_bigf_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 4, "SKILL SHOT");
	printf_millions (skill_bigf_made -1);
	font_render_string_center (&font_fixed6, 64, 14, sprintf_buffer);
	sprintf ("BIGFOOT NOW %dK", skill_bigf_made *50);
	font_render_string_center (&font_var5, 64, 24, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

/* void fall_nok_de-- (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "OVER FALLS");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}
*/

void wpmano_intro_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "MAN OVERBOARD");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void wp5x_intro_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 16, "5M HAZARD MODE");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void eb_score_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 14, "EXTRA BALL");
	font_render_string_center (&font_var5, 64, 26, "1 M");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void dam_ok_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 14, "BROKE DAM");
	font_render_string_center (&font_var5, 64, 26, "10 M");
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}



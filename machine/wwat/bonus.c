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

#include <freewpc.h>

extern U8 shots_falls;
extern U8 shots_secretpass;

extern U8 gold_hitcount;

//extern U8 raft_perfectcount;
extern U8 raftnr;

extern U8 riverclass;

extern U8 jets_extra_hit;

extern U8 combos_nrdrops;
extern U8 combos_nrrloops;
extern U8 combos_3made;
extern U8 combos_4made;

extern U8 hurry_counter;

extern U8 caveshots;
extern U8 lostmine_nrshot;




/* Total bonus score */
score_t total_bonus;
/* Temp variable used to calculate bonus per door/loop etc */
score_t bonus_scored;

bool buttons_held;



/* Speed up the bonus if both flipper buttons are pressed */
static void bonus_button_monitor (void)
{
	buttons_held = FALSE;
	for (;;)
	{
		if ((switch_poll_logical (SW_LEFT_BUTTON) 
			&& switch_poll_logical (SW_RIGHT_BUTTON)) 
			&& buttons_held == FALSE)
		{	
			buttons_held = TRUE;
		}
		task_sleep (TIME_100MS);
	}
}

static void bonus_pause (void)
{
	if (buttons_held)
		task_sleep (TIME_100MS);
	else
		task_sleep_sec (1);
}

static void bonus_sched_transition (void)
{
	if (buttons_held == TRUE)
		dmd_sched_transition (&trans_scroll_down_fast);
	else
		dmd_sched_transition (&trans_scroll_down);
}



void bonus_deff (void)
{
//	task_sleep (TIME_100MS);

	/* Clear the bonus score */
	score_zero (total_bonus);

	/* Show Initial bonus screen */
/*	sample_start (MUS_FADE_BONUS, SL_500MS); */
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed10, 64, 16, "BONUS");
	dmd_sched_transition (&trans_bitfade_fast);
	dmd_show_low ();
	task_sleep_sec (1);

	task_recreate_gid (GID_BONUS_BUTTON_MONITOR, bonus_button_monitor);

	if (raftnr > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_100K]);
		score_mul (bonus_scored, raftnr); 
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("RAFT NUMBER");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 100,000", raftnr);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING1, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}

/*	if (raft_perfectcount > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_1M]);
		score_mul (bonus_scored, raft_perfectcount); 
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("PERFECT RAFTS");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 1,000,000", raft_perfectcount);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING1, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}
*/

	if (hurry_counter > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_100K]);
		score_mul (bonus_scored, hurry_counter); 
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("HURRY UP RIVER");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 100,000", hurry_counter);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING1, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}


	if (shots_secretpass > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_250K]);
		score_mul (bonus_scored, shots_secretpass); 
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("SECRET PASSAGE");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 250,000", shots_secretpass);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING1, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}

	if (shots_falls > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_20K]);
		score_mul (bonus_scored, shots_falls); 
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("INSANITY FALLS");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 20,000", shots_falls);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING2, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}

	if (caveshots > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_20K]);
		score_mul (bonus_scored, caveshots); 
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("CAVE VISITS");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 20,000", caveshots);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING3, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}


	if (lostmine_nrshot > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_20K]);
		score_mul (bonus_scored, lostmine_nrshot); 
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("LOST MINE");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 20,000", lostmine_nrshot);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING3, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}


	if (combos_nrdrops > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_20K]);
		score_mul (bonus_scored, combos_nrdrops);
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("DISASTER COMBOS");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 20,000", combos_nrdrops);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING4, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}

	if (combos_nrrloops > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_20K]);
		score_mul (bonus_scored, combos_nrrloops);
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("BOULDER LOOPS");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 20,000", combos_nrrloops);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING1, SL_1S, PRI_GAME_QUICK3);
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		bonus_pause ();
	}

	if (combos_3made > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_20K]);
		score_mul (bonus_scored, combos_3made);
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("TRIPLE COMBOS");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 20,000", combos_3made);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING2, SL_1S, PRI_GAME_QUICK3);
		bonus_pause ();
	}

	if (combos_4made > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_25K]);
		score_mul (bonus_scored, combos_4made);
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("QUAD COMBOS");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 25,000", combos_4made);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING3, SL_1S, PRI_GAME_QUICK3);
		bonus_pause ();
	}

	if (jets_extra_hit > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_20K]);
		score_mul (bonus_scored, jets_extra_hit);
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("BOULDER AREA");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 20,000", jets_extra_hit);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING4, SL_1S, PRI_GAME_QUICK3);
		bonus_pause ();
	}

	if (gold_hitcount > 0)
	{
		dmd_alloc_low_clean ();
		score_zero (bonus_scored);
		score_add (bonus_scored, score_table[SC_25K]);
		score_mul (bonus_scored, gold_hitcount);
		score_add (total_bonus, bonus_scored);
		sprintf_score (bonus_scored);
		font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
		sprintf ("GOLD HITS");
		font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
		sprintf ("%d X 25,000", gold_hitcount);
		font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
		bonus_sched_transition ();
		dmd_show_low ();
		sound_start (ST_SAMPLE, SND_BONUSTING4, SL_1S, PRI_GAME_QUICK3);
		bonus_pause ();
	}


	if (riverclass > 1)
	{
		U8 i;
		for (i = 2; i <= riverclass; i++)
		{
			dmd_alloc_low_clean ();
			score_zero (bonus_scored);
			score_add (bonus_scored, total_bonus);
			sprintf_score (bonus_scored);
			font_render_string_center (&font_fixed10, 64, 16, sprintf_buffer);
			sprintf ("RIVER CLASS");
			font_render_string_center (&font_mono5, 64, 4, sprintf_buffer);
			sprintf ("%d X BONUS", (i));
			font_render_string_center (&font_mono5, 64, 26, sprintf_buffer);
			bonus_sched_transition ();
			dmd_show_low ();

			if (buttons_held)
				task_sleep (TIME_100MS);
			else
			{
				switch (i)
				{
					case 3:
						sound_start (ST_SAMPLE, SND_BONUSTING1, SL_1S, PRI_GAME_QUICK3);
						break;
					case 4:
						sound_start (ST_SAMPLE, SND_BONUSTING2, SL_1S, PRI_GAME_QUICK3);
						break;
					case 5:
						sound_start (ST_SAMPLE, SND_BONUSTING3, SL_1S, PRI_GAME_QUICK3);
						break;
					case 6:
						sound_start (ST_SAMPLE, SND_BONUSTING4, SL_1S, PRI_GAME_QUICK3);
						break;
				}
				task_sleep (TIME_400MS);
			}
		}
		score_add (total_bonus, bonus_scored);
	}

	task_kill_gid (GID_BONUS_BUTTON_MONITOR);

	score_long (total_bonus);

	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 6, "TOTAL BONUS");
	sprintf_score (total_bonus);
	font_render_string_center (&font_fixed10, 64, 24, sprintf_buffer);
	dmd_show_low ();	

	task_sleep_sec (2);
	deff_exit ();
}

void endgame_deff (void)
{
	dmd_alloc_pair ();
	frame_draw (IMG_FLIPLOGO);
	dmd_show2 ();
	task_sleep_sec (2);
	deff_exit ();
}


CALLSET_ENTRY (bonus, bonus)
{
	deff_start_sync (DEFF_BONUS);
//	task_sleep_sec (1);
//	while (deff_get_active () == DEFF_BONUS)
//		task_sleep (TIME_500MS);
}

//-ALLSET_ENTRY (bonus, music_refresh)
//{
//	if (deff_get_active () == DEFF_BONUS)
//		music_request (MUS_MODE_SLOW_1, PRI_GAME_MODE1 +3);
//	if (deff_get_active () == DEFF_ENDGAME)
//		music_request (SND_GAMEOVER, PRI_GAME_MODE1 +3);
//}


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

U8 combos_shots;

__local__ U8 combos_nrdrops;
__local__ U8 combos_nrrloops;
__local__ U8 combos_3made;
__local__ U8 combos_4made;

void combos_stop (void)
{
	combos_shots = 0;
	free_timer_stop (TIM_DISDROP_LOOP);
	free_timer_stop (TIM_COMBOS);
	free_timer_stop (TIM_RLOOP_COMBO);
	lamp_off (LM_LIGHT_SPINE);
}

void combos_scoredrop (void)
{
	leff_start (LEFF_HZ_DISDROP);
	if (combos_nrdrops == 3)
	{
		raft_award_hazard ();
	} 
	if (combos_nrdrops % 3 == 0)
	{
		score (SC_1M);
		sound_start (ST_SAMPLE, SND_OK_3, SL_3S, PRI_GAME_QUICK3);
		deff_start (DEFF_COMBO_DROP);
	}
}

void combos_scorerloop (void)
{
	sound_start (ST_SAMPLE, SND_OK_3, SL_3S, PRI_GAME_QUICK3);
	deff_start (DEFF_COMBO_RLOOP);
	score (SC_250K);
}

void combos_score_combo (U8 combonr)
{
	score (SC_250K);
	switch (combonr)
	{
		case 3:
			bounded_increment (combos_3made, 255);
			sound_start (ST_SAMPLE, SND_OK_3, SL_3S, PRI_GAME_QUICK3);
			deff_start (DEFF_COMBO3);
			break;
		case 4:
			bounded_increment (combos_4made, 255);
			sound_start (ST_SAMPLE, SND_OK_4, SL_3S, PRI_GAME_QUICK3);
			deff_start (DEFF_COMBO4);
			break;
	}
}


CALLSET_ENTRY (combos, sw_rapids_main_ramp)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ6LIT))
	{
		combos_stop ();
		return;
	}

	if (combos_shots == 1)
		combos_shots = 2;

	if (combos_shots == 3)
	{
		combos_shots = 2;
		combos_score_combo (4);
	}
}


// start of all combos and then rapidsmainramp
CALLSET_ENTRY (combos, left_ramp_made)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ2LIT) || flag_test (FLAG_HZ6LIT))
	{
		combos_stop ();
		return;
	}

	lamp_on (LM_LIGHT_SPINE);
	if (combos_shots == 2)
		combos_shots = 3;
	else
		combos_shots = 1;
}


/* only as 3rd shot and then end combo */
CALLSET_ENTRY (combos, dev_lock_enter)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (!flag_test (FLAG_HZ3LIT) && combos_shots == 2)
	{
		combos_score_combo (3);
	}
	combos_stop ();
}

CALLSET_ENTRY (combos, right_loop_made)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (!flag_test (FLAG_HZ5LIT) && combos_shots == 2)
	{
		combos_score_combo (3);
	}
	combos_stop ();

	if (free_timer_test (TIM_RLOOP_COMBO))
	{
		bounded_increment (combos_nrrloops, 255);
		combos_scorerloop ();
	}
	free_timer_restart (TIM_RLOOP_COMBO, TIME_4S);

}

CALLSET_ENTRY (combos, sw_disas_drop_main)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

//	free_timer_stop (TIM_RLOOP_COMBO);

	if (!flag_test (FLAG_HZ4LIT) && combos_shots == 2)
	{
		combos_score_combo (3);
	}
	combos_stop ();

	if (free_timer_test (TIM_DISDROP_LOOP))
	{
		bounded_increment (combos_nrdrops, 255);
		combos_scoredrop ();
	}
	free_timer_restart (TIM_DISDROP_LOOP, TIME_4S);
}


CALLSET_ENTRY (combos, sw_3bank_top, sw_3bank_center, sw_3bank_bottom, sw_2bank_low, sw_2bank_up, sw_river_r1, sw_river_r2, sw_river_i, sw_river_v, sw_river_e, sw_lock_left, sw_lock_right, sw_jet, dev_lostmine_enter, sw_canyon_entrance, left_loop_made, end_ball)
{
	if (!in_live_game || !global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;
	combos_stop ();
}

CALLSET_ENTRY (combos, start_ball)
{
	combos_shots = 0;
}

CALLSET_ENTRY (combos, start_player)
{
	combos_nrdrops = 0;
	combos_3made = 0;
	combos_4made = 0;
	combos_nrrloops = 0;
}


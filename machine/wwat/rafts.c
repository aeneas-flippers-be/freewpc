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
Shoot lit hazards to progress raft until wet willy

*/

#include <freewpc.h>

__local__ U8 raftnr;
__local__ U8 raftmode;
__local__ U8 raft_perfectcount;

U8 raft_randomhz;
U8 raft_random;
U8 raft_perfect;


void raft_perfect_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "PERFECT PATH");

	printf_millions (raftnr *2);

	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void raft_up_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "NEXT RAFT");

	printf_millions (raftnr);

	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}


void raft_hz_reset (void)
{
	flag_off (FLAG_HZ1LIT);
	flag_off (FLAG_HZ2LIT);
	flag_off (FLAG_HZ3LIT);
	flag_off (FLAG_HZ4LIT);
	flag_off (FLAG_HZ5LIT);
	flag_off (FLAG_HZ6LIT);
	flag_off (FLAG_HZ7LIT);

	lamplist_apply (LAMPLIST_HAZARDS, lamp_off);
}

void raft_reset (void)
{
	raftnr = 1;
	raftmode = 1;
	raft_perfect = 2;
	raft_hz_reset ();

	lamplist_apply (LAMPLIST_RAFTS, lamp_off);
}

void raft_lighthaz (U8 nexthz)
{
	switch (nexthz)
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
}


void raft_next2rafts (void)
{
	raft_randomhz = random_scaled(6) + 1;
	raft_random = random_scaled(3) + 1;

	raft_lighthaz (raft_randomhz);

	if (raft_randomhz > 4)
		raft_randomhz = raft_randomhz - raft_random;
	else 
		raft_randomhz = raft_randomhz + raft_random;

	raft_lighthaz (raft_randomhz);
}

void raft_award (void)
{
	score_multiple (SC_1M, raftnr * raft_perfect);

	raftnr++;
	raftmode = 1;
	
	if (raftnr < 8)
	{
		sound_start (ST_SAMPLE, SND_OK_1, SL_3S, PRI_GAME_QUICK3);
		if (raft_perfect == 2)
		{
			raft_perfectcount++;
			deff_start (DEFF_RAFT_PERFECT);

			if (raft_perfectcount == 2)
				flag_on (FLAG_DAM_LIT);
		}
//		else
//			deff_start (DEFF_RAFT_UP);

//		raftnr++;
//		raftmode = 1;
		raft_next2rafts ();
		hurry_stop ();
		hurry_start ();
	}
	else
	{
		raft_hz_reset ();
		deff_start (DEFF_WET_QUAL);
		speech_start (SND_WWHOWDYFOLKS, SL_4S);
	}
	raft_perfect = 2;
}


void raft_test_completed (void)
{
	if (!flag_test (FLAG_HZ1LIT) &&	!flag_test (FLAG_HZ2LIT)
		&& !flag_test (FLAG_HZ3LIT) && !flag_test (FLAG_HZ4LIT)
		&& !flag_test (FLAG_HZ5LIT) && 	!flag_test (FLAG_HZ6LIT) && !flag_test (FLAG_HZ7LIT))
	{

		if (raftnr == 6 && raftmode == 2)
			speech_start (SND_ARETHEREYET, SL_4S);

		if ((raftnr > 6 && raftmode < 3) || (raftnr > 3 && raftmode == 1))
		{
			raftmode++;
			raft_next2rafts ();
		}
		else
		{
			raft_award ();
		}
	}
}

void raft_proceed (void)
{
	raft_hz_reset ();
	raft_award ();
}

void raft_score_hz1_boulder (void)
{
	flag_off (FLAG_HZ1LIT);
	lamp_tristate_off (LM_HZ_BOULDER_GARDEN);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_BOULDERGARDEN, SL_3S);
	else
		speech_start (SND_SCREAM4, SL_3S);
	raft_test_completed ();
}

void raft_score_hz2_spinech (void)
{
	flag_off (FLAG_HZ2LIT);
	lamp_tristate_off (LM_HZ_SPINE_CHILLER);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_SPINECHILLER, SL_3S);
	raft_test_completed ();
}

void raft_score_hz3_nowayout (void)
{
	flag_off (FLAG_HZ3LIT);
	lamp_tristate_off (LM_HZ_NO_WAY_OUT);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_NOWAYOUT, SL_3S);
	raft_test_completed ();
}

void raft_score_hz4_disdrop (void)
{
	flag_off (FLAG_HZ4LIT);
	lamp_tristate_off (LM_HZ_DISDROP);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_DISDROP, SL_3S);
	else
		speech_start (SND_SCREAM5, SL_3S);
	raft_test_completed ();
}

void raft_score_hz5_boombend (void)
{
	flag_off (FLAG_HZ5LIT);
	lamp_tristate_off (LM_HZ_BOOM_BEND);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_BOOMBEND, SL_3S);
	else
		speech_start (SND_SCREAM3, SL_3S);

	raft_test_completed ();
}

void raft_score_hz6_insfalls (void)
{
	flag_off (FLAG_HZ6LIT);
	lamp_tristate_off (LM_HZ_INSANITY_FALLS);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_INSANITYFALLS, SL_3S);
	flasher_pulse (FLASH_INSANITY_FALLS_FL);
	raft_test_completed ();
}

void raft_score_hz7_bigbluff (void)
{
	flag_off (FLAG_HZ7LIT);
	lamp_tristate_off (LM_HZ_BIGFOOT_BLUFF);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_BIGFOOTBLUFF, SL_3S);
	raft_test_completed ();
}

void raft_award_hazard (void)
{
	if (flag_test (FLAG_HZ1LIT))
		raft_score_hz1_boulder ();
	else if (flag_test (FLAG_HZ5LIT))
		raft_score_hz5_boombend ();
	else if (flag_test (FLAG_HZ2LIT))
		raft_score_hz2_spinech ();
	else if (flag_test (FLAG_HZ3LIT))
		raft_score_hz3_nowayout ();
	else if (flag_test (FLAG_HZ4LIT))
		raft_score_hz4_disdrop ();
	else if (flag_test (FLAG_HZ6LIT))
		raft_score_hz6_insfalls ();
	else if (flag_test (FLAG_HZ7LIT))
		raft_score_hz7_bigbluff ();
}


CALLSET_ENTRY (raft, left_ramp_made)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ2LIT))
		raft_score_hz2_spinech ();
	else
	{
		deff_start (DEFF_HZ2);
		raft_perfect = 1;
	}
}

CALLSET_ENTRY (raft, dev_lock_enter)
{
	if (flag_test (FLAG_HZ3LIT) && global_flag_test (GLOBAL_FLAG_RAFTMODE))
		raft_score_hz3_nowayout ();
}

CALLSET_ENTRY (raft, sw_disas_drop_main)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ4LIT))
	{
		raft_score_hz4_disdrop ();
		raft_perfect = 1;
	}
}

CALLSET_ENTRY (raft, sw_rapids_main_ramp)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ6LIT))
		raft_score_hz6_insfalls ();
	else
	{
		deff_start (DEFF_HZ6);
		raft_perfect = 1;
	}
}

CALLSET_ENTRY (raft, sw_canyon_main)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ7LIT))
		raft_score_hz7_bigbluff ();
	else
	{
		raft_perfect = 1;
	}

}

CALLSET_ENTRY (raft, left_loop_made)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ1LIT))
		raft_score_hz1_boulder ();
	else
	{
		deff_start (DEFF_HZ1);
		raft_perfect = 1;
	}
}

CALLSET_ENTRY (raft, right_loop_made)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ5LIT))
		raft_score_hz5_boombend ();
	else
	{
		deff_start (DEFF_HZ5);
		raft_perfect = 1;
	}

}


CALLSET_ENTRY (raft, secret_passage_made)
{
	deff_start (DEFF_SECRET);
	speech_start (SND_YOUFSECRPASS, SL_4S);
//	raft_perfect = 1;
	raft_award_hazard ();
}



CALLSET_ENTRY (raft, lamp_update)
{

	if (global_flag_test (GLOBAL_FLAG_PF_LAMPS_OFF) || !global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	switch (raftnr)
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
		case 9:
			lamp_tristate_flash (LM_WET_WILLIES);
			break;
	}

	switch (raftnr)
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
/*
	if (raftnr > 1)
		lamp_tristate_on (LM_RAFT_1);
	if (raftnr > 2)
		lamp_tristate_on (LM_RAFT_2);
	if (raftnr > 3)
		lamp_tristate_on (LM_RAFT_3);
	if (raftnr > 4)
		lamp_tristate_on (LM_RAFT_4);
	if (raftnr > 5)
		lamp_tristate_on (LM_RAFT_5);
	if (raftnr > 6)
		lamp_tristate_on (LM_RAFT_6);
	if (raftnr > 7)
		lamp_tristate_on (LM_RAFT_7);
	if (raftnr > 8)
		lamp_tristate_on (LM_RAFT_8);
*/

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

	if (raftnr == 9)
		lamp_tristate_flash (LM_HZ_NO_WAY_OUT);

}

CALLSET_ENTRY (raft, music_refresh)
{
	if (in_game)
	{
		switch (raftnr)
		{
			case 1:
				music_request (MUS_RAFT1, PRI_GAME_MODE1 +1);
				break;
			case 2:
				music_request (MUS_RAFT2, PRI_GAME_MODE1 +1);
				break;
			case 3:
				music_request (MUS_RAFT3, PRI_GAME_MODE1 +1);
				break;
			case 4:
				music_request (MUS_RAFT4, PRI_GAME_MODE1 +1);
				break;
			case 5:
				music_request (MUS_RAFT5, PRI_GAME_MODE1 +1);
				break;
			case 6:
				music_request (MUS_RAFT6, PRI_GAME_MODE1 +1);
				break;
			case 7:
				music_request (MUS_RAFT7, PRI_GAME_MODE1 +1);
				break;
			case 8:
				music_request (MUS_RAFT8, PRI_GAME_MODE1 +1);
				break;
			case 9:
				music_request (MUS_RAFT9, PRI_GAME_MODE1 +1);
				break;
		}
	}
}

CALLSET_ENTRY (raft, start_player)
{
	raft_perfectcount = 0;
	raft_reset ();
	raft_hz_reset ();
	raft_next2rafts ();
}


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
RULES Shoot lit hazards to progress raft until wet willy
completing a raft starts river hurryup
completed 3 river hurries starts dam mode next time

moved to GAME_OBJS
*/

#include <freewpc.h>

extern U8 bigfoot_found;
extern U8 skill_ramp_made;
extern U8 skill_bigf_made;
extern U8 hurry_counter; 

extern U8 raftnr;   //nr of raft we are on - until 9 = wet willy
//extern U8 raft_perfectcount;	//nr of times player made a perfect raft

__local__ U8 raftmode;  //count for increasing nr of hazard shots to make before raft is awarded

U8 raft_randomhz;
U8 raft_random;
//U8 raft_perfect;  // is 1 or 3 - used as score multiplier






//void raft_perfect_de//ff (void)
/*{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_var5, 64, 4, "PERFECT PATH");
	font_render_string_center (&font_var5, 64, 12, "BIGFOOT FOUND");

	printf_millions (raftnr * 6);

	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}
*/


void raft_up_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "NEXT RAFT");

	printf_millions (raftnr *2);

	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void raft_hz_lamps_tri_off (void)
{
	lamp_tristate_off (LM_HZ_BOULDER_GARDEN);
	lamp_tristate_off (LM_HZ_SPINE_CHILLER);
	lamp_tristate_off (LM_HZ_NO_WAY_OUT);
	lamp_tristate_off (LM_HZ_DISDROP);
	lamp_tristate_off (LM_HZ_BOOM_BEND);
	lamp_tristate_off (LM_HZ_INSANITY_FALLS);
	lamp_tristate_off (LM_HZ_BIGFOOT_BLUFF);
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

	raft_hz_lamps_tri_off ();
}

void raft_raftlamps_on (U8 myraftnr)
{
	switch (myraftnr)
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

	switch (myraftnr)
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
	
}


void raft_raftlamps_off (void)		//turn off all lamps
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

void raft_reset (void)		//reset rafts
{
	raftnr = 1;
	raftmode = 1;
//	raft_perfect = 3;
	raft_hz_reset ();

	raft_raftlamps_off ();
}

void raft_lighthaz (U8 nexthz)		//set correct lights (yellow triangle)
{
	switch (nexthz)
	{
		case 1:
			flag_on (FLAG_HZ1LIT);
			lamp_tristate_on (LM_HZ_BOULDER_GARDEN);
			break;
		case 2:
			flag_on (FLAG_HZ2LIT);
			lamp_tristate_on (LM_HZ_SPINE_CHILLER);
			break;
		case 3:
			flag_on (FLAG_HZ3LIT);
			lamp_tristate_on (LM_HZ_NO_WAY_OUT);
			break;
		case 4:
			flag_on (FLAG_HZ4LIT);
			lamp_tristate_on (LM_HZ_DISDROP);
			break;
		case 5:
			flag_on (FLAG_HZ5LIT);
			lamp_tristate_on (LM_HZ_BOOM_BEND);
			break;
		case 6:
			flag_on (FLAG_HZ6LIT);
			lamp_tristate_on (LM_HZ_INSANITY_FALLS);
			break;
		case 7:
			flag_on (FLAG_HZ7LIT);
			lamp_tristate_on (LM_HZ_BIGFOOT_BLUFF);
			break;
	}
}


void raft_next2rafts (void)		//define next 2 raft shots to light to make
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


void raft_award (bool bsilent)
{
	bool lbsilent;	//test
	lbsilent = bsilent;

//	score_multiple (SC_1M, raftnr * raft_perfect *2);
	score_multiple (SC_1M, raftnr * 2);

	raftnr++;
	raftmode = 1;

	if (!lbsilent)
		leff_start (LEFF_FL_BGRAFT);
	
	if (raftnr < 9)  //was 8 but raftnr++ moved up ?
	{
//		sound_start (ST_SAMPLE, SND_OK_1, SL_3S, PRI_GAME_QUICK3);
/*		if (raft_perfect == 3)
		{
			raft_perfectcount++;
			bounded_increment (bigfoot_found, 255);
			deff_start (DEFF_RAFT_PERFECT);

			if (raft_perfectcount == 2)
				flag_on (FLAG_DAM_LIT);
		}
//		else
//			deff_start (DEFF_RAFT_UP);
*/
//		raftnr++;
//		raftmode = 1;
		raft_next2rafts ();
	}
	else
	{
		raft_hz_reset ();
		if (!lbsilent)
		{
			speech_start (SND_WWHOWDYFOLKS, SL_4S);
			deff_start (DEFF_WET_QUAL);
		}
	}
//	raft_perfect = 3;
	callset_invoke (raft_lamps_on);
}


void raft_test_completed (bool bsilent)
{
	bool lbsilent;	//test
	lbsilent = bsilent;
	
	if (!flag_test (FLAG_HZ1LIT) &&	!flag_test (FLAG_HZ2LIT)
		&& !flag_test (FLAG_HZ3LIT) && !flag_test (FLAG_HZ4LIT)
		&& !flag_test (FLAG_HZ5LIT) && 	!flag_test (FLAG_HZ6LIT) && !flag_test (FLAG_HZ7LIT))
	{

		if (raftnr == 6 && raftmode == 2 && !lbsilent)
			speech_start (SND_ARETHEREYET, SL_4S);

		if ((raftnr > 6 && raftmode < 3) || (raftnr > 3 && raftmode == 1))
		{
			raftmode++;
			raft_next2rafts ();
		}
		else
		{
			raft_award (lbsilent);
//			riverhurry_stop ();
			if (raftnr < 9 && !lbsilent)  //was 8 but raftnr++ moved up ?
			{
				if (hurry_counter > 1 && hurry_counter % 3 == 0)			//RULE  start dam every 3rd time completed riverhurry
					{
						dam_start ();
					}
					else
					{
						riverhurry_start ();
					}	//RULE start river hurry after awarding raft
									//started here and not in raft_award as this is not started from secret passage or whirlpool
			}
		}
	}
}

//called external to increase a raft
void raft_proceed (void)
{
	raft_hz_reset ();
//	raft_perfect = 1;	//don't give multiplier in score
	if (raftnr < 9)
		raft_award (FALSE);
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
	raft_test_completed (FALSE);
}

void raft_score_hz2_spinech (void)
{
	flag_off (FLAG_HZ2LIT);
	lamp_tristate_off (LM_HZ_SPINE_CHILLER);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_SPINECHILLER, SL_3S);
	raft_test_completed (FALSE);
}

void raft_score_hz3_nowayout (bool bsilent)
{
	bool lbsilent;	//test
	lbsilent = bsilent;

	flag_off (FLAG_HZ3LIT);
	lamp_tristate_off (LM_HZ_NO_WAY_OUT);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_NOWAYOUT, SL_3S);
	raft_test_completed (lbsilent);
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
	raft_test_completed (FALSE);
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

	raft_test_completed (FALSE);
}

void raft_score_hz6_insfalls (void)
{
	flag_off (FLAG_HZ6LIT);
	lamp_tristate_off (LM_HZ_INSANITY_FALLS);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_INSANITYFALLS, SL_3S);
	flasher_pulse (FLASH_INSANITY_FALLS_FL);
	raft_test_completed (FALSE);
}

void raft_score_hz7_bigbluff (void)
{
	flag_off (FLAG_HZ7LIT);
	lamp_tristate_off (LM_HZ_BIGFOOT_BLUFF);
	score (SC_250K);
	if (raftnr < 4)
		speech_start (SND_BIGFOOTBLUFF, SL_3S);
	raft_test_completed (FALSE);
}

void raft_award_hazard (void)	//award first available hazard
{
	if (flag_test (FLAG_HZ1LIT))
		raft_score_hz1_boulder ();
	else if (flag_test (FLAG_HZ5LIT))
		raft_score_hz5_boombend ();
	else if (flag_test (FLAG_HZ2LIT))
		raft_score_hz2_spinech ();
	else if (flag_test (FLAG_HZ3LIT))
		raft_score_hz3_nowayout (FALSE);
	else if (flag_test (FLAG_HZ4LIT))
		raft_score_hz4_disdrop ();
	else if (flag_test (FLAG_HZ6LIT))
		raft_score_hz6_insfalls ();
	else if (flag_test (FLAG_HZ7LIT))
		raft_score_hz7_bigbluff ();
}



void raftmode_on (void)
{
	global_flag_on (GLOBAL_FLAG_RAFTMODE);
	callset_invoke (raft_lamps_on);
}

void raftmode_off (void)
{
	global_flag_off (GLOBAL_FLAG_RAFTMODE);
	cave_stop ();
	riverhurry_stop ();
	callset_invoke (raft_lamps_off);
}


CALLSET_ENTRY (raft, raft_score_hz3_nowayout_true)
{
	raft_score_hz3_nowayout (TRUE);	
}

CALLSET_ENTRY (raft, raft_score_hz3_nowayout_false)
{
	raft_score_hz3_nowayout (FALSE);	
}


CALLSET_ENTRY (raft, raft_lamps_off)
{
	raft_raftlamps_off ();

	raft_hz_lamps_tri_off ();
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
		score (SC_25K);
//		raft_perfect = 1;
	}
}

/*
--ALLSET_ENTRY (raft, dev_lock_enter)
{
	if (flag_test (FLAG_HZ3LIT) && global_flag_test (GLOBAL_FLAG_RAFTMODE))
		raft_score_hz3_nowayout ();
}
*/

CALLSET_ENTRY (raft, sw_disas_drop_main)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ4LIT))
	{
		raft_score_hz4_disdrop ();
//		raft_perfect = 1;
	}
	else
		score (SC_25K);

}

CALLSET_ENTRY (raft, sw_rapids_main_ramp)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	score_multiple (SC_50K, skill_ramp_made);

	if (flag_test (FLAG_HZ6LIT))
		raft_score_hz6_insfalls ();
	else
	{
		deff_start (DEFF_HZ6);
//		raft_perfect = 1;
	}
}

CALLSET_ENTRY (raft, sw_canyon_main)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	score_multiple (SC_50K, skill_bigf_made);

	if (flag_test (FLAG_HZ7LIT))
		raft_score_hz7_bigbluff ();
	else
	{
//		raft_perfect = 1;
		if (!global_flag_test (GLOBAL_FLAG_WPOOLLIT) && !global_flag_test (GLOBAL_FLAG_BIGFOOTLIT))
			deff_start (DEFF_HZ7);
	}

}

CALLSET_ENTRY (raft, left_loop_made)	//left loop hazard 1
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ1LIT))
		raft_score_hz1_boulder ();
	else
	{
		deff_start (DEFF_HZ1);
//		raft_perfect = 1;
		score (SC_25K);
	}
}

CALLSET_ENTRY (raft, right_loop_made)	//right loop hazard 5
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (flag_test (FLAG_HZ5LIT))
		raft_score_hz5_boombend ();
	else
	{
		deff_start (DEFF_HZ5);
//		raft_perfect = 1;
		score (SC_25K);
	}

}


CALLSET_ENTRY (raft, secret_passage_made)	//secret passage award raft
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	deff_start (DEFF_SECRET);
	speech_start (SND_YOUFSECRPASS, SL_4S);
//	raft_perfect = 1;
//	raft_award_hazard ();
	raft_award (FALSE);
}



CALLSET_ENTRY (raft, raft_lamps_on)
{
	raft_raftlamps_on (raftnr);

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
	if (in_game && global_flag_test (GLOBAL_FLAG_RAFTMODE))
	{
		switch (raftnr)
		{
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
			default:
			case 1:
				music_request (MUS_RAFT1, PRI_GAME_MODE1 +1);
				break;
		}
	}
}

CALLSET_ENTRY (raft, start_player)
{
	raft_reset ();
//	raft_perfectcount = 0;
	raft_next2rafts ();
	raftmode_on ();
}


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
WPOOLMODES.C
- red lights advance with jet edge switch hits or redtgts
- complete river targets to qualify wpool mode  - in rivertgt.c
- bigfoot diverter activates when wpool mode qualified
- shoot wpool to start mode
*/

#include <freewpc.h>
#include <status.h>
#include <eb.h>

__local__ U8 wpool_award;

U8 wpool_ballsdiverted;



void wpm_lamps_off (void)
{
	lamp_tristate_off (LM_BD_WHIRLP_CHALL);
	lamp_tristate_off (LM_BD_MAN_OVERBD);
	lamp_tristate_off (LM_BD_LIGHT_EB);
	lamp_tristate_off (LM_BD_ADV_RAFT);
	lamp_tristate_off (LM_BD_MYSTERY);
	lamp_tristate_off (LM_BD_5X_PF);
}

void wpm_lamps_on (void)
{
	if (flag_test (FLAG_BD_WHIRLP_PLAYED))
		lamp_tristate_on (LM_BD_WHIRLP_CHALL);
	if (flag_test (FLAG_BD_MANOVER_PLAYED))
		lamp_tristate_on (LM_BD_MAN_OVERBD);
	if (flag_test (FLAG_BD_LIGHTEB_PLAYED))
		lamp_tristate_on (LM_BD_LIGHT_EB);
	if (flag_test (FLAG_BD_ADVRAFT_PLAYED))
		lamp_tristate_on (LM_BD_ADV_RAFT);
	if (flag_test (FLAG_BD_MYSTERY_PLAYED))
		lamp_tristate_on (LM_BD_MYSTERY);
	if (flag_test (FLAG_BD_5XPF_PLAYED))
		lamp_tristate_on (LM_BD_5X_PF);

	switch (wpool_award)
	{
		case 1:
			lamp_tristate_flash (LM_BD_WHIRLP_CHALL);
			break;
		case 2:
			lamp_tristate_flash (LM_BD_MAN_OVERBD);
			break;
		case 3:
			lamp_tristate_flash (LM_BD_LIGHT_EB);
			break;
		case 4:
			lamp_tristate_flash (LM_BD_ADV_RAFT);
			break;
		case 5:
			lamp_tristate_flash (LM_BD_MYSTERY);
			break;
		case 6:
			lamp_tristate_flash (LM_BD_5X_PF);
			break;
	}
}

void wpm_mystery_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "MYSTERY");

//TODO ??
	U8 i;
	i = random_scaled(5) +1;
	score_multiple (SC_1M, i);
	printf_millions (i);

	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);
	dmd_show_low ();
	task_sleep_sec (1);
	deff_exit ();
}

void wpm_reset_bdmodes (void)
{
	U8 i;
	flag_off (FLAG_BD_WHIRLP_PLAYED);
	flag_off (FLAG_BD_MANOVER_PLAYED);
	flag_off (FLAG_BD_LIGHTEB_PLAYED);
	flag_off (FLAG_BD_MYSTERY_PLAYED);
	flag_off (FLAG_BD_ADVRAFT_PLAYED);
	flag_off (FLAG_BD_5XPF_PLAYED);

	i = random_scaled(5) +1;
	wpool_award = i;	//start is random
	lamp_tristate_off (LM_LIGHT_WHIRLPOOL);
	global_flag_off (GLOBAL_FLAG_WPOOLLIT);
	wpm_lamps_off ();
}

void wpm_award_whirlp (void)
{
	flag_on (FLAG_BD_WHIRLP_PLAYED);
	wpch_start ();
}

void wpm_award_manover (void)
{
	flag_on (FLAG_BD_MANOVER_PLAYED);
	wpman_start ();
}

void wpm_award_eb (void)
{
	flag_on (FLAG_BD_LIGHTEB_PLAYED);

	if (can_award_extra_ball())
	{
		speech_start (SND_GETEXTRABALL, SL_4S);
		light_easy_extra_ball ();
		deff_start_sync (DEFF_EXTRA_BALL_LIT);
	}
	else
	{
		sound_start (ST_SAMPLE, SND_OK_5, SL_4S, PRI_GAME_QUICK3);
		score (SC_1M);
		deff_start_sync (DEFF_EB_SCORE);
	}
	task_sleep_sec (1);
}

void wpm_award_advraft (void)
{
	flag_on (FLAG_BD_ADVRAFT_PLAYED);
	raft_proceed ();
//	task_sleep_sec (2);
}

void wpm_award_mystery (void)
{
	flag_on (FLAG_BD_MYSTERY_PLAYED);
	speech_start (SND_SPIRITRIVER, SL_4S);
	deff_start (DEFF_WPM_MYSTERY);
	task_sleep_sec (2);
//	fall_start ();
}

void wpm_award_5xpf (void)
{
	flag_on (FLAG_BD_5XPF_PLAYED);
	wp5x_start ();
}


bool wpm_check_award_free (U8 aw)
{
	if (aw == 1)
		return flag_test (FLAG_BD_WHIRLP_PLAYED);
	else if (aw == 2)
		return flag_test (FLAG_BD_MANOVER_PLAYED);
	else if (aw == 3)
		return flag_test (FLAG_BD_LIGHTEB_PLAYED);
	else if (aw == 4)
		return flag_test (FLAG_BD_ADVRAFT_PLAYED);
	else if (aw == 5)
		return flag_test (FLAG_BD_MYSTERY_PLAYED);
	else if (aw == 6)
		return flag_test (FLAG_BD_5XPF_PLAYED);
	else
		return FALSE;
}

void wpm_next_award_task (void)
{
	U8 i;
	for (i = 0; i < 7; i++)
	{
		if (wpool_award < 6)
			wpool_award++;
		else 
			wpool_award = 1;
		
		if (wpm_check_award_free (wpool_award))
			break;
	}
	wpm_lamps_off ();
	wpm_lamps_on ();
	task_exit ();
}

void wpm_next_award (void)
{
	if (!task_find_gid (GID_NEXTAWARD))
		task_create_gid (GID_NEXTAWARD, wpm_next_award_task);
}

void wpm_award (void)
{
	switch (wpool_award)
	{
		case 1:
			wpm_award_whirlp ();
			break;
		case 2:
			wpm_award_manover ();
			break;
		case 3:
			wpm_award_eb ();
			break;
		case 4:
			wpm_award_mystery ();
			break;
		case 5:
			wpm_award_advraft ();
			break;
		case 6:
			wpm_award_5xpf ();
			break;
	}

	wpm_next_award ();


	if (flag_test (FLAG_BD_WHIRLP_PLAYED) && flag_test (FLAG_BD_MANOVER_PLAYED) &&
		flag_test (FLAG_BD_LIGHTEB_PLAYED) && flag_test (FLAG_BD_MYSTERY_PLAYED) &&
		flag_test (FLAG_BD_ADVRAFT_PLAYED) && flag_test (FLAG_BD_5XPF_PLAYED))
		{
			flag_on (FLAG_WPOOLFINISHED);
			wpm_reset_bdmodes ();
		}
}



// invoked in bigfootdiv.c
CALLSET_ENTRY (wpm, wpool_enter)
{
	bounded_increment (wpool_ballsdiverted, 255);
	deff_start (DEFF_WPM_ENTER);
	sound_start (ST_SAMPLE, SND_ENTERWP1, SL_4S, PRI_GAME_QUICK3);	//TODO sounds loops sometimes - select other sample
}


CALLSET_ENTRY (wpm, sw_whirlpool_exit)
{
//	sound_start (ST_SAMPLE, SND_SPLASH, SL_3S, PRI_GAME_QUICK3);
	sound_start (ST_SAMPLE, SND_SPLASH_6, SL_3S, PRI_GAME_QUICK3);

	if (wpool_ballsdiverted == 0)
	{
		deff_start (DEFF_WPM_DIRTY);
		score (SC_250K);
	}

	bounded_decrement (wpool_ballsdiverted, 0);

	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_WPCH_RUNNING) || multi_ball_play ())
		return;

// MAPMODE REMOVED
//	if (!flag_test (FLAG_MAPPLAYED) &&  flag_test (FLAG_BFCMAP))
//	{
//		global_flag_on (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
//		map_start ();
//		return;
//	} 	else 

	//dammode removed here is now started as third riverhurry
/*	if (flag_test (FLAG_DAM_LIT))
	{
		flag_off (FLAG_DAM_LIT);
		dam_start ();
		return;
	}
	else 
*/
	if (global_flag_test (GLOBAL_FLAG_WPOOLLIT))
	{
		global_flag_off (GLOBAL_FLAG_WPOOLLIT);
		lamp_tristate_off (LM_LIGHT_WHIRLPOOL);
		deff_start (DEFF_WPM_ENTER);
//		global_flag_on (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
		wpm_award ();
//		global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	}
}


//move to next award when going up the spine chiller ramp
CALLSET_ENTRY (wpm, left_ramp_made)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	wpm_next_award ();
}


CALLSET_ENTRY (wpm, raft_lamps_off)
{
	wpm_lamps_off ();
}

CALLSET_ENTRY (wpm, raft_lamps_on)
{
	wpm_lamps_on ();
}


CALLSET_ENTRY (wpm, start_ball)
{
	wpool_ballsdiverted = 0;
}

CALLSET_ENTRY (wpm, start_player)
{
	wpm_reset_bdmodes ();
	flag_off (FLAG_WPOOLFINISHED);
//	flag_off (FLAG_DAM_LIT);
}


CALLSET_ENTRY (wpm, status_report)
{
	status_page_init ();
	if (flag_test (FLAG_WPOOLFINISHED))
		font_render_string_center (&font_mono5, 64, 2, "POOL COMPLETED");

	if (flag_test (FLAG_BD_WHIRLP_PLAYED))
		font_render_string (&font_mono5, 2, 10, "WPOOL CHALL");

	if (flag_test (FLAG_BD_MANOVER_PLAYED))
		font_render_string (&font_mono5, 2, 18, "MAN OVERBOARD");

	if (flag_test (FLAG_BD_LIGHTEB_PLAYED))
		font_render_string (&font_mono5, 2, 24, "EXTRA BALL");

	if (flag_test (FLAG_BD_MYSTERY_PLAYED))
		font_render_string (&font_mono5, 80, 10, "MYSTERY");

	if (flag_test (FLAG_BD_ADVRAFT_PLAYED))
		font_render_string (&font_mono5, 80, 18, "ADVANCE RAFT");

	if (flag_test (FLAG_BD_5XPF_PLAYED))
		font_render_string (&font_mono5, 80, 24, "5X FUN");

	status_page_complete ();
}


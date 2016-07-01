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
- red lights advance with bumper hits
- complete river targets to qualify wpool mode  in rivertgt.c
- bigfoot diverter activates when wpool mode qualified
- shoot wpool to start mode

lamps:
57: bd whirlp chall, red
58: bd man overbd, red
81: bd light eb, red
82: bd adv raft, red
83: bd mystery, red
84: bd 5x pf, red
ll: bouldermodes

switch:
48: canyon entrance, ingame
57: canyon main, ingame, opto
62: whirlpool exit, ingame, opto

*/

#include <freewpc.h>
#include <eb.h>


__local__ U8 wpool_award;

U8 i;
U8 wpool_ballsdiverted;


void wpm_mystery_deff (void)
{
	dmd_alloc_low_clean ();
	font_render_string_center (&font_fixed6, 64, 10, "MYSTERY");

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
	flag_off (FLAG_BD_WHIRLP_PLAYED);
	flag_off (FLAG_BD_MANOVER_PLAYED);
	flag_off (FLAG_BD_LIGHTEB_PLAYED);
	flag_off (FLAG_BD_MYSTERY_PLAYED);
	flag_off (FLAG_BD_ADVRAFT_PLAYED);
	flag_off (FLAG_BD_5XPF_PLAYED);
	wpool_award = 1;
	lamp_tristate_off (LM_LIGHT_WHIRLPOOL);
	global_flag_off (GLOBAL_FLAG_WPOOLLIT);
	lamplist_apply (LAMPLIST_BOULDERMODES, lamp_off);
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
	speech_start (SND_GETEXTRABALL, SL_4S);
	flag_on (FLAG_BD_LIGHTEB_PLAYED);
	light_easy_extra_ball ();
	deff_start (DEFF_EXTRA_BALL_LIT);
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
//	deff_start (DEFF_WPM_MYSTERY);
	task_sleep_sec (2);
	fall_start ();
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
	for (i = 0; i < 7; i++)
	{
		if (wpool_award < 6)
			wpool_award++;
		else 
			wpool_award = 1;
		
		if (wpm_check_award_free (wpool_award))
			break;
	}
	lamp_tristate_off (LM_BD_WHIRLP_CHALL);
	lamp_tristate_off (LM_BD_MAN_OVERBD);
	lamp_tristate_off (LM_BD_LIGHT_EB);
	lamp_tristate_off (LM_BD_ADV_RAFT);
	lamp_tristate_off (LM_BD_MYSTERY);
	lamp_tristate_off (LM_BD_5X_PF);
	task_exit ();
}

void wpm_next_award (void)
{
	if (!task_find_gid (GID_NEXTAWARD))
		task_create_gid (GID_NEXTAWARD, wpm_next_award_task);
}

void wpm_award (void)
{

/*	if (!flag_test (FLAG_BD_WHIRLP_PLAYED))
	{
		wpm_award_whirlp ();
	}
	else if (!flag_test (FLAG_BD_MANOVER_PLAYED))
	{
		wpm_award_manover ();
	}
	else if (!flag_test (FLAG_BD_LIGHTEB_PLAYED))
	{
		wpm_award_eb ();
	}
	else if (!flag_test (FLAG_BD_MYSTERY_PLAYED))
	{
		wpm_award_mystery ();
	}
	else if (!flag_test (FLAG_BD_ADVRAFT_PLAYED))
	{
		wpm_award_advraft ();
	}
	else if (!flag_test (FLAG_BD_5XPF_PLAYED))
	{
		wpm_award_5xpf ();
	}
*/
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
	sound_start (ST_SAMPLE, SND_ENTERWP1, SL_4S, PRI_GAME_QUICK3);
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

	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE))
		return;

	if (!flag_test (FLAG_MAPPLAYED) &&  flag_test (FLAG_BFCMAP))
	{
//		global_flag_on (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
		map_start ();
	} 
	else if (flag_test (FLAG_DAM_LIT))
	{
		flag_off (FLAG_DAM_LIT);
		dam_start ();
	}
	else if (global_flag_test (GLOBAL_FLAG_WPOOLLIT))
	{
		global_flag_off (GLOBAL_FLAG_WPOOLLIT);
		lamp_tristate_off (LM_LIGHT_WHIRLPOOL);
		deff_start (DEFF_WPM_ENTER);
//		global_flag_on (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
		wpm_award ();
//		global_flag_off (GLOBAL_FLAG_HOLD_MINE_KICKOUT);
	}
}

CALLSET_ENTRY (wpm, lamp_update)
{
	if (!global_flag_test (GLOBAL_FLAG_RAFTMODE) || global_flag_test (GLOBAL_FLAG_PF_LAMPS_OFF))
		return;

/*	lamp_tristate_off (LM_BD_WHIRLP_CHALL);
	lamp_tristate_off (LM_BD_MAN_OVERBD);
	lamp_tristate_off (LM_BD_LIGHT_EB);
	lamp_tristate_off (LM_BD_ADV_RAFT);
	lamp_tristate_off (LM_BD_MYSTERY);
	lamp_tristate_off (LM_BD_5X_PF);
*/

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

CALLSET_ENTRY (wpm, start_player)
{
	wpm_reset_bdmodes ();
	flag_off (FLAG_WPOOLFINISHED);
	flag_off (FLAG_DAM_LIT);
	wpool_ballsdiverted = 0;
}


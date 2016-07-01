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
hit enough jets to advance riverclass and thus bonus multiplier
play sound in regular mode
play moo in cow mode
play money sound in bouldergarden frenzy mode

*/

#include <freewpc.h>
#include <status.h>

extern U8 riverclass;
extern U8 caveshots;

__local__ U8 jets_hit;
U8 jets_extra_hit;
U8 jets_sound_index;

sound_code_t jet_sounds[18] = {
SND_BGARDEN_1, SND_BGARDEN_2, SND_BGARDEN_3, SND_BGARDEN_4, SND_BGARDEN_5, SND_BGARDEN_6,
SND_BGARDEN_7, SND_BGARDEN_8, SND_BGARDEN_9, SND_BGARDEN_10, SND_BGARDEN_11, SND_BGARDEN_12,
SND_BGARDEN_13, SND_BGARDEN_14, SND_BGARDEN_15, SND_BGARDEN_16, SND_BGARDEN_17, SND_BGARDEN_18};

sound_code_t jet_coin_sounds[12] = {SND_BGARDEN_COIN_1, SND_BGARDEN_COIN_2, SND_BGARDEN_COIN_3,
SND_BGARDEN_COIN_4, SND_BGARDEN_COIN_5, SND_BGARDEN_COIN_6, SND_BGARDEN_COIN_7, SND_BGARDEN_COIN_8, 
SND_BGARDEN_COIN_9, SND_BGARDEN_COIN_10, SND_BGARDEN_COIN_11, SND_BGARDEN_COIN_12};

const U8 jets_needed[] = {10, 20, 35, 50, 75, 100};

void jet_hit_deff (void)
{
	dmd_alloc_low_clean ();
	sprintf ("%d JETS FOR", jets_needed[riverclass]-jets_hit);
	font_render_string_center (&font_fixed6, 64, 7, sprintf_buffer);
	sprintf ("CLASS %d", riverclass +1);
	font_render_string_center (&font_fixed6, 64, 21, sprintf_buffer);

	dmd_show_low ();
	task_sleep (TIME_500MS);
	deff_exit ();
}


CALLSET_ENTRY (jets, sw_jet)
{
	bounded_increment (jets_hit, 255);
	jets_sound_index++;

	score_multiple (SC_20K, riverclass);

	if (caveshots == 20)
		sound_start (ST_SAMPLE, SND_COW, SL_1S, PRI_GAME_QUICK3);
	else if (global_flag_test (GLOBAL_FLAG_GOLD_RUNNING))
	{
		if (jets_sound_index > 11)
			jets_sound_index = 0;
		sound_start (ST_SAMPLE, jet_coin_sounds[jets_sound_index], SL_1S, PRI_GAME_QUICK3);
	}
	else
	{
		if (jets_sound_index > 17)
			jets_sound_index = 0;
		sound_start (ST_SAMPLE, jet_sounds[jets_sound_index], SL_1S, PRI_GAME_QUICK3);
	}

	if (riverclass == 6)
		return;

	if (jets_hit >= jets_needed[riverclass])
	{
		jets_hit = 0;
		rivcl_increase_class ();
	}
	else
	{
		deff_restart (DEFF_JET_HIT);
	}
}


CALLSET_ENTRY (jets, sw_jets_lower, sw_jets_right)
{
	sound_start (ST_SAMPLE, SND_BGARDEN_COIN_12, SL_1S, PRI_GAME_QUICK3);
	bounded_increment (jets_extra_hit, 255);

	if (global_flag_test (GLOBAL_FLAG_RAFTMODE))
		wpm_next_award ();
}

CALLSET_ENTRY (jets, start_ball)
{
	jets_hit = 0;
	jets_extra_hit = 0;
}

CALLSET_ENTRY (jets, start_player)
{
	jets_sound_index = 0;
}

CALLSET_ENTRY (jets, status_report)
{
	status_page_init ();
	sprintf ("%d JETS HIT", jets_hit);
	font_render_string_center (&font_mono5, 64, 10, sprintf_buffer);
	sprintf ("%d JETS NEEDED", jets_needed[riverclass]);
	font_render_string_center (&font_mono5, 64, 21, sprintf_buffer);
	status_page_complete ();
}

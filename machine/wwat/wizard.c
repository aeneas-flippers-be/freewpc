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
- wizmode in multiple steps, each time shoot lock again

1- wake up bigfoot - shoot 2 white
2- visit cave
3- 2 drops
4- 20 bumper hits
5- complete red tgts
6- 2 spine chillers =multimill
7- spine chill to wpool
8- 2x no way out to rapids

*/

#include <freewpc.h>

U8 wiz_sound_index;

sound_code_t wiz_sounds[12] = {
SND_BGFT_LAUGH1, SND_BGFT_LAUGH2, SND_BGFT_LAUGH3, SND_BGFT_LAUGH4, SND_BGFT_LAUGH5, SND_BGFT_LAUGH6,
SND_BGFT_LAUGH7, SND_BGFT_LAUGH8, SND_BGFT_LAUGH9, SND_BGFT_LAUGH10, SND_BGFT_LAUGH11, SND_BGFT_LAUGH12};

U8 wiz_raftnr;
bool wiz_raftgoal_made;

U8 wiz_shot1made;
U8 wiz_shot2made;
U8 wiz_shot3made;



void wiz_score_jackpot (void)
{
	score (SC_10M);
	if (++wiz_sound_index == 12)
		wiz_sound_index = 0;
	sound_start (ST_SAMPLE, wiz_sounds[wiz_sound_index], SL_2S, PRI_GAME_QUICK3);
	deff_start (DEFF_JACKPOT);
}

//TODO
void wiz_running_deff (void)
{
	for (;;)
	{
		dmd_alloc_low_clean ();

		if (wiz_raftgoal_made)
		{
			sprintf("SHOOT");
			font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
			sprintf("NO WAY OUT");
			font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
		}
		else
		{
			switch (wiz_raftnr)
			{
				case 1:
					sprintf("WAKE UP BIGFOOT");
					font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
					sprintf("HIT TARGETS");
					font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
					break;
				case 2:
					sprintf("SEE BIGFOOT");
					font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
					sprintf("VISIT CAVE");
					font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
					break;
				case 3:
					sprintf("SHOOT 2X");
					font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
					sprintf("DISASTER DROP");
					font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
					break;
				case 4:
					sprintf("GET 20");
					font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
					sprintf("BUMPER HITS");
					font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
					break;
				case 5:
					sprintf("COMPLETE");
					font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
					sprintf("3 RED TARGETS");
					font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
					break;
				case 6:
					sprintf("LOOP");
					font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
					sprintf("SPINE CHILLER");
					font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
					break;
				case 7:
					sprintf("SHOOT RAMP");
					font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
					sprintf("THEN POOL");
					font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
					break;
				case 8:
					sprintf("2X RAPIDS RAMP");
					font_render_string_center (&font_var5, 64, 16, sprintf_buffer);
					sprintf("TO NO WAY OUT");
					font_render_string_center (&font_var5, 64, 26, sprintf_buffer);
					break;
			}
		}
		dmd_show_low ();
		task_sleep (TIME_133MS);
	}
}


void wizard_stop (void)
{
	global_flag_off (GLOBAL_FLAG_WIZ_MB_RUNNING);
	global_flag_off (GLOBAL_FLAG_WIZ_RUNNING);
	global_flag_off (GLOBAL_FLAG_WPOOLLIT);
	deff_stop (DEFF_WIZ_RUNNING);
	deff_stop (DEFF_WIZ_MB_RUNNING);
//	deff_stop (DEFF_JACKPOT);
	leff_stop (LEFF_RAFTLOOP);
	leff_stop (LEFF_TGTTOGGLE);

	raft_hz_lamps_tri_off ();

	lamp_tristate_off (LM_LIGHT_SPINE);
	lamp_tristate_off (LM_UPF_MULTI_JP);
	lamp_tristate_off (LM_UPF_BIGFOOT_JP);
	lamp_tristate_off (LM_2BANK_UP);
	lamp_tristate_off (LM_2BANK_LOW);

	flag_off (FLAG_WPOOLFINISHED);
	flag_off (FLAG_GOLDPLAYED);
	flag_off (FLAG_WETFINISHED);
	raftmode_on ();
}

void wizard_start (void)
{
	raftmode_off ();

	speech_start (SND_WWATER, SL_3S);
	deff_start_sync (DEFF_WIZ_INTRO);
//	task_sleep_sec (1);

	wiz_raftgoal_made = FALSE;
	wiz_raftnr = 1;

	wiz_shot1made = 0;
	wiz_shot2made = 0;
	wiz_shot3made = 0;

	lamp_tristate_flash (LM_2BANK_UP);
	lamp_tristate_flash (LM_2BANK_LOW);

	leff_start (LEFF_FL_WETWILLY);

	global_flag_on (GLOBAL_FLAG_WIZ_RUNNING);
}

void wizard_mb_start (void)
{
	speech_start (SND_WWATER, SL_3S);
	task_sleep_sec (1);

	wiz_sound_index = 0;

//	lamplist_apply (LAMPLIST_LOCKSGREEN, lamp_off);
	leff_start (LEFF_RAFTLOOP);
	leff_start (LEFF_TGTTOGGLE);

	global_flag_off (GLOBAL_FLAG_WIZ_RUNNING);
	deff_stop (DEFF_WIZ_RUNNING);
	global_flag_on (GLOBAL_FLAG_WIZ_MB_RUNNING);

	lamp_tristate_flash (LM_UPF_MULTI_JP);
	lamp_tristate_flash (LM_2BANK_UP);
	lamp_tristate_flash (LM_2BANK_LOW);
	lamp_tristate_flash (LM_UPF_BIGFOOT_JP);

	qmball_flash_hz ();

	task_sleep_sec (1);	
	lock_unlockball ();
	task_sleep_sec (1);	
	lock_unlockball ();
//	task_sleep_sec (1);	
//	lock_unlockball ();
//	set_ball_count (3);
}


void wiz_test3red (void)
{
	if (wiz_shot1made == 1 && wiz_shot2made == 1 && wiz_shot3made == 1)
	{
		wiz_raftgoal_made = TRUE;
		lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
		lamp_tristate_off (LM_3BANK_TOP);
		lamp_tristate_off (LM_3BANK_CENTER);
		lamp_tristate_off (LM_3BANK_BOTTOM);
	}
}


CALLSET_ENTRY (wizard, display_update)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		deff_start_bg (DEFF_WIZ_MB_RUNNING, 0);
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		deff_start_bg (DEFF_WIZ_RUNNING, 0);
}

CALLSET_ENTRY (wizard, music_refresh)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		music_request (MUS_MULTIBALL, PRI_GAME_MODE1 + 5);
}



CALLSET_ENTRY (wizard, sw_3bank_top)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 5)
	{
		wiz_shot1made = 1;
		wiz_test3red ();
	}
}

CALLSET_ENTRY (wizard, sw_3bank_center)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 5)
	{
		wiz_shot1made = 2;
		wiz_test3red ();
	}
}

CALLSET_ENTRY (wizard, sw_3bank_bottom)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 5)
	{
		wiz_shot1made = 3;
		wiz_test3red ();
	}
}


CALLSET_ENTRY (wizard, sw_2bank_up)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 1)
	{
		wiz_shot1made = 1;
		if (wiz_shot1made == 1 && wiz_shot2made == 1)
			wiz_raftgoal_made = TRUE;
			lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
			lamp_tristate_off (LM_2BANK_UP);
			lamp_tristate_off (LM_2BANK_LOW);
	}
}

CALLSET_ENTRY (wizard, sw_2bank_low)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 1)
	{
		wiz_shot2made = 1;
		if (wiz_shot1made == 1 && wiz_shot2made == 1)
			wiz_raftgoal_made = TRUE;
			lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
			lamp_tristate_off (LM_2BANK_UP);
			lamp_tristate_off (LM_2BANK_LOW);
	}
}

CALLSET_ENTRY (wizard, sw_canyon_main)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		wiz_score_jackpot ();
}

CALLSET_ENTRY (wizard, left_ramp_made)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		wiz_score_jackpot ();

	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && (wiz_raftnr == 6 || wiz_raftnr == 7))
	{
		if (free_timer_test (TIM_SKILL) && wiz_raftnr == 6)
// reuse skill timer
		{
			wiz_raftgoal_made = TRUE;
			lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
			lamp_tristate_off (LM_HZ_SPINE_CHILLER);
		}
		free_timer_start (TIM_SKILL, TIME_4S);
	}
}





//ALLSET_ENTRY (wizard, dev_lock_enter)
/*{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		wiz_score_jackpot ();

	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING))
	{
		if (wiz_raftnr == 8 && wiz_shot1made == 2)
			wiz_raftgoal_made = TRUE;

		if (wiz_raftgoal_made)
		{
			wiz_raftgoal_made = FALSE;
			wiz_raftnr++;
			wiz_shot1made = 0;
			wiz_shot2made = 0;
			wiz_shot3made = 0;
			lamp_tristate_off (LM_HZ_NO_WAY_OUT);
			score (SC_10M);

			switch (wiz_raftnr)
			{
				case 3:
					lamp_tristate_flash (LM_HZ_DISDROP);
					break;
				case 5:
					lamp_tristate_flash (LM_3BANK_TOP);
					lamp_tristate_flash (LM_3BANK_CENTER);
					lamp_tristate_flash (LM_3BANK_BOTTOM);
					break;
				case 6:
					lamp_tristate_flash (LM_HZ_SPINE_CHILLER);
					break;
				case 8:
					lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
					lamp_tristate_flash (LM_LIGHT_SPINE);
					break;
			}
			task_sleep_sec (2);
		}

		if (wiz_raftnr == 2)
			global_flag_on (GLOBAL_FLAG_BIGFOOTLIT);
		if (wiz_raftnr == 7)
			global_flag_on (GLOBAL_FLAG_WPOOLLIT);
		if (wiz_raftnr == 8)
			global_flag_off (GLOBAL_FLAG_WPOOLLIT);

		if (wiz_raftnr == 9)
		{
			lamp_tristate_off (LM_HZ_NO_WAY_OUT);
			lamp_tristate_off (LM_LIGHT_SPINE);
			wizard_mb_start ();
		}
	}
}
*/







CALLSET_ENTRY (wizard, sw_disas_drop_main)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		wiz_score_jackpot ();

	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 3)
	{
		bounded_increment (wiz_shot1made, 2);
		if (wiz_shot1made == 2)
		{
			wiz_raftgoal_made = TRUE;
			lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
			lamp_tristate_off (LM_HZ_DISDROP);
		}
	}
}

CALLSET_ENTRY (wizard, sw_whirlpool_exit)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 7)
	{
		if (free_timer_test (TIM_SKILL))
		{
			global_flag_off (GLOBAL_FLAG_WPOOLLIT);
			wiz_raftgoal_made = TRUE;
			lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
		}
	}
}

CALLSET_ENTRY (wizard, sw_rapids_main_ramp)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		wiz_score_jackpot ();

	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 8)
	{
		bounded_increment (wiz_shot1made, 2);
	}
}

CALLSET_ENTRY (wizard, left_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		wiz_score_jackpot ();
}

CALLSET_ENTRY (wizard, right_loop_made)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
		wiz_score_jackpot ();
}


CALLSET_ENTRY (wizard, sw_bigfoot_cave)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 2)
	{
		wiz_raftgoal_made = TRUE;
		lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
		global_flag_off (GLOBAL_FLAG_BIGFOOTLIT);
	}
}

CALLSET_ENTRY (wizard, sw_jet)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_RUNNING) && wiz_raftnr == 4)
	{
		bounded_increment (wiz_shot1made, 20);
		if (wiz_shot1made == 20)
		{
			wiz_raftgoal_made = TRUE;
			lamp_tristate_flash (LM_HZ_NO_WAY_OUT);
		}
	}
}

CALLSET_ENTRY (wizard, any_pf_switch)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING))
	{
		score (SC_20K);
	}
}

CALLSET_ENTRY (wizard, single_ball_play)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING) || global_flag_test (GLOBAL_FLAG_WIZ_RUNNING))
	{
		wizard_stop ();
	}
}

CALLSET_ENTRY (wizard, end_ball, tilt)
{
	if (global_flag_test (GLOBAL_FLAG_WIZ_MB_RUNNING) || global_flag_test (GLOBAL_FLAG_WIZ_RUNNING))
	{
		wizard_stop ();
	}
}



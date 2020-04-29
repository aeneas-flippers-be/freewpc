#include <freewpc.h>


void lock_kick_leff (void)
{
	flasher_pulse (FLASH_R_MOUNTAIN_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_R_MOUNTAIN_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_R_MOUNTAIN_FL);
	leff_exit ();
}

void lostmine_kick_leff (void)
{
	flasher_pulse (FLASH_MINE_POPPER_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_MINE_POPPER_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_MINE_POPPER_FL);
	leff_exit ();
}

void fl_ulpf_leff (void)
{
	flasher_pulse (FLASH_UL_PF_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_UL_PF_FL);
	leff_exit ();
}

void fl_cave_leff (void)
{
	flasher_pulse (FLASH_BIGFOOT_CAVE_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_BIGFOOT_CAVE_FL);
	leff_exit ();
}

void fl_lmountain_leff (void)
{
	flasher_pulse (FLASH_L_MOUNTAIN_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_L_MOUNTAIN_FL);
	leff_exit ();
}

void fl_bigfoot_leff (void)
{
	flasher_pulse (FLASH_BIGFOOT_BODY_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_BIGFOOT_BODY_FL);
	leff_exit ();
}

void fl_wpool_leff (void)
{
	flasher_pulse (FLASH_WPOOL_ENTER_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_WPOOL_ENTER_FL);
	leff_exit ();
}

void fl_wetwilly_leff (void)
{
	flasher_pulse (FLASH_WET_WILLY_HEAD);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_WET_WILLY_HEAD);
	leff_exit ();
}

void fl_bgraft_leff (void)
{
	flasher_pulse (FLASH_BG_RAFT);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_BG_RAFT);
	leff_exit ();
}

void fl_bgriders_leff (void)
{
	flasher_pulse (FLASH_BG_RIDERS);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_BG_RIDERS);
	leff_exit ();
}

void fl_bfdiv_leff (void)
{
	flasher_pulse (FLASH_R_MOUNTAIN_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_BIGFOOT_BODY_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_WPOOL_ENTER_FL);
	leff_exit ();
}


void fl_mainramp_leff (void)
{
	flasher_pulse (FLASH_R_MOUNTAIN_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_L_MOUNTAIN_FL);
	task_sleep (TIME_100MS);
	flasher_pulse (FLASH_UL_PF_FL);
	leff_exit ();
}

//when rapids ramp shot is made - from upfld to left inlane
void fl_rapidsmade_leff (void)
{
	flasher_pulse (FLASH_UL_PF_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_INSANITY_FALLS_FL);
	task_sleep (TIME_200MS);
	flasher_pulse (FLASH_MINE_POPPER_FL);
	leff_exit ();
}


void fl_all_pf_loop_leff (void)
{
	for (;;)
	{
		flasher_pulse (FLASH_R_MOUNTAIN_FL);
		task_sleep (TIME_33MS);
		flasher_pulse (FLASH_MINE_POPPER_FL);
		task_sleep (TIME_33MS);
		flasher_pulse (FLASH_BIGFOOT_CAVE_FL);
		task_sleep (TIME_33MS);
		flasher_pulse (FLASH_L_MOUNTAIN_FL);
		task_sleep (TIME_33MS);
		flasher_pulse (FLASH_WET_WILLY_HEAD);
		task_sleep (TIME_33MS);
		flasher_pulse (FLASH_INSANITY_FALLS_FL);
		task_sleep (TIME_33MS);
		flasher_pulse (FLASH_WPOOL_ENTER_FL);
		task_sleep (TIME_33MS);
		flasher_pulse (FLASH_UL_PF_FL);
		task_sleep (TIME_33MS);
		flasher_pulse (FLASH_BIGFOOT_BODY_FL);
		task_sleep (TIME_33MS);
	}
}

void fl_pf_ltor_leff (void)
{
	flasher_pulse (FLASH_MINE_POPPER_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_INSANITY_FALLS_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_UL_PF_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_L_MOUNTAIN_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_R_MOUNTAIN_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_WET_WILLY_HEAD);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_BIGFOOT_BODY_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_BIGFOOT_CAVE_FL);
	leff_exit ();
}

void fl_pf_rtol_leff (void)
{
	flasher_pulse (FLASH_BIGFOOT_CAVE_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_BIGFOOT_BODY_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_WET_WILLY_HEAD);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_R_MOUNTAIN_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_L_MOUNTAIN_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_UL_PF_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_INSANITY_FALLS_FL);
	task_sleep (TIME_33MS);
	flasher_pulse (FLASH_MINE_POPPER_FL);
	leff_exit ();
}





void hz_disdrop_leff (void)
{
	leff_on (LM_HZ_DISDROP);
	task_sleep (TIME_100MS);
	leff_off (LM_HZ_DISDROP);
	task_sleep (TIME_100MS);
	leff_on (LM_HZ_DISDROP);
	task_sleep (TIME_100MS);
	leff_off (LM_HZ_DISDROP);
	task_sleep (TIME_100MS);
	leff_exit ();
}

void bftg_leff (void)
{
	leff_on (LM_2BANK_UP);
	leff_on (LM_2BANK_LOW);
	task_sleep (TIME_100MS);
	leff_off (LM_2BANK_UP);
	leff_off (LM_2BANK_LOW);
	task_sleep (TIME_100MS);
	leff_on (LM_2BANK_UP);
	leff_on (LM_2BANK_LOW);
	leff_exit ();
}

void skilllock_leff (void)
{
	leff_off (LM_LOCK_1);
	leff_off (LM_LOCK_2);
	leff_off (LM_LOCK_3);

	for (;;)
	{
		leff_on (LM_LOCK_1);
		task_sleep (TIME_33MS);
		leff_off (LM_LOCK_3);
		task_sleep (TIME_100MS);
		leff_on (LM_LOCK_2);
		task_sleep (TIME_33MS);
		leff_off (LM_LOCK_1);
		task_sleep (TIME_100MS);
		leff_on (LM_LOCK_3);
		task_sleep (TIME_33MS);
		leff_off (LM_LOCK_2);
		task_sleep (TIME_100MS);
		flasher_pulse (FLASH_BIGFOOT_BODY_FL);
	}
}

void wpoolmode_leff (void)
{
	for (;;)
	{
		leff_off (LM_WHIRLPOOL_6);
		leff_on (LM_WHIRLPOOL_1);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_1);
		leff_on (LM_WHIRLPOOL_2);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_2);
		leff_on (LM_WHIRLPOOL_3);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_3);
		leff_on (LM_WHIRLPOOL_4);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_4);
		leff_on (LM_WHIRLPOOL_5);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_5);
		leff_on (LM_WHIRLPOOL_6);
		task_sleep (TIME_300MS);
	}
}

void wpoolmode2_leff (void)
{
	for (;;)
	{
		leff_off (LM_WHIRLPOOL_6);
		leff_off (LM_WHIRLPOOL_3);
		leff_on (LM_WHIRLPOOL_4);
		leff_on (LM_WHIRLPOOL_1);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_1);
		leff_off (LM_WHIRLPOOL_4);
		leff_on (LM_WHIRLPOOL_5);
		leff_on (LM_WHIRLPOOL_2);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_2);
		leff_off (LM_WHIRLPOOL_5);
		leff_on (LM_WHIRLPOOL_6);
		leff_on (LM_WHIRLPOOL_3);
		task_sleep (TIME_300MS);
	}
}

void wpoolmode3_leff (void)
{
	for (;;)
	{
		leff_off (LM_WHIRLPOOL_2);
		leff_off (LM_WHIRLPOOL_4);
		leff_off (LM_WHIRLPOOL_6);
		leff_on (LM_WHIRLPOOL_1);
		leff_on (LM_WHIRLPOOL_3);
		leff_on (LM_WHIRLPOOL_5);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_1);
		leff_off (LM_WHIRLPOOL_3);
		leff_off (LM_WHIRLPOOL_5);
		leff_on (LM_WHIRLPOOL_2);
		leff_on (LM_WHIRLPOOL_4);
		leff_on (LM_WHIRLPOOL_6);
		task_sleep (TIME_300MS);
	}
}


void wpoolmode6_leff (void)
{
	for (;;)
	{
		leff_on (LM_WHIRLPOOL_2);
		leff_on (LM_WHIRLPOOL_4);
		leff_on (LM_WHIRLPOOL_6);
		leff_on (LM_WHIRLPOOL_1);
		leff_on (LM_WHIRLPOOL_3);
		leff_on (LM_WHIRLPOOL_5);
		task_sleep (TIME_300MS);

		leff_off (LM_WHIRLPOOL_1);
		leff_off (LM_WHIRLPOOL_3);
		leff_off (LM_WHIRLPOOL_5);
		leff_off (LM_WHIRLPOOL_2);
		leff_off (LM_WHIRLPOOL_4);
		leff_off (LM_WHIRLPOOL_6);
		task_sleep (TIME_300MS);
	}
}


//goldrush
void goldrafts_leff (void)
{
	leff_on (LM_RAFT_1);
	leff_on (LM_RAFT_3);
	leff_on (LM_RAFT_5);
	leff_on (LM_RAFT_7);
	for (;;)
	{
		leff_toggle (LM_RAFT_1);
		leff_toggle (LM_RAFT_2);
		leff_toggle (LM_RAFT_3);
		leff_toggle (LM_RAFT_4);
		leff_toggle (LM_RAFT_5);
		leff_toggle (LM_RAFT_6);
		leff_toggle (LM_RAFT_7);
		leff_toggle (LM_RAFT_8);
		task_sleep (TIME_400MS); //500 too slow needs to be almost half - 300 weird in middle ? 400=150bpm
	}
}

//mball quickmb wizard
void raftloop_leff (void)
{
	for (;;)
	{
		leff_off (LM_RAFT_8);
		leff_on (LM_RAFT_1);
		task_sleep (TIME_200MS);
		leff_on (LM_RAFT_2);
		task_sleep (TIME_200MS);
		leff_on (LM_RAFT_3);
		task_sleep (TIME_200MS);
		leff_on (LM_RAFT_4);
		task_sleep (TIME_200MS);
		leff_on (LM_RAFT_5);
		task_sleep (TIME_200MS);
		leff_on (LM_RAFT_6);
		task_sleep (TIME_200MS);
		leff_on (LM_RAFT_7);
		task_sleep (TIME_200MS);
		leff_on (LM_RAFT_8);
		task_sleep (TIME_200MS);
		leff_off (LM_RAFT_1);
		task_sleep (TIME_200MS);
		leff_off (LM_RAFT_2);
		task_sleep (TIME_200MS);
		leff_off (LM_RAFT_3);
		task_sleep (TIME_200MS);
		leff_off (LM_RAFT_4);
		task_sleep (TIME_200MS);
		leff_off (LM_RAFT_5);
		task_sleep (TIME_200MS);
		leff_off (LM_RAFT_6);
		task_sleep (TIME_200MS);
		leff_off (LM_RAFT_7);
		task_sleep (TIME_200MS);
	}
}

//wizard
void tgttoggle_leff (void)
{
	leff_on (LM_RIVER_R1);
	leff_on (LM_RIVER_V);
	leff_on (LM_RIVER_R2);
	leff_on (LM_3BANK_TOP);
	leff_on (LM_3BANK_BOTTOM);
	leff_on (LM_2BANK_LOW);

	for (;;)
	{
		leff_toggle (LM_RIVER_R1);
		leff_toggle (LM_RIVER_I);
		leff_toggle (LM_RIVER_V);
		leff_toggle (LM_RIVER_E);
		leff_toggle (LM_RIVER_R2);
		leff_toggle (LM_3BANK_TOP);
		leff_toggle (LM_3BANK_CENTER);
		leff_toggle (LM_3BANK_BOTTOM);
		leff_toggle (LM_2BANK_UP);
		leff_toggle (LM_2BANK_LOW);
		task_sleep (TIME_200MS);
	}
}




/*
Move oyl lights and get all 3 lit to award something

Lamps
11: oyl o, yellow
12: center lane, yellow
13: right lane, yellow

Switches
11: oyl o, ingame
15: oyl l, ingame
42: oyl y, ingame

RULES
OYL: Complete OYL rollovers, 1k rollover, 20k completed
TODO award rollover complete, sounds
*/


#include <freewpc.h>

//U8 oyl_count;




static void award_oyl_completed (void)
{
//	bounded_increment (oyl_count, 99);
	score (SC_20K);
	
	/* Show animation */
//	deff_start (DEFF_ROLLOVER_COMPLETED);
	/* Flash and turn off inlane lamps */
	lamplist_apply (LAMPLIST_OYL, lamp_off);
//	lamplist_apply (LAMPLIST_OYL, lamp_flash_on);
//	task_sleep_sec (1);
//	lamplist_apply (LAMPLIST_OYL, lamp_flash_off);
}

static bool oyl_completed (void)
{
	if (lamp_test (LM_OYL_O)
		&& lamp_test (LM_OYL_Y)
		&& lamp_test (LM_OYL_L))
		return TRUE;
	else
		return FALSE;
}


static void check_oyl (void)
{
	if (oyl_completed () == TRUE)
	{
		award_oyl_completed ();
	}
}





CALLSET_ENTRY (oyl, sw_left_button)
{
	if (in_game)
		lamplist_rotate_previous (LAMPLIST_OYL, lamp_matrix);
}

CALLSET_ENTRY (oyl, sw_right_button)
{
	if (in_game)
		lamplist_rotate_next (LAMPLIST_OYL, lamp_matrix);
}

CALLSET_ENTRY (oyl, sw_oyl_o)
{
	lamp_on (LM_OYL_O);
	check_oyl ();
	score (SC_1K);
}

CALLSET_ENTRY (oyl, sw_oyl_y)
{
	lamp_on (LM_OYL_Y);
	check_oyl ();
	score (SC_1K);
}

CALLSET_ENTRY (oyl, sw_oyl_l)
{
	lamp_on (LM_OYL_L);
	check_oyl ();
	score (SC_1K);
}


CALLSET_ENTRY (oyl, start_ball)
{
	/* Turn off all inlanes at start of ball */
	lamplist_apply (LAMPLIST_OYL, lamp_off);
//	oyl_count = 0;
}

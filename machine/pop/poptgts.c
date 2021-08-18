/*
Handle all 6 popeye targets

Lamps
35: pop e1
36: pop y
37: pop e2
53: popeye p1
54: popeye o
55: popeye p2


Switches
26: pop e1, standup
27: pop y, standup
28: pop e2, standup
71: pop p1, standup
72: pop o, standup
73: pop p2, standup

RULES:
Poptgts: light pop-eye targets, 1k target, 250k complete
TODO award completion, sounds
*/


#include <freewpc.h>



static void award_poptgts_completed (void)
{
	score (SC_250K);
	
	/* Show animation */
//	deff_start (DEFF_ROLLOVER_COMPLETED);
	/* Flash and turn off popeye lamps */
	lamplist_apply (LAMPLIST_POPTGTS, lamp_off);
	lamplist_apply (LAMPLIST_POPTGTS, lamp_flash_on);
	task_sleep_sec (1);
	lamplist_apply (LAMPLIST_POPTGTS, lamp_flash_off);
}


static bool poptgts_completed (void)
{
	if (lamp_test (LM_POP_P1)
		&& lamp_test (LM_POP_O)
		&& lamp_test (LM_POP_P2)
		&& lamp_test (LM_POP_E1)
		&& lamp_test (LM_POP_Y)
		&& lamp_test (LM_POP_E2))
		return TRUE;
	else
		return FALSE;
}


static void check_poptgts (void)
{
	if (poptgts_completed () == TRUE)
	{
		award_poptgts_completed ();
	}

}



CALLSET_ENTRY (poptgts, sw_pop_p1)
{
	lamp_on (LM_POP_P1);
	check_poptgts ();
	score (SC_1K);
}

CALLSET_ENTRY (poptgts, sw_pop_o)
{
	lamp_on (LM_POP_O);
	check_poptgts ();
	score (SC_1K);
}

CALLSET_ENTRY (poptgts, sw_pop_p2)
{
	lamp_on (LM_POP_P2);
	check_poptgts ();
	score (SC_1K);
}

CALLSET_ENTRY (poptgts, sw_pop_e1)
{
	lamp_on (LM_POP_E1);
	check_poptgts ();
	score (SC_1K);
}

CALLSET_ENTRY (poptgts, sw_pop_y)
{
	lamp_on (LM_POP_Y);
	check_poptgts ();
	score (SC_1K);
}

CALLSET_ENTRY (poptgts, sw_pop_e2)
{
	lamp_on (LM_POP_E2);
	check_poptgts ();
	score (SC_1K);

}


CALLSET_ENTRY (poptgts, start_ball)
{
//switch off lamps
	lamplist_apply (LAMPLIST_POPTGTS, lamp_off);
}


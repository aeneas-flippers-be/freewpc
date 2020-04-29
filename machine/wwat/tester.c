
#include <freewpc.h>

extern U8 lostmine_nrshot; //lostmine.o in machine2
extern U8 lostmine_nrshotgold;  //lostmine.o in machine2

CALLSET_ENTRY (tester, sw_right_inlane)
{
//hurry mode
//	hurry_start ();

//man overboard
	flag_on (FLAG_BFCLIGHT);
//	wpman_start ();

//dam mode
	dam_start ();

//quickmb
//	free_timer_restart (TIM_SKILL, TIME_4S);

//wetwilly
//	raftnr = 9;

//waterfall
//	fall_start ();

//goldrush
//	flag_on (FLAG_BFCLIGHT);
	flag_on (FLAG_BFCKEY);
	lostmine_nrshot = 2;
	lostmine_nrshotgold = 3;
//ready to shoot lostmine

//map mode then dam mode then wpool mode
	flag_on (FLAG_BFCMAP);
//	flag_test (FLAG_DAM_LIT);
	global_flag_on (GLOBAL_FLAG_WPOOLLIT);
}


#include <freewpc.h>

CALLSET_ENTRY (jets, sw_left_jet, sw_right_jet, sw_bottom_jet)
{

   score (SC_5K);

}


/* TEST */
CALLSET_ENTRY (testbsd, sw_left_inlane)
{
	sol_enable (SOL_LEFT_GATE);
	task_sleep (TIME_1S);
	sol_disable(SOL_LEFT_GATE);
}

CALLSET_ENTRY (testbsd, sw_right_inlane)
{
	sol_enable (SOL_SHOOTER_RAMP);
	task_sleep (TIME_1S);
	sol_disable(SOL_SHOOTER_RAMP);
}


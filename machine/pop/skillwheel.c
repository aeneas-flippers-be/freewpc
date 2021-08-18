/* 
Basic implemetation

RULES
Skillwheel: rotate wheel and detect ball
TODO handle multiple balls, sounds, detect hole

*/


#include <freewpc.h>
#include <wheel.h>

CALLSET_ENTRY (skillwheel, sw_launch_button)
{
	//TODO wheel stops after 10 seconds - check here if its turning, if not only start wheel and don't launch ball
	wheel_start ();	
	sol_request (SOL_AUTOFIRE);
}

CALLSET_ENTRY (skillwheel, serve_ball, ball_search)
{
	wheel_start ();	
}

CALLSET_ENTRY (skillwheel, bonus, stop_game)
{
	wheel_stop ();	
}


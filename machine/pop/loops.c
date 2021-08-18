
/*
Light loops, score loops, handle gates

Lamps
44: left inlane, white
45: right inlane, white
51: left loop arrow
16: right loop arrow


Switches
75: left inlane, ingame
78: right inlane, ingame
25: left loop, ingame
33: right loop opto, opto, ingame


Coils
left gate: driver(duty), sol=SOL_LEFT_GATE, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60
right gate: driver(duty), sol=SOL_RIGHT_GATE, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60


Rules:
Loops: Inlanes / loop arrows / gates: similar to original rules
Lampset alternates with flipper buttons, starts with right inlane after wheel
Lit inlane lights loop shot arrow
Shooting lit loop opens top gate and awards loop shot

TODO loop shot award
TODO sounds
TODO multiple loops, now only 1 can be made
TODO disable gates automatically after delay

*/


#include <freewpc.h>
#include <left_gate.h>
#include <right_gate.h>





/* handle loop shots */
CALLSET_ENTRY (loops, sw_right_loop_opto)
{
	if (!in_live_game)
		return;

	if (free_timer_test (TIM_LLOOP))
	{
		right_gate_stop ();
		free_timer_stop (TIM_LLOOP);
		lamp_off (LM_LEFT_LOOP_ARROW);
		callset_invoke (left_loop_made);
	}
	else
	{
		if (lamp_test (LM_RIGHT_LOOP_ARROW))
		{
			left_gate_start ();
			free_timer_start (TIM_RLOOP, TIME_2S);
		}
	}
}

CALLSET_ENTRY (loops, sw_left_loop)
{
	if (!in_live_game)
		return;

	if (free_timer_test (TIM_RLOOP))
	{
		left_gate_stop ();
		free_timer_stop (TIM_RLOOP);
		lamp_off (LM_RIGHT_LOOP_ARROW);
		callset_invoke (right_loop_made);
	}
	else
	{
		if (lamp_test (LM_LEFT_LOOP_ARROW))
		{
			right_gate_start ();
			free_timer_start (TIM_LLOOP, TIME_2S);
		}
	}
}


/* failed to make loop shot around */
CALLSET_ENTRY (loops, sw_oyl_o, sw_oyl_y, sw_oyl_l, tilt, end_game)
{
	left_gate_stop ();
	right_gate_stop ();
}


/* handle inlanes */
CALLSET_ENTRY (loops, sw_right_inlane)
{
	if (lamp_test (LM_RIGHT_INLANE))
	{
		lamp_on (LM_LEFT_LOOP_ARROW);		
	}
}

CALLSET_ENTRY (loops, sw_left_inlane)
{
	if (lamp_test (LM_LEFT_INLANE))
	{
		lamp_on (LM_RIGHT_LOOP_ARROW);		
	}
}

/* alternate light with flippers */
CALLSET_ENTRY (loops, sw_left_button)
{
	if (in_game)
		lamplist_rotate_previous (LAMPLIST_INLANES, lamp_matrix);
}

CALLSET_ENTRY (loops, sw_right_button)
{
	if (in_game)
		lamplist_rotate_next (LAMPLIST_INLANES, lamp_matrix);
}


/* init */
CALLSET_ENTRY (loops, start_ball)
{
	/* Turn off all inlanes at start of ball and loop arrows */
	lamplist_apply (LAMPLIST_INLANES, lamp_off);
	lamp_off (LM_RIGHT_LOOP_ARROW);
	lamp_off (LM_LEFT_LOOP_ARROW);
	lamp_on (LM_RIGHT_INLANE);
}

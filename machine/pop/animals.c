
/*
Left animal ramp

Lamps
73: animal rhino
67: animal panda
68: animal leopard
75: animal eagle
62: animal dolphin

63: left popper arrow  (=instand mb)

85: animal jackpot (= upper pf)

21: island rhino
22: island leopard
23: island eagle
24: island dolphin
28: island panda


Switches
68: animal rhino, ingame
67: animal panda, ingame
66: animal tiger, ingame
65: animal eagle, ingame
64: animal dolphin, ingame

84: animal jackpot, ingame  -- upper pf entry

Devices
Left Hole: left popper, left popper sw

G6: animal ramp fl, flash
H4: animal diverter, duty(SOL_DUTY_75), time(TIME_66MS)


RULES
Animals: Shoot left scoop, ball kicks up into animal ramp
Enter animal ramp from upper pf
get 5 shots for each ball on the ramp, up to 4 seconds

*/


#include <freewpc.h>
U8 animal_shots;


CALLSET_ENTRY (animals, sw_left_button)
{
	if (!in_live_game)
		return;

	if (free_timer_test (TIM_ANIMAL) && animal_shots > 0)
	{
		animal_shots--;
		sol_request (SOL_ANIMAL_DIV);
	}
}


CALLSET_ENTRY (animals, dev_left_hole_kick_attempt, sw_animal_jackpot)
{
	if (!in_live_game)
		return;

	if (free_timer_test (TIM_ANIMAL))
		animal_shots = animal_shots + 5;
	else
		animal_shots = 5;

	free_timer_restart (TIM_ANIMAL, TIME_4S);
}

CALLSET_ENTRY (animals, start_ball)
{
	animal_shots = 0;
}

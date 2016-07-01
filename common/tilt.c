/*
 * Copyright 2006-2011 by Brian Dominy <brian@oddchange.com>
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

/*  AE mix james and brian */

/**
 * \file
 * \brief Common tilt functions
 *
 * This module handles all of the tilt switches, start game-specific
 * effects when they occur, and updates the core state machines
 * appropriately (in the case of a slam tilt, this will abort the
 * game).  It also provides the display and lamp effects that go along
 * with them.
 */

#include <freewpc.h>
#include <coin.h>

/** The number of tilt warnings that have been issued on this ball. */
U8 tilt_warnings;
bool in_tilt_warning;

/* A timer that allows tilt to settle during endball before
   proceeding to the next ball. */
free_timer_id_t tilt_ignore_timer;


/** Lamp effect function for a leff that turns all lights off.
 * Used by the system-defined tilt function. */
void no_lights_leff (void)
{
	for (;;)
		task_sleep_sec (5);
}


void tilt_warning_leff (void)
{
	task_sleep (TIME_500MS);
	leff_exit ();
}


void tilt_warning_task (void) {
	task_sleep (TIME_2S);
	in_tilt_warning = FALSE;
	task_exit ();
}




CALLSET_ENTRY (tilt, sw_tilt)
{
	extern U8 in_tilt;

	/* Ignore tilt switch activity while already in tilt state.
	 * But restart the timer that tells us that the tilt is still
	 * moving, so we can delay endball. */
	if (in_tilt || in_tilt_warning)
	{
		free_timer_restart (tilt_ignore_timer, TIME_2S);
		return;
	}

	else if (++tilt_warnings >= system_config.tilt_warnings)
	{
		/* Warnings exceeded... tilt the current ball */
		in_tilt = TRUE;
		in_tilt_warning = FALSE;
		sound_reset ();
#ifdef CONFIG_GI
		gi_disable (PINIO_GI_STRINGS);
#endif
		deff_stop_all ();
		leff_stop_all ();

#ifdef DEFF_TILT
		deff_start (DEFF_TILT);
#endif
#ifdef LEFF_TILT
		leff_start (LEFF_TILT);
#endif

		free_timer_restart (tilt_ignore_timer, TIME_2S);
		in_tilt = TRUE;
		set_valid_playfield (); // this handles the special case where the game was tilted with ball on shooter lane before it is fired (see below)
		flipper_disable ();
		callset_invoke (tilt);
		task_remove_duration (TASK_DURATION_LIVE);
		task_duration_expire (TASK_DURATION_LIVE);
		audit_increment (&system_audits.tilts);
		audit_increment (&system_audits.plumb_bob_tilts);

	//at this point ball should drain and game/end_ball should take over and tilt condition will be reset below

	//unless already in bonus
		if (in_bonus) 	callset_invoke (bonus_complete); // if tilted, player gets no bonus

	//unless ball stuck on shooter so handle that case
		if (switch_poll_logical (MACHINE_SHOOTER_SWITCH) ) launch_ball();

	}
	else
	{
		// Give a warning this time
		in_tilt_warning = TRUE;

#ifdef DEFF_TILT_WARNING
		deff_start (DEFF_TILT_WARNING);
#endif
#ifdef LEFF_TILT_WARNING
		leff_start (LEFF_TILT_WARNING);
#endif
		callset_invoke (tilt_warning);
		task_create_gid1 (GID_TILT_WARNING, tilt_warning_task); //make a few second pause
	}
}


CALLSET_ENTRY (tilt, sw_slam_tilt)
{
#ifdef SW_COIN_DOOR_CLOSED
	/* Ignore slam tilt switch entirely while coin door is open,
	and configured for tournament mode.  This is to avoid inadvertent slam tilts
	while dealing with problems. */
	if (system_config.tournament_mode && !switch_poll_logical (SW_COIN_DOOR_CLOSED))
		return;

	/* Ignore right after a coin door open/close */
	if (nonball_event_did_follow (sw_coin_door_closed, sw_slam_tilt))
		return;
#endif

	/* Kill the current game */
	stop_game ();

	/* Disable coins briefly, the whole point of the slam tilt */
	event_can_follow (sw_slam_tilt, sw_coin, TIME_5S);

	/* Start the slam tilt effect */
	callset_invoke (slam_tilt);
	deff_start (DEFF_SLAM_TILT);
	leff_restart (LEFF_TILT);

	/* Audit the event */
	audit_increment (&system_audits.slam_tilts);

	/* When slamtilt penalty adjustment is enabled, remove a credit. */
	if (price_config.slamtilt_penalty)
		remove_credit ();

	/* Wait for the switch to clear before rebooting. */
#ifdef SW_SLAM_TILT
	task_sleep_sec (1);
	for (;;)
	{
		task_sleep (TIME_500MS);
		if (!switch_poll (SW_SLAM_TILT))
			break;
	}
#endif
	warm_reboot ();
}


CALLSET_ENTRY (tilt, bonus_complete)
{
	/* Clear the tilt flag.  Note, this is not combined
	with the above to handle tilt while bonus is running. */
	if (in_tilt)
	{
		/* Wait for tilt bob to settle */
		while (free_timer_test (tilt_ignore_timer))
			task_sleep (TIME_100MS);

		/* Cancel the tilt effects */
#ifdef DEFF_TILT
		deff_stop (DEFF_TILT);
#endif
#ifdef LEFF_TILT
		leff_stop (LEFF_TILT);
#endif
		in_tilt = FALSE;
		in_tilt_warning = FALSE;
	}
}


CALLSET_ENTRY (tilt, start_ball)
{
	tilt_warnings = 0;
	in_tilt_warning = FALSE;
}


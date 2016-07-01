/*
 * Copyright 2006-2010 by Brian Dominy <brian@oddchange.com>
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
By Aeneas for Whitewater

# GAME_OBJS  = .text page, no labeling or prototype needed 
# GAME_PAGED_OBJS = page 59, labelled MACHINE, prototypes use __machine__ 
# GAME_TEST_OBJS = page 58, no labeling or prototype needed  
# EFFECTS = page 57, 
# COMMON = page 56, , prototypes use __common__
# GAME2_OBJS = page 55, labelled MACHINE2, prototypes use __machine2__
# GAME3_OBJS = page 54, labelled MACHINE3, prototypes use __machine3__
# GAME4_OBJS = page 53, labelled MACHINE4, prototypes use __machine4__
# GAME5_OBJS = page 52, labelled MACHINE5, prototypes use __machine5__
*/


/* helper */
__machine__ void printf_millions (U8 n);

/* bigfoothead */
__machine__ void bfh_showface_cw (void);
__machine__ void bfh_showface_ccw (void);
__machine__ void bfh_rotate_ccw (U8 nrturns);
__machine__ void bfh_rotate_cw (U8 nrturns);


/* dammode */
__machine__ void dam_start (void);

/* lock */
__machine__ void lock_lockball (void);
__machine__ void lock_unlockball (void);

 /* mapmode.c */
__machine__ void map_start (void);

/* rafts */
__machine__ void raft_proceed (void);
__machine__ void raft_award_hazard (void);
__machine__ void raft_hz_reset (void);
__machine__ void raft_reset (void);
__machine__ void raft_next2rafts (void);

/* rafthurryup.c */
__machine__ void hurry_start (void);
__machine__ void hurry_stop (void);

/* wpoolmodes */
__machine__ void wp5x_start (void);
__machine__ void wpm_next_award (void);

/* riverclass.c */
__machine__ void rivcl_increase_class (void);

/* simpleshots.c */
__machine__ void lamps_out (void);

/* kickback */
__machine__ void kickback_enable (void);

/* wpwpchall.c */
__machine__ void wpch_start (void);




/* goldrush.c */
__machine2__ void gold_start (void);

 /* mball.c */
__machine2__ void mball_start (void);

/* quickmb.c */
__machine2__ void qmball_start (void);

/* waterfall */
__machine2__ void fall_start (void);

/* wp manoverb.c */
__machine2__ void wpman_start (void);

/* wetwilly.c */
__machine2__ void wet_start (void);

 /* wizard.c */
__machine2__ void wizard_start (void);



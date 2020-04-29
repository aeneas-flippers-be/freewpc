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
# GAME_TEST_OBJS = page 58, no labeling or prototype needed  
# EFFECTS = page 57, 
# COMMON = page 56, , prototypes use __common__
# GAME_PAGED_OBJS = page 59, labelled MACHINE, prototypes use __machine__ 
# GAME2_OBJS = page 55, labelled MACHINE2, prototypes use __machine2__
# GAME3_OBJS = page 54, labelled MACHINE3, prototypes use __machine3__
# GAME4_OBJS = page 53, labelled MACHINE4, prototypes use __machine4__
# GAME5_OBJS = page 52, labelled MACHINE5, prototypes use __machine5__
*/


/* 
 * GAME_OBJS = bbash.o bigfoothead.o bigfootdiv.o bigfoottgt.o cavehurry.o deffsobj.o jets.o kickback.o lock.o rafts.o rafthurryup.o \
 * redtgt.o wpoolmodes.o  
 */

/* bbash */
__machine__ void bash_start (void);

/* bigfoothead */
__machine__ void bfh_showface_cw (void);
__machine__ void bfh_showface_ccw (void);
__machine__ void bfh_rotate_ccw (U8 nrturns);
__machine__ void bfh_rotate_cw (U8 nrturns);

/* bigfoottgt */
__machine__ void bftgt_reset (void);

/* cavehurry */
__machine__ void cave_start (void);
__machine__ void cave_stop (void);

/* deffsobj */
__machine__ void printf_millions (U8 n);

/* kickback */
__machine__ void kickback_enable (void);

/* lock */
__machine__ void lock_lockball (void);
__machine__ void lock_unlockball (void);
__machine__ void lock_lamps_off (void);
__machine__ void lock_lamp_update (void);

/* rafts */
__machine__ void raft_proceed (void);
__machine__ void raft_award_hazard (void);
__machine__ void raft_hz_lamps_tri_off (void);
__machine__ void raft_raftlamps_on (U8 myraftnr);
__machine__ void raft_raftlamps_off (void);
__machine__ void raft_hz_reset (void);
__machine__ void raft_reset (void);
__machine__ void raft_next2rafts (void);
__machine__ void raftmode_on (void);
__machine__ void raftmode_off (void);
__machine__ void raft_score_hz3_nowayout (bool bsilent);	//started in lock.c now

/* riverhurry.c */
__machine__ void riverhurry_start (void);
__machine__ void riverhurry_stop (void);

/* wpoolmodes */
__machine__ void wpm_next_award (void);



/*
 * pages machine1
 * GAME_PAGED_OBJS = bigfootcave.o combos.o lanes.o rivertgt.o simpleshots.o
*/


/* rivertgt */
__machine__ void river_lamps_off (void);
__machine__ void river_lamps_on (void);
__machine__ void river_off (void);



/*
 * machine2 
 * GAME2_OBJS = dammode.o extraball.o goldrush.o lostmine.o multimill.o mball.o riverclass.o quickmb.o skill.o waterfall.o wetwilly.o wizard.o wpmanoverb.o wp5xpf2.o wpwpchall.o
*/

/* dammode */
__machine2__ void dam_start (void);

/* goldrush.c */
__machine2__ void gold_start (void);

 /* mball.c */
__machine2__ void mball_start (void);

/* riverclass.c */
__machine2__ void rivcl_increase_class (void);

/* quickmb.c */
__machine2__ void qmball_start (void);
__machine2__ void qmball_flash_hz (void);

/* waterfall */
__machine2__ void fall_start (void);

/* wetwilly.c */
__machine2__ void wet_start (void);

 /* wizard.c */
__machine2__ void wizard_start (void);

/* wp manoverb.c */
__machine2__ void wpman_start (void);

/* wp5xpf and wp5xpf2 */
__machine2__ void wp5x_start (void);

/* wpwpchall.c */
__machine2__ void wpch_start (void);



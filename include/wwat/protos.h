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
void bash_start (void);

/* bigfoothead */
void bfh_showface_cw (void);
void bfh_showface_ccw (void);
void bfh_rotate_ccw (U8 nrturns);
void bfh_rotate_cw (U8 nrturns);

/* bigfoottgt */
void bftgt_reset (void);

/* cavehurry */
void cave_start (void);
void cave_stop (void);

/* deffsobj */
void printf_millions (U8 n);

/* kickback */
void kickback_enable (void);

/* lock */
void lock_lockball (void);
void lock_unlockball (void);
void lock_lamps_off (void);
void lock_lamp_update (void);

/* riverhurry.c */
void riverhurry_start (void);
void riverhurry_stop (void);

/* wpoolmodes */
void wpm_next_award (void);

/* rafts */
void raft_proceed (void);
void raft_award_hazard (void);
void raft_hz_lamps_tri_off (void);
void raft_raftlamps_on (U8 myraftnr);
void raft_raftlamps_off (void);
void raft_hz_reset (void);
void raft_reset (void);
void raft_next2rafts (void);
void raftmode_on (void);
void raftmode_off (void);
void raft_score_hz3_nowayout (bool bsilent);	//started in lock.c now



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





/*******************************************************************
 * machine page 4
 ********************************************************************/

/* ww_modes.c */
__machine4__ void set_ww_mode (U8 mode_flag);

__machine4__ __boolean get_ww_mode (U8 mode_flag);




/*
 * Copyright 2016 Aeneas Verhe
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
placeholder to define vars that are used by multiple files, keep in game_objs
*/

#include <freewpc.h>

__local__ U8 caveshots;  //bigfootcave bonus.c jets
__local__ U8 bigfoot_found; //bigfootcave

__local__ U8 combos_nrdrops;  //combos
__local__ U8 combos_nrrloops;  
__local__ U8 combos_3made;    
__local__ U8 combos_4made;  

score_t gold_score; //goldrush
U8 gold_hitcount;  //goldrush bonus.c deffs3.c

U8 jets_extra_hit;    //jets bonus.c

U8 lock_balls_in_devlock;  //locks.c    balls actually present in physical lock

__local__ U8 lock_player_locks_lit; //locks.c wpwpchall.c goldrush.c quickmb.c wp5xpf2.c

__local__ U8 lostmine_nrshot;      //lostmine.c bonus.c

U8 mmil_count;  //multimill deffs3.c

U8 qmb_jp_mul;  //quickmb deffs3.c

__local__ U8 raftnr;  //rafts.c bonus.c lock.c					current raft
//__local__ U8 raft_perfectcount;  //rafts.c bonus.c		how many times perfect raft shots are made

__local__ U8 hurry_counter;  //rafthurryup.c bonus.c

bool rivtarget1;	//river letter spelled or not
bool rivtarget2;
bool rivtarget3;
bool rivtarget4;
bool rivtarget5;

__local__ U8 riverclass;  //riverclass bonus.c deffs3.c jets.c lock.c

__local__ U8 shots_falls;  //simpleshots.c bonus.c deffs3.c
__local__ U8 shots_secretpass;  //simpleshots.c bonus.c

__local__ U8 skill_ramp_made;  //skill deffs3.c		nr of skillshots made, shown in deff and points made
__local__ U8 skill_bigf_made;  //skill deffs3.c		nr of skillshots made, shown in deff and points made
__local__ U8 skill_raftnr;	//skill					max skillshot raft made - for start loop lamps
U8 skill_count;				//skill deffs3

U8 wpch_jackpots_made;  //wpwpchall deffs3.c


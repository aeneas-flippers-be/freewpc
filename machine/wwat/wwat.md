#--------------------------------------------------------------------------
# Machine description for Whitewater
# (C) Copyright 2016 Aeneas Verhe
#
# See tools/genmachine for more information about the format of this file.
#--------------------------------------------------------------------------
# This file describes many characteristics of a pinball machine,
# mostly physical stuff, although some rules can be coded here also.

##########################################################################
# General section (before a [section] header is given.
# Miscellaneous parameters are specified here.
##########################################################################
Title: bigfoot
include platform/wpc/wpc-fliptronic.md

Pinmame-Zip: ww_l5.zip
Pinmame-ROM: wwatr_l5.rom
#Lamp-Matrix-Width:
#Lamp-Matrix-Height:


##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################

define MACHINE_WWAT
define MACHINE_NUMBER 518
define MACHINE_HAS_UPPER_RIGHT_FLIPPER
define MACHINE_BALL_SAVE_TIME 1
define MACHINE_CUSTOM_AMODE

define MACHINE_GRAND_CHAMPION_INITIALS { 'A', 'E', 'V' }
define MACHINE_GRAND_CHAMPION_SCORE { 0x00, 0x20, 0x00, 0x00, 0x00 }
define MACHINE_HIGH_SCORE_INITIALS { 'M', 'A', 'Y' }, { 'K', 'A', 'T' }, { 'M', 'A', 'Y' }, { 'K', 'A', 'T' }
define MACHINE_HIGH_SCORES { 0x00, 0x17, 0x50, 0x00, 0x00 }, { 0x00, 0x15, 0x00, 0x00, 0x00 }, { 0x00, 0x12, 0x50, 0x00, 0x00 }, { 0x00, 0x10, 0x00, 0x00, 0x00 }


##########################################################################
# Lamp Description
# The key is given in column/row format.  The first parameter must be
# the lamp name.  Optionally you can specify a color, and x() and y()
# for the location on the playfield.  Only a subset of lamp colors are
# recognized; see tools/genmachine for details.  Lamp location is
# given in terms of the Lamp-Matrix-Width and Lamp-Matrix-Height.
##########################################################################
[lamps]
11: shoot again, shoot-again, orange, ball-save
12: kickback, red
13: left outlane, white
14: left inlane, red
15: right inlane, red
16: right outlane, white
17: light spine, yellow
18: 6x multi, white
21: river r1, blue
22: river i, blue
23: river v, blue
24: river e, blue
25: river r2, blue
26: hz no way out, orange
27: lock 3, green
28: lock 2, green
31: raft 7, yellow
32: raft 8, yellow
33: wet willies, yellow
34: ramp mil, red
35: hz spine chiller, orange
36: lock left, green
37: 2x multi, white
38: 3x multi, white
41: 3bank center, red
42: 3bank bottom, red
43: lock 1, green
44: 3bank top, red
45: hz disdrop, orange
46: lock right, green
47: 4x multi, white
48: 5x multi, white
51: hz boom bend, orange
52: hz boulder garden, orange
53: hz insanity falls, orange
54: hz bigfoot bluff, orange
55: light whirlpool, red
56: collect eb, extra-ball, orange
57: bd whirlp chall, red
58: bd man overbd, red
61: raft 1, yellow
62: raft 2, yellow
63: raft 3, yellow
64: raft 4, yellow
65: raft 5, yellow
66: raft 6, yellow
67: 2bank up, white
68: 2bank low, white
71: whirlpool 1, blue
72: whirlpool 2, blue
73: whirlpool 3, blue
74: whirlpool 4, blue
75: whirlpool 5, blue
76: whirlpool 6, blue
77: upf multi jp, red
78: upf bigfoot jp, red
81: bd light eb, red
82: bd adv raft, red
83: bd mystery, red
84: bd 5x pf, red

##########################################################################
# Switch Description
# The key is in column/row format.  The first parameter must be the switch
# name.  Options can be given in any order:
#    ingame - only service the switch during a game
#    intest - also service the switch in test mode
#    novalid - tripping this switch does NOT mark ball in play
#    standup - this is a standup
#    button - this is a button
#    edge - this switch should be serviced on either transition
#    opto - this switch is optical and activates on closed->open
#
# These parameters mark various well-known switches.  Only one of these
# can exist per type:
#    outhole, slam-tilt, tilt, shooter, start-button, buyin-button
#
# Use sound() to invoke a sound call automatically when the switch activates.
# Use lamp() to flicker a lamp automatically on activation.  TODO:
#   this requires the c_name, and not the friendly md name.
# Use c_decl() to override the default name of the switch event.
#
##########################################################################
[switches]
11: right flipper, button, intest, c_decl(sw_right_button)
12: left flipper, button, intest, c_decl(sw_left_button)
13: start button, yellow, start-button, cabinet, intest
14: plumb bob tilt, c_decl(sw_tilt), cabinet, tilt, ingame, novalid
15: outhole, outhole, service, novalid, intest, noscore
16: left jet, ingame, c_decl(sw_jet)
17: right jet, ingame, c_decl(sw_jet)
18: bottom jet, ingame, c_decl(sw_jet)
21: slam tilt, slam-tilt, ingame, cabinet, novalid, noscore
22: coin door closed, noscore, novalid
25: kickback, ingame
26: left inlane, ingame
27: right inlane, ingame
28: right outlane, ingame
31: river r2, ingame, standup
32: river e, ingame, standup
33: river v, ingame, standup
34: river i, ingame, standup
35: river r1, ingame, standup
36: 3bank top, ingame, standup
37: 3bank center, ingame, standup
38: 3bank bottom, ingame, standup
41: lock left, ingame, standup
42: lock right, ingame, standup
43: left loop, ingame
44: right loop, ingame
45: secret passage, ingame
46: left ramp enter, ingame
47: rapids enter, ingame
48: canyon entrance, ingame
51: left slingshot, ingame, c_decl(sw_sling)
52: right slingshot, ingame, c_decl(sw_sling)
53: ball shooter, edge, shooter, novalid, debounce(TIME_200MS)
54: jets lower, ingame
55: jets right, ingame
56: extra ball, ingame, standup
57: canyon main, ingame, opto
58: bigfoot cave, ingame
61: mine popper, ingame, opto
62: whirlpool exit, ingame, opto
63: lock 1, opto, ingame
64: lock 2, opto, ingame
65: lock 3, opto, ingame
66: left ramp main, ingame, opto
68: disas drop enter, ingame, opto
71: rapids main ramp, ingame
73: 2bank low, ingame
74: 2bank up, ingame
75: disas drop main, ingame
76: Trough 1, noscore, novalid
77: Trough 2, noscore, novalid
78: Trough 3, noscore, novalid
86: bfhead back, opto, novalid
87: bfhead front, opto, novalid



##########################################################################
# Drives
# This describes the names of the solenoid/motor drives.
# Hn = high power solenoids
# Ln = low power solenoids
# Gn = general purpose solenoids
# etc.
#
# The following options are supported:
#    flash - this is a flasher (default is solenoid, flash implies nosearch)
#    motor - this is a motor (default is solenoid)
#    nosearch - do not activate this during ball search
#
# The following options denote well-known drives:
#    knocker, ballserve
#
##########################################################################
[drives]
#H = high power J130
#### these are all 50v power
H1: outhole, duty(SOL_DUTY_50), time(TIME_133MS)
H2: Ball Release, ballserve, duty(SOL_DUTY_25), time(TIME_133MS)
H3: mine popper, duty(SOL_DUTY_75), time(TIME_100MS)
H4: lock popper, duty(SOL_DUTY_100), time(TIME_133MS)
H5: kickback, duty(SOL_DUTY_50), time(TIME_100MS)
H6: bigfoot div, duty(SOL_DUTY_50), time(TIME_133MS)
H7: knocker, knocker, duty(SOL_DUTY_75), time(TIME_50MS), nosearch
H8: Backglass, flash

#L = low power J127
#### these are all 50v power
L1: wet willy head, flash
L2: left slingshot, duty(SOL_DUTY_100), time(TIME_33MS)
L3: right slingshot, duty(SOL_DUTY_100), time(TIME_33MS)
L4: left jet, duty(SOL_DUTY_75), time(TIME_50MS)
L5: right jet, duty(SOL_DUTY_75), time(TIME_50MS)
L6: bottom jet, duty(SOL_DUTY_75), time(TIME_50MS)
L7: bg raft, flash
L8: bg riders, flash

# G = J126 on Power Driver Board
G1: bigfoot body fl, flash
G2: r mountain fl, flash
G3: l mountain fl, flash
G4: ul pf fl, flash
G5: Insanity falls fl, flash
G6: mine popper fl, flash
G7: wpool enter fl, flash
G8: bigfoot cave fl, flash

# A = J122 pins 1-2-3-4
#### these are all 20v power
A1: bf enable, motor, nosearch
A2: bf drive, motor, nosearch
A3: chase clock
A4: chase data

# F = J902 on Fliptronic II
#### these are all 50v power

[templates]
outhole: driver(outhole), sol=SOL_OUTHOLE, swno=SW_OUTHOLE, swevent=sw_outhole
left sling: driver(sling), sw=SW_LEFT_SLINGSHOT, sol=SOL_LEFT_SLINGSHOT
right sling: driver(sling), sw=SW_RIGHT_SLINGSHOT, sol=SOL_RIGHT_SLINGSHOT
left jet: driver(jet), sw=SW_LEFT_JET, sol=SOL_LEFT_JET
right jet: driver(jet), sw=SW_RIGHT_JET, sol=SOL_RIGHT_JET
lower jet: driver(jet), sw=SW_BOTTOM_JET, sol=SOL_BOTTOM_JET
bigfdiv: driver(duty2), sol=SOL_BIGFOOT_DIV, timeout=TIME_3S, ontime=TIME_33MS, duty_mask=DUTY_MASK_50
kickback Driver: driver(spsol), sw=SW_KICKBACK, sol=SOL_KICKBACK, ontime=12, offtime=18

bigfhead: driver(bivar3), dir_sol=SOL_BF_DRIVE, enable_sol=SOL_BF_ENABLE, back_sw=SW_BFHEAD_BACK, front_sw=SW_BFHEAD_FRONT, includetest(yes)



##########################################################################
# General Illumination
##########################################################################
[gi]
0: PF Upper
1: PF Middle
2: PF Lower
3: BG boat
4: BG sky

##########################################################################
# Tests
# These are additional test items that should appear in the TESTS menu.
##########################################################################
#Templates that use include test must still be listed here otherwise it won't be listed in the test menu
[tests]
bigfhead:


##########################################################################
# Containers
# These denote devices that can hold, count, and eject pinballs.
# The key is the name of the device.  The first parameter is the name
# of the solenoid that kicks out a ball.  The 'trough' parameter should
# be specified on the single trough device.  The 'init_max_count'
# parameter should say how many balls are normally held in this device
# at startup.  The remaining parameters are the names of the switches
# that count pinball, in front from entry to exit.
##########################################################################
[containers]
Trough: Ball Release, trough, init_max_count(3), \
	 Trough 3, Trough 2, Trough 1
Lostmine: mine popper, mine popper, init_max_count(0)
Lock: lock popper, lock 3, lock 2, lock 1, init_max_count(0)




#------------------------------------------------------------------------
# The remaining sections describe software aspects, and not the physical
# machine.
#------------------------------------------------------------------------

##########################################################################
# Items for the Feature Adjustments menu.  Parameters indicate the
# type of adjustment and the default value.
##########################################################################
[adjustments]


##########################################################################
# Items for the Feature Audits menu.
##########################################################################
[audits]

##########################################################################
# Sound calls for well-known events
##########################################################################
[system_sounds]

##########################################################################
# Music calls for well-known events
##########################################################################
[system_music]

##########################################################################
# A list of all scores needed by the game rules.
# 10 sling.c
# 10K qmball goldrush
# 20K  mball.c lock.c secretpass.c redtgt.c wizard
# 25K jets.c
# 100k 
# 250K outlanes goldrush
# 1M  multimill.c
# 10M  mball.c
# 20M  wpmanoverb
#
##########################################################################
[scores]
10:
500:
10K:
20K:
25K:
100K:
250K:
1M:
10M:
20M:


##########################################################################
# Bit flags.
##########################################################################
[flags]
kickbacklit:

bd_whirlp_played:
bd_manover_played:
bd_lighteb_played:
bd_advraft_played:
bd_mystery_played:
bd_5xpf_played:

wpoolfinished:
goldplayed:
wetfinished:
mapplayed:
dam lit:

hz1lit:
hz2lit:
hz3lit:
hz4lit:
hz5lit:
hz6lit:
hz7lit:

bfcmap:
bfclight:
bfccamera:
bfckey:



##########################################################################
# Global flags.
##########################################################################
[globalflags]
raftmode:
dam running:
cow running:
fall running:
gold running:
hurry running:
map running:
mball Running:
qmball Running:
wpch running:
wp5x running:
wpmano running:
wet running:
wiz running:
wiz mb running:

bigfoottgt1:
bigfoottgt2:
bigfootlit:

redtgt1:
redtgt2:
redtgt3:

riverr1:
riveri:
riverv:
rivere:
riverr2:

wpoollit:
pf lamps off:
skill enabled:

hold lock kickout:
hold mine kickout:
##ball at plunger:


##########################################################################
# Display effects
##########################################################################
[deffs]
#
#text page GAME_OBJS
####################
wpm mystery: PRI_GAME_MODE4, D_QUEUED+D_PAUSE
raft perfect: PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
raft up: PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
map running: runner, PRI_GAME_MODE4, D_QUEUED
bftgt: PRI_GAME_QUICK3, D_RESTARTABLE
bftgt ok: PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT+D_RESTARTABLE
dam running: runner, PRI_GAME_MODE4, D_QUEUED

#
#MACHINE_PAGE page GAME_PAGED_OBJS
##################################
jet hit: page(MACHINE_PAGE), PRI_GAME_QUICK2, D_RESTARTABLE
cave award: page(MACHINE_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
hurry running: page(MACHINE_PAGE), runner, PRI_GAME_MODE6, D_QUEUED
hurry scored: page(MACHINE_PAGE), PRI_GAME_QUICK6, D_QUEUED


#
#MACHINE2_PAGE page GAME2_OBJS
##############################
mb jackpot collected: page(MACHINE2_PAGE), PRI_GAME_QUICK4, D_QUEUED+D_TIMEOUT+D_RESTARTABLE

wet running: page(MACHINE2_PAGE), runner, PRI_GAME_MODE4, D_QUEUED
wet jackpot: page(MACHINE2_PAGE), PRI_GAME_QUICK2, D_RESTARTABLE

wpmano running: page(MACHINE2_PAGE), runner, PRI_GAME_MODE4, D_QUEUED
wpmano total: page(MACHINE2_PAGE), PRI_GAME_MODE5, D_QUEUED

fall running: page(MACHINE2_PAGE), runner, PRI_GAME_MODE4, D_QUEUED
fall ok: page(MACHINE2_PAGE), PRI_GAME_QUICK5, D_QUEUED+D_TIMEOUT

wiz running: page(MACHINE2_PAGE), runner, PRI_GAME_MODE6, D_QUEUED


#
#MACHINE3_PAGE page GAME3_OBJS
##############################
bonus: page(MACHINE3_PAGE), runner, PRI_BONUS
endgame: page(MACHINE3_PAGE), runner, PRI_BONUS

#deffs3
extra ball: page(MACHINE3_PAGE), PRI_EB, D_PAUSE+D_QUEUED
extra ball lit: page(MACHINE3_PAGE), PRI_EB, D_PAUSE+D_QUEUED
jackpot: page(MACHINE3_PAGE), PRI_GAME_QUICK2, D_RESTARTABLE
bigfoot jackpot: page(MACHINE3_PAGE), PRI_GAME_QUICK2, D_QUEUED+D_TIMEOUT+D_RESTARTABLE
mb start: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED+D_PAUSE
mb running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE4, D_QUEUED
mb restart: page(MACHINE3_PAGE), runner, PRI_GAME_MODE5, D_QUEUED
mb relocked: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
riverclass: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
kickback: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
lock lit: page(MACHINE3_PAGE), PRI_GAME_QUICK5, D_QUEUED
lock lock1: page(MACHINE3_PAGE), PRI_GAME_QUICK6, D_QUEUED+D_PAUSE
lock lock2: page(MACHINE3_PAGE), PRI_GAME_QUICK6, D_QUEUED+D_PAUSE
lock lock3: page(MACHINE3_PAGE), PRI_GAME_QUICK6, D_QUEUED+D_PAUSE
wpch start: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED
wpch running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE4, D_QUEUED
wpch jackpot: page(MACHINE3_PAGE), PRI_GAME_QUICK2, D_QUEUED+D_TIMEOUT+D_RESTARTABLE
wpch jackpot6: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
mmilcollected: page(MACHINE3_PAGE), PRI_GAME_QUICK2, D_QUEUED+D_TIMEOUT+D_RESTARTABLE
qmb start: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED+D_PAUSE
qmb running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE4, D_QUEUED
qmb up: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
gold running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE4, D_QUEUED
gold total: page(MACHINE3_PAGE), PRI_GAME_QUICK6, D_QUEUED+D_TIMEOUT+D_PAUSE
wpm dirty: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
wpm enter: page(MACHINE3_PAGE), PRI_GAME_QUICK4, D_QUEUED+D_TIMEOUT
wet qual: page(MACHINE3_PAGE), PRI_GAME_QUICK4, D_QUEUED
wet start: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED+D_PAUSE
wet ok: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED+D_TIMEOUT
wet nok: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED+D_TIMEOUT
lostmine: page(MACHINE3_PAGE), PRI_GAME_MODE3, D_QUEUED+D_TIMEOUT
redtgt kickback: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT
wp5xpf running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE3, D_QUEUED
riverletter: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_QUEUED+D_TIMEOUT+D_RESTARTABLE
river complete: page(MACHINE3_PAGE), PRI_GAME_MODE3, D_QUEUED+D_TIMEOUT
combo drop: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_TIMEOUT
combo rloop: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_TIMEOUT
combo3: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_TIMEOUT
combo4: page(MACHINE3_PAGE), PRI_GAME_QUICK3, D_TIMEOUT
map start: page(MACHINE3_PAGE), PRI_GAME_QUICK6, D_QUEUED+D_PAUSE
map found: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED
map cow: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED
wiz start: page(MACHINE3_PAGE), PRI_GAME_MODE3, D_QUEUED+D_PAUSE
wiz mb running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE5, D_QUEUED
hz1: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_TIMEOUT
hz2: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_TIMEOUT
hz3: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_TIMEOUT
hz4: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_TIMEOUT
hz5: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_TIMEOUT
hz6: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_TIMEOUT
hz7: page(MACHINE3_PAGE), PRI_GAME_MODE2, D_TIMEOUT
secret: page(MACHINE3_PAGE), PRI_GAME_MODE3, D_TIMEOUT
skill running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE1, D_QUEUED
skill: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED+D_TIMEOUT
fall nok: page(MACHINE3_PAGE), PRI_GAME_MODE5, D_QUEUED+D_TIMEOUT




##########################################################################
# Lampsets
# These denote logical groupings of lamps.
# The key is a textual name for the set.  The options specify which lamps
# are a part of that set.  You can specify 1 or more lamp values,
# separated by commas, where each value can be: 1) a single lamp name,
# 2) another lampset name, already defined, or 3) a lamp range in the
# form lamp1..lampN.
#
# The special construct PF:function indicates that a Perl subroutine
# should be used to select and sort the lamps.  Some functions are
# builtin to genmachine; others can be defined by you and included
# via the 'perlinclude' directive.
#
# Note that a lampset may contain only one lamp.  The lampset is the
# unit of 'allocation' for a lamp effect.
##########################################################################
[lamplists]
lanes: left outlane..right outlane
redtgts: 3bank top, 3bank center, 3bank bottom
river: river r1..river r2
bigfootbank: 2bank up, 2bank low
bouldermodes: bd whirlp chall, bd man overbd, bd light eb, bd adv raft, bd mystery, bd 5x pf
rivclass: 2x multi, 3x multi, 4x multi, 5x multi, 6x multi
rafts: raft 1..raft 6, raft 7, raft 8
hazards: hz no way out, hz spine chiller, hz disdrop, hz boom bend..hz bigfoot bluff
locksgreen: lock 1, lock 2, lock 3, lock left, lock right
locksthree: lock 1, lock 2, lock 3
hzdisdrop: hz disdrop
goldrush: river r2, river e, river v, river i, river r1, 3bank top, 3bank center, 3bank bottom, 2bank up, 2bank low
wpoolblue: whirlpool 1, whirlpool 2, whirlpool 3, whirlpool 4, whirlpool 5, whirlpool 6


##########################################################################
# Lamp effects
##########################################################################
[leffs]
lock kick: PRI_LEFF2, page(MACHINE3_PAGE)
lostmine kick: shared, PRI_LEFF2, page(MACHINE3_PAGE)
fl ulpf: shared, PRI_LEFF2, page(MACHINE3_PAGE)
fl lmountain: shared, PRI_LEFF2, page(MACHINE3_PAGE)
fl cave: shared, PRI_LEFF2, page(MACHINE3_PAGE)
fl bigfoot: shared, PRI_LEFF2, page(MACHINE3_PAGE)
fl wpool: shared, PRI_LEFF2, page(MACHINE3_PAGE)
hz disdrop: shared, PRI_LEFF2, page(MACHINE3_PAGE), LAMPS(HZDISDROP)
bftg: shared, PRI_LEFF2, page(MACHINE3_PAGE), LAMPS(BIGFOOTBANK)
skilllock: shared, PRI_LEFF3, page(MACHINE3_PAGE), LAMPS(LOCKSGREEN)
wpoolmode: shared, PRI_LEFF3, page(MACHINE3_PAGE), LAMPS(WPOOLBLUE)
wpoolmode2: shared, PRI_LEFF3, page(MACHINE3_PAGE), LAMPS(WPOOLBLUE)
wpoolmode3: shared, PRI_LEFF3, page(MACHINE3_PAGE), LAMPS(WPOOLBLUE)
wpoolmode6: shared, PRI_LEFF3, page(MACHINE3_PAGE), LAMPS(WPOOLBLUE)
goldrafts:  shared, PRI_LEFF3, page(MACHINE3_PAGE), LAMPS(RAFTS)
raftloop:  shared, PRI_LEFF3, page(MACHINE3_PAGE), LAMPS(RAFTS)
tgttoggle: shared, PRI_LEFF3, page(MACHINE3_PAGE), LAMPS(GOLDRUSH)

##########################################################################
# Timers
##########################################################################
[timers]
multimill:
wpool:
lramp:
lrampdown:
lloop:
rloop:
skill:
disdrop loop:
combos:
rloop combo:

##########################################################################
# The default high scores.  Use GC to indicate the grand champion.
# The parameters are the initials followed by the score value.  Periods
# may optionally be used to group digits, but they are not necessary.
# Commas _cannot_ be used for this purpose since they separate parameters.
##########################################################################
[highscores]

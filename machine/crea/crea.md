#--------------------------------------------------------------------------
# Machine description for MovieTime
# (C) Copyright 2021 Aeneas Verhe
#
# See tools/genmachine for more information about the format of this file.
#--------------------------------------------------------------------------
# This file describes many characteristics of a pinball machine,
# mostly physical stuff, although some rules can be coded here also.

##########################################################################
# General section (before a [section] header is given.
# Miscellaneous parameters are specified here.
##########################################################################
Title: movietime
include platform/wpc/wpc-fliptronic.md

Pinmame-Zip: cftbl_l4.zip
Pinmame-ROM: creat_l4.rom
#Lamp-Matrix-Width:
#Lamp-Matrix-Height:


##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################

define MACHINE_MOVIE
define MACHINE_NUMBER 588
define MACHINE_BALL_SAVE_TIME 1
#define MACHINE_CUSTOM_AMODE

define FREE_ONLY

define DEVELOPMENT_MENU

##########################################################################
# Lamp Description
# The key is given in column/row format.  The first parameter must be
# the lamp name.  Optionally you can specify a color, and x() and y()
# for the location on the playfield.  Only a subset of lamp colors are
# recognized; see tools/genmachine for details.  Lamp location is
# given in terms of the Lamp-Matrix-Width and Lamp-Matrix-Height.
##########################################################################
[lamps]
11: paidp, yellow
12: paida, yellow
13: paidi, yellow
14: paidd, yellow
15: 
16: 
17: 
18: admitone
21: kissk
22: kissi
23: kisss1
24: kisss2
25: tenmil
26: twentymil
27: thirtymil
28: specialsa
31: startmegamenu
32: playgroundaward
33: litebigmillions
34: slide
35: rightsearch
36: rightvideo
37: rightstartmovie
38: megamenu
41: lips
42: leftsearch
43: leftvideo
44: leftstartmovie
45: comboaward
46: parkingok
47: moveyourcar
48: extraball
51: SnackBar
52: CenterSearch
53: Cola
54: Hotdog
55: SuperJackpot
56: Jackpot
57: Rescue
58: RestartMultiball
61: FreePass, shoot-again, ball-save
62: BuildCombo
63: UnlimitedMillions
64: CreatureFeature
65: ExtraBallCountdown
66: BigMillions
67: MovieMadness
68: CountToFeature
71: C
72: R
73: E
74: A
75: T
76: U
77: R2
78: E2
81: filmf
82: filmi
83: filml
84: filmm
85: startcombo
86: popcorn
87: icecream
88: start, start


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
11: right flipper, button, intest, c_decl(sw_right_button), noscore
12: left flipper, button, intest, c_decl(sw_left_button), noscore
13: start button, yellow, start-button, cabinet, intest
14: plumb bob tilt, c_decl(sw_tilt), cabinet, tilt, ingame, novalid
15: top left, ingame
16: left subway, ingame
17: center subway, ingame
18: center shot, ingame
21: slam tilt, slam-tilt, ingame, cabinet, novalid, noscore
22: coin door closed, noscore, novalid
25: paidp, ingame
26: paida, ingame
27: paidi, ingame
28: paidd, ingame
33: centerjet, ingame
34: slide popper, ingame, opto, edge
35: rightrampenter, ingame
36: leftrampenter, ingame
37: bowl popper, ingame, opto, edge, noscore
38: rampupdown, ingame, noscore
41: cola, ingame, standup
42: hotdog, ingame, standup
43: popcorn, ingame, standup
44: icecream, ingame, standup
45: leftjet, ingame
46: rightjet, ingame
47: left slingshot, ingame
48: right slingshot, ingame
51: left outlane, ingame
52: left inlane, ingame
53: right inlane, ingame
54: right outLane, ingame
55: outhole, outhole, service, novalid, intest, noscore
56: Trough 1, noscore, novalid
57: Trough 2, noscore, novalid
58: Trough 3, noscore, novalid
61: rightrampexit, ingame
62: leftrampexit, ingame
63: centerlaneexit, ingame
64: upperramp, ingame
65: bowl, ingame
66: ball shooter, edge, shooter, novalid, noscore, debounce(TIME_200MS)



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
H1: slide popper, duty(SOL_DUTY_75), time(TIME_100MS)
H2: left subway enter, flash
H3: bowl popper, duty(SOL_DUTY_75), time(TIME_100MS)
H4: Ball Release, ballserve, duty(SOL_DUTY_25), time(TIME_133MS)
H5: left sling, duty(SOL_DUTY_100), time(TIME_33MS)
H6: right sling, duty(SOL_DUTY_100), time(TIME_33MS)
H7: knocker, knocker, duty(SOL_DUTY_75), time(TIME_50MS), nosearch
H8: bottom right fl, flash


#L = low power J127
#### these are all 50v power
L1: back fl, flash
L2: bowl fl, flash
L3: creature fl, flash
L4: outhole, duty(SOL_DUTY_50), time(TIME_133MS)
L5: left jet, duty(SOL_DUTY_75), time(TIME_50MS)
L6: right jet, duty(SOL_DUTY_75), time(TIME_50MS)
L7: center jet, duty(SOL_DUTY_75), time(TIME_50MS)
L8: right popper fl, flash


# G = J126 on Power Driver Board
G1: kiss car fl, flash
G2: right ramp fl, flash
G3: left lamp fl, flash
G4: seq gi 1, nosearch
G5: holo push, motor, nosearch
G6: snackbar fl, flash
G7: updown ramp up, duty(SOL_DUTY_50), time(TIME_66MS)
G8: seq gi 2, nosearch


# A = J122 pins 1-2-3-4
#### these are all 20v power
A1: start movie fl, flash
A2: updown ramp down, duty(SOL_DUTY_50), time(TIME_66MS)
A3: holo motor, motor, nosearch
A4: holo lamp, nosearch

# F = J902 on Fliptronic II
#### these are all 50v power
F1: L.R. Flip Power
F2: L.R. Flip Hold
F3: L.L. Flip Power
F4: L.L. Flip Hold




[templates]
outhole: driver(outhole), sol=SOL_OUTHOLE, swno=SW_OUTHOLE, swevent=sw_outhole
left sling: driver(sling), sw=SW_LEFT_SLINGSHOT, sol=SOL_LEFT_SLING
right sling: driver(sling), sw=SW_RIGHT_SLINGSHOT, sol=SOL_RIGHT_SLING
left jet: driver(jet), sw=SW_LEFTJET, sol=SOL_LEFT_JET
right jet: driver(jet), sw=SW_RIGHTJET, sol=SOL_RIGHT_JET
lower jet: driver(jet), sw=SW_CENTERJET, sol=SOL_CENTER_JET
updown ramp up: driver(duty), sol=SOL_UPDOWN_RAMP_UP, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60
updown ramp down: driver(duty), sol=SOL_UPDOWN_RAMP_DOWN, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60




##########################################################################
# General Illumination
##########################################################################
[gi]
0: seq gi 1
1: pf middle
2: pf upper
3: seq gi 2
4: pf lower


##########################################################################
# Tests
# These are additional test items that should appear in the TESTS menu.
##########################################################################
#Templates that use include test must still be listed here otherwise it won't be listed in the test menu
[tests]


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
Trough: Ball Release, trough, init_max_count(3), Trough 3, Trough 2, Trough 1
Slide Popper: slide popper, slide popper
Bowl Popper: bowl popper, bowl popper



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
#Add Coin: SND_COIN
Tilt Warning: SPCH_FM_HEY
Tilt: SPCH_FM_THATDOESIT

##########################################################################
# Music calls for well-known events
##########################################################################
[system_music]
Start Ball: MUS_DEFAULT_AT_PLUNGER
Ball In Play: MUS_MAIN
End Game: MUS_MAIN4


##########################################################################
# A list of all scores needed by the game rules.
#
#
##########################################################################
[scores]
10:
100:
500:
1K:
10K:
20K:
25K:
50K:
100K:
250K:
1M:
5M:
10M:
15M:
20M:
25M:
30M:
35M:
40M:
45M:
50M:
60M:


##########################################################################
# Bit flags.
##########################################################################
[flags]
Multiball Lit:
Multiball ball locked:
Multiball Running:
Admit One:
MMenu Lit:
xball lit:

video1lit:
video2lit:

cola:
hotdog:
popcorn:
icecream:



##########################################################################
# Global flags.
##########################################################################
[globalflags]
ball on pf:
skillshot lit:
tempfl:
video1:
video2:



##########################################################################
# Display effects
##########################################################################
[deffs]
#
#text page GAME_OBJS
####################



#
#MACHINE_PAGE page GAME_PAGED_OBJS page(MACHINE_PAGE),
##################################
MB2 Start: page(MACHINE_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED
MB3 Start: page(MACHINE_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED
Lock2 lit: page(MACHINE_PAGE), runner, PRI_GAME_MODE7, D_QUEUED+D_TIMEOUT
MB Running: page(MACHINE_PAGE), runner, PRI_GAME_MODE7, D_QUEUED+D_TIMEOUT
MB Lit: page(MACHINE_PAGE), runner, PRI_GAME_MODE7, D_QUEUED+D_TIMEOUT

Bowl letter: page(MACHINE_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED

Award Kiss: page(MACHINE_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED

Paid Made: page(MACHINE_PAGE), PRI_GAME_QUICK7, D_PAUSE+D_QUEUED
Paid Letter: page(MACHINE_PAGE), PRI_GAME_QUICK8, D_QUEUED+D_TIMEOUT


#
#MACHINE2_PAGE page GAME2_OBJS page(MACHINE2_PAGE),
##############################



#
#MACHINE3_PAGE page GAME3_OBJS page(MACHINE3_PAGE)
##############################
Skill Made: page(MACHINE3_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED
DCombo Coll: page(MACHINE3_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED
DCombo Init: page(MACHINE3_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED

MMenu Running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE7, D_QUEUED+D_TIMEOUT

BigMil Running: page(MACHINE3_PAGE), runner, PRI_GAME_MODE7, D_QUEUED+D_TIMEOUT
BigMil Jackpot: page(MACHINE3_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED




#MACHINE4_PAGE page GAME4_OBJS page(MACHINE4_PAGE)
##############################


#MACHINE5_PAGE page GAME5_OBJS page(MACHINE5_PAGE)
##############################
xball: page(MACHINE5_PAGE), PRI_GAME_QUICK8, D_PAUSE+D_QUEUED




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
Playfield: PF:all
Paid: paidp..paidd
Kiss: kissk..kisss2
CreatureBB: C..E2
Film: filmf..filmm



##########################################################################
# Lamp effects
##########################################################################
[leffs]


##########################################################################
# Timers
##########################################################################
[timers]


##########################################################################
# The default high scores.  Use GC to indicate the grand champion.
# The parameters are the initials followed by the score value.  Periods
# may optionally be used to group digits, but they are not necessary.
# Commas _cannot_ be used for this purpose since they separate parameters.
##########################################################################
[highscores]
GC: AE, 500000000
1: KAT, 400000000
2: MYA, 350000000
3: ELS, 300000000
4: BAS, 250000000


#--------------------------------------------------------------------------
# Machine description for DrWho
# (C) Copyright 2023 Aeneas Verhe
#
# See tools/genmachine for more information about the format of this file.
#--------------------------------------------------------------------------
# This file describes many characteristics of a pinball machine,
# mostly physical stuff, although some rules can be coded here also.

##########################################################################
# General section (before a [section] header is given.
# Miscellaneous parameters are specified here.
##########################################################################
Title: drwho
include platform/wpc/wpc-fliptronic.md

Pinmame-Zip: dw_l2.zip
Pinmame-ROM: drwho_l2.rom
#Lamp-Matrix-Width:
#Lamp-Matrix-Height:


##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################

define MACHINE_DRWHO
define MACHINE_NUMBER 506
define MACHINE_HAS_UPPER_LEFT_FLIPPER
define MACHINE_BALL_SAVE_TIME 3
#define MACHINE_CUSTOM_AMODE

define FREE_ONLY

#define DEVELOPMENT_MENU

##########################################################################
# Lamp Description
# The key is given in column/row format.  The first parameter must be
# the lamp name.  Optionally you can specify a color, and x() and y()
# for the location on the playfield.  Only a subset of lamp colors are
# recognized; see tools/genmachine for details.  Lamp location is
# given in terms of the Lamp-Matrix-Width and Lamp-Matrix-Height.
##########################################################################
[lamps]
11: escape e1, orange
12: escape s, orange
13: escape c, orange
14: escape a, orange
15: escape p, orange
16: escape e2, orange
17: left outlane, red
18: left inlane, red
21: right inlane, red
22: right outlane, red
23: doctor 7, yellow
24: escape special, white
25: escape 3m, white
26: escape 2m, white
27: escape 1k, white
28: escape 5k, white
31: grid top 1, red
32: grid top 2, red
33: grid top 3, red
34: grid top 4, red
35: grid top 5, red
36: doctor 2, yellow
37: hangon score
38: videomode
41: grid center 1, red
42: grid center 2, red
43: grid center 3, red
44: grid center 4, red
45: grid center 5, red
46: transmat, white
47: tardis, blue
48: doctor 1, yellow
51: grid bottom 1, red
52: grid bottom 2, red
53: grid bottom 3, red
54: grid bottom 4, red
55: grid bottom 5, red
56: mpf left lock, white
57: mpf right lock, white
58: mpf light lock, white
61: repair r1, orange
62: repair e, orange
63: repair p, orange
64: repair a, orange
65: repair i, orange
66: repair r2, orange
67: doctor 5, yellow
68: shoot again, shoot-again, red, ball-save
71: doctor 4, yellow
72: doctor 6, yellow
73: 15x, white
74: 2x, white
75: 25x, white
76: 3x, white
77: 65x, white
78: 4x, white
81: who w, white
82: doctor 3, yellow
83: who 1m
84: who 2m
85: who lite eb
86: adv bonus
87: ball launch, launch, cabinet, yellow
88: start button, start, cabinet, yellow

#collect eb, extra-ball, orange


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
15: left slingshot, ingame, c_decl(sw_sling)
16: right slingshot, ingame, c_decl(sw_sling)
17: ball shooter, edge, shooter, novalid, noscore, debounce(TIME_200MS)
18: exit jets, ingame
21: slam tilt, slam-tilt, ingame, cabinet, novalid, noscore
22: coin door closed, noscore, novalid
25: Trough 1, noscore, novalid
26: Trough 2, noscore, novalid
27: Trough 3, noscore, novalid
28: outhole, outhole, service, novalid, intest, noscore
31: tardis popper, opto, ingame
32: mpf home, opto, noscore, novalid
33: enter top ramp, opto
34: launch button, launch-button, cabinet, novalid
35: top ramp made, ingame
36: enter bottom ramp, ingame
37: score bottom ramp, ingame
38: mpf dalek center, ingame
41: escape e1, ingame, standup
42: escape s, ingame, standup
43: escape c, ingame, standup
44: escape a, ingame, standup
45: escape p, ingame, standup
46: escape e2, ingame, standup
47: hangon score, ingame
48: select dr, ingame
51: repair r1, ingame, standup
52: repair e, ingame, standup
53: repair p, ingame, standup
54: repair a, ingame, standup
55: repair i, ingame, standup
56: repair r2, ingame, standup
57: trap down, noscore, novalid
58: transmat award, ingame, standup
61: left jet, ingame, c_decl(sw_jet)
62: right jet, ingame, c_decl(sw_jet)
63: bottom jet, ingame, c_decl(sw_jet)
64: left outlane, ingame
65: left inlane, ingame
66: right inlane, ingame
67: right outlane, ingame
68: mpf dalek left, ingame
71: grid 5, opto, ingame
72: grid 4, opto, ingame
73: grid 3, opto, ingame
74: grid 2, opto, ingame
75: grid 1, opto, ingame
76: mpf left lock, opto, ingame
77: mpf right lock, opto, ingame
78: mpf light lock, ingame, standup
82: pf glass, novalid, noscore
88: mpf dalek right, ingame





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
H1: trapdoor div, duty(SOL_DUTY_50), time(TIME_133MS)
H2: autofire, launch, nosearch
H3: tardis popper, duty(SOL_DUTY_100), time(TIME_133MS)
H4: mpf left lock, duty(SOL_DUTY_75), time(TIME_100MS)
H5: mpf right lock, duty(SOL_DUTY_75), time(TIME_100MS)
H6: second chance fl, flash
H7: knocker, knocker, duty(SOL_DUTY_75), time(TIME_50MS), nosearch
H8: dr3 fl, flash


#L = low power J127
#### these are all 50v power
L1: left slingshot, duty(SOL_DUTY_100), time(TIME_33MS)
L2: right slingshot, duty(SOL_DUTY_100), time(TIME_33MS)
L3: left jet, duty(SOL_DUTY_75), time(TIME_50MS)
L4: right jet, duty(SOL_DUTY_75), time(TIME_50MS)
L5: bottom jet, duty(SOL_DUTY_75), time(TIME_50MS)
L6: bb dalek fl, flash
L7: outhole, duty(SOL_DUTY_50), time(TIME_133MS)
L8: Ball Release, ballserve, duty(SOL_DUTY_25), time(TIME_133MS)


# G = J126 on Power Driver Board
G1: mpf dr fl, flash
G2: grid left fl, flash
G3: grid right fl, flash
G4: jets dr5 fl, flash
G5: repair dr4 fl, flash
G6: whoh dr2 fl, flash
G7: whoo dr6 fl, flash
G8: escape dr1 fl, flash


# A = J122 pins 1-2-3-4
#### these are all 20v power
A3: mpf drive, motor, nosearch
A4: mpf enable, motor, nosearch

# F = J902 on Fliptronic II
#### these are all 50v power
F1: L.R. Flip Power
F2: L.R. Flip Hold
F3: L.L. Flip Power
F4: L.L. Flip Hold


[templates]
outhole: driver(outhole), sol=SOL_OUTHOLE, swno=SW_OUTHOLE, swevent=sw_outhole
left sling: driver(sling), sw=SW_LEFT_SLINGSHOT, sol=SOL_LEFT_SLINGSHOT
right sling: driver(sling), sw=SW_RIGHT_SLINGSHOT, sol=SOL_RIGHT_SLINGSHOT
left jet: driver(jet), sw=SW_LEFT_JET, sol=SOL_LEFT_JET
right jet: driver(jet), sw=SW_RIGHT_JET, sol=SOL_RIGHT_JET
bottom jet: driver(jet), sw=SW_BOTTOM_JET, sol=SOL_BOTTOM_JET
trapdoor: driver(duty2), sol=SOL_TRAPDOOR_DIV, timeout=TIME_3S, ontime=TIME_33MS, duty_mask=DUTY_MASK_50
#mpf: driver(bivar3), dir_sol=SOL_MPF_DRIVE, enable_sol=SOL_MPF_ENABLE, back_sw=SW_BFHEAD_BACK, front_sw=SW_BFHEAD_FRONT, includetest(yes)



##########################################################################
# General Illumination
##########################################################################
[gi]
0: BB top
1: BB bottom
2: PF A
3: PF B
4: PF C

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
Lock left: mpf left lock, mpf left lock
Lock right: mpf right lock, mpf right lock
tardis: tardis popper, tardis popper




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
#
# 10 sling.c
##########################################################################
[scores]
10:
250K:
500K:
1M:
2M:
3M:
10M:


##########################################################################
# Bit flags.
##########################################################################
[flags]




##########################################################################
# Global flags.
##########################################################################
[globalflags]



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


#
#MACHINE2_PAGE page GAME2_OBJS page(MACHINE2_PAGE),
##############################


#
#MACHINE3_PAGE page GAME3_OBJS page(MACHINE3_PAGE)
##############################





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

escape: escape e1..escape e2
repair: repair r1..repair r2



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


#--------------------------------------------------------------------------
# Machine description for Creature
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
Title: creature
include platform/wpc/wpc-fliptronic.md

Pinmame-Zip: cftbl_l4.zip
Pinmame-ROM: creat_l4.rom
#Lamp-Matrix-Width:
#Lamp-Matrix-Height:


##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################

define MACHINE_CREA
define MACHINE_NUMBER 588
#define MACHINE_BALL_SAVE_TIME 1
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
11: paidp, yellow
12: paida, yellow
13: paidi, yellow
14: paidd, yellow
15: 
16: 
17: 
18: admitone, shoot-again, ball-save
21: kkiss
22: ikiss
23: s1kiss
24: s2kiss
25: tenmillion
26: twentymillion
27: thirtymillion
28: specialsa
31: startmegamenu
32: playgroundaward
33: litebigmillions
34: slide
35: rightsearch
36: rightvideo
37: rightstartmoviea
38: megamenu
41: lips
42: leftsearch
43: leftvideo
44: leftstartmoviea
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
61: FreePass
62: BuildCombo
63: UnlimitedMillions
64: CreatureFeature
65: ExtraBallCountdown
66: BigMillions
67: MovieMadness
68: SnackAttack
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

13: start button, yellow, start-button, cabinet, intest
14: plumb bob tilt, c_decl(sw_tilt), cabinet, tilt, ingame, novalid
15: topleftrollover, ingame
16: left subway, ingame
17: center subway, ingame
18: center shot, ingame
21: slam tilt, slam-tilt, ingame, cabinet, novalid, noscore
22: coin door closed, noscore, novalid
25: paidp
26: paida
27: paidi
28: paidid
33: centerjet
34: rightpopper
35: rightrampenter
36: leftrampenter
37: lowerrightpopper
38: rampupdown
41: cola
42: hotdog
43: popcorn
44: icecream
45: leftjet
46: rightjet
47: leftslingshot
48: rightslingshot
51: leftoutlanes
52: leftinlane
53: rightinlane
54: rightoutLane
55: outhole, outhole, service, novalid, intest, noscore
56: Trough 1, noscore, novalid
57: Trough 2, noscore, novalid
58: Trough 3, noscore, novalid
61: rightrampexit
62: leftrampexit
63: centerlaneexit
64: upperramp
65: bowl
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
H1: top right popper, duty(SOL_DUTY_75), time(TIME_100MS)
H2: left subway enter, flash
H3: lower right popper, duty(SOL_DUTY_75), time(TIME_100MS)
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
G1: bottom left fl, flash
G2: right ramp fl, flash
G3: left lamp fl, flash
G4: seq gi 1, flash
G5: holo push, flash
G6: center hole fl, flash
G7: updown ramp, duty(SOL_DUTY_50), time(TIME_66MS)
G8: seq gi 2, flash


# A = J122 pins 1-2-3-4
#### these are all 20v power
A1: start movie fl, flash
A2: updown ramp fl, flash
A3: creature motor, motor
A4: creature lamp, motor

# F = J902 on Fliptronic II
#### these are all 50v power
F1: L.R. Flip Power
F2: L.R. Flip Hold
F3: L.L. Flip Power
F4: L.L. Flip Hold




[templates]
outhole: driver(outhole), sol=SOL_OUTHOLE, swno=SW_OUTHOLE, swevent=sw_outhole
left sling: driver(sling), sw=SW_LEFTSLINGSHOT, sol=SOL_LEFT_SLING
right sling: driver(sling), sw=SW_RIGHTSLINGSHOT, sol=SOL_RIGHT_SLING
left jet: driver(jet), sw=SW_LEFTJET, sol=SOL_LEFT_JET
right jet: driver(jet), sw=SW_RIGHTJET, sol=SOL_RIGHT_JET
lower jet: driver(jet), sw=SW_CENTERJET, sol=SOL_CENTER_JET
updown ramp: driver(duty), sol=SOL_UPDOWN_RAMP, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60




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
#
##########################################################################
[scores]
10:
500:
10K:
20K:
25K:
50K:
100K:
175K:
195110:
250K:
1M:
10M:
20M:


##########################################################################
# Bit flags.
##########################################################################
[flags]




##########################################################################
# Global flags.
##########################################################################
[globalflags]

#plunger ball:
#fall running:


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


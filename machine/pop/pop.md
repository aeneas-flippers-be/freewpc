#--------------------------------------------------------------------------
# Machine description for Popeye
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
Title: sailor
include platform/wpc/wpc-dcs.md

Pinmame-Zip: popeye_l5.zip
Pinmame-ROM: peye_lx5.rom
#Lamp-Matrix-Width:
#Lamp-Matrix-Height:


##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################

define MACHINE_POP
define MACHINE_NUMBER 522
define MACHINE_HAS_UPPER_LEFT_FLIPPER
define MACHINE_HAS_UPPER_RIGHT_FLIPPER
#define MACHINE_BALL_SAVE_TIME 1
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
11: oyl o, yellow
12: oyl y, yellow
13: oyl l, yellow
14: fight bluto
15: right popper spcan, green
16: right loop arrow
17: right loop spcan, green
18: hag standup
21: island rhino
22: island leopard
23: island eagle
24: island dolphin
25: item can opener
26: item bottle
27: item ketchup
28: island panda
31: lockjaw
32: never green
33: earth paving
34: escalator
35: pop e1, orange
36: pop y, orange
37: pop e2, orange
38: item flower
41: spillco oil
42: blutonium waste
43: left outlane, extra-ball, orange
44: left inlane, white
45: right inlane, white
46: special
47: shoot again, shoot-again, orange, ball-save
48: rescue olive
51: left loop arrow
52: left loop spcan, green
53: pop p1, orange
54: pop o, orange
55: pop p2, orange
56: left ramp arrow
57: collect item
58: left ramp spcan, green
61: sea standup
62: animal dolphin
63: left popper arrow
64: left popper spcan, green
65: left cheek, red
66: right cheek, red
67: animal panda
68: animal leopard
71: backbox tail
72: backbox star
73: animal rhino
74: backbox light
75: animal eagle
76: upper ramp left
77: upper ramp center
78: upper ramp right
81: upper extra ball, extra-ball, orange
82: wimpy 2x wheel
83: two bank upper
84: two bank lower
85: animal jackpot
86: buyin
87: ball launch, launch, cabinet, yellow
88: start button, start, cabinet, yellow


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
11: oyl o, ingame
12: buyin, cabinet, intest
13: start button, yellow, start-button, cabinet, intest
14: tilt, ingame, novalid
15: oyl l, ingame
16: left jet, ingame
17: right jet, ingame
18: center jet, ingame
21: slam tilt, slam-tilt, ingame, cabinet, novalid, noscore
22: coin door closed, noscore, novalid
23: launch button, launch-button, cabinet, novalid
25: left loop, ingame
26: pop e1, standup, ingame
27: pop y, standup, ingame
28: pop e2, standup, ingame
31: left popper sw, ingame, opto
32: right popper sw, ingame, opto
33: right loop opto, opto, ingame
34: ramp entrance, opto, ingame
36: escalator popper sw, opto, ingame
35: ramp made, opto, ingame
37: wheel exit, opto
38: hag standup, standup, ingame
41: two bank upf, ingame
42: oyl y, ingame
43: lockup upper
44: lockup center
45: lockup lower
46: wheel opto 1, opto
47: wheel opto 2, opto
48: wheel opto 3, opto
51: Trough 1, trough, opto, noscore, novalid
52: Trough 2, trough, opto, noscore, novalid
53: Trough 3, trough, opto, noscore, novalid
54: Trough 4, trough, opto, noscore, novalid
55: Trough 5, trough, opto, noscore, novalid
56: Trough 6, trough, opto, noscore, novalid
57: trough jam, opto, noscore, novalid
58: sea standup, standup, ingame
61: left cheek, standup, ingame
62: right cheek, standup, ingame
63: escalator exit, ingame
64: animal dolphin, ingame
65: animal eagle, ingame
66: animal tiger, ingame
67: animal panda, ingame
68: animal rhino, ingame
71: pop p1, standup, ingame
72: pop o, standup, ingame
73: pop p2, standup, ingame
74: left outlane, ingame
75: left inlane, ingame
76: left slingshot, ingame, c_decl(sw_sling)
77: right slingshot, ingame, c_decl(sw_sling)
78: right inlane, ingame
81: upper exit to wheel, opto, ingame
82: upper ramp left, opto, ingame
83: upper ramp right, opto, ingame
84: animal jackpot, ingame
85: right outlane, novalid, ingame
86: ball shooter, edge, shooter, novalid, noscore, debounce(TIME_200MS)
87: lockup kicker sw, ingame
88: upper shot exit, ingame



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
H1: right popper, duty(SOL_DUTY_100), time(TIME_133MS)
H2: left popper, duty(SOL_DUTY_100), time(TIME_133MS)
H3: autofire, launch, nosearch
H4: animal div, duty(SOL_DUTY_75), time(TIME_66MS)
H5: trough coil, ballserve
H6: lockup kicker, duty(SOL_DUTY_100), time(TIME_100MS)
H7: knocker, knocker, duty(SOL_DUTY_75), time(TIME_66MS), nosearch
H8: escalator popper, duty(SOL_DUTY_100), time(TIME_133MS)


#L = low power J127
#### these are all 50v power
L1: left jet, duty(SOL_DUTY_75), time(TIME_66MS)
L2: right jet, duty(SOL_DUTY_75), time(TIME_66MS)
L3: center jet, duty(SOL_DUTY_75), time(TIME_66MS)
L4: left slingshot, duty(SOL_DUTY_100), time(TIME_33MS)
L5: right slingshot, duty(SOL_DUTY_100), time(TIME_33MS)
L6: left gate, duty(SOL_DUTY_50), time(TIME_66MS)
L7: right gate, duty(SOL_DUTY_50), time(TIME_66MS)
L8: lockup release, duty(SOL_DUTY_75), time(TIME_500MS)

# G = J126 on Power Driver Board
G1: wheel motor, motor
G2: upper pl left fl, flash
G3: right loop bb fl, flash
G4: fight bluto fl, flash
G5: left loop bb fl, flash
G6: animal ramp fl, flash
G7: skill wheel fl, flash
G8: r popper bb fl, flash

# A = J122 pins 1-2-3-4
#### these are all 20v power
A2: ramp jackpot fl, flash
A3: lockjaw arrow fl, flash
A4: esc bb tutrtle fl, flash

# F = J902 on Fliptronic II
#### these are all 50v power
F1: L.R. Flip Power
F2: L.R. Flip Hold
F3: L.L. Flip Power
F4: L.L. Flip Hold
F5: U.R. Flip Power
F6: U.R. Flip Hold
F7: U.L. Flip Power
F8: U.L. Flip Hold



[templates]
left sling: driver(sling), sw=SW_LEFT_SLINGSHOT, sol=SOL_LEFT_SLINGSHOT
right sling: driver(sling), sw=SW_RIGHT_SLINGSHOT, sol=SOL_RIGHT_SLINGSHOT
left jet: driver(jet), sw=SW_LEFT_JET, sol=SOL_LEFT_JET
right jet: driver(jet), sw=SW_RIGHT_JET, sol=SOL_RIGHT_JET
lower jet: driver(jet), sw=SW_CENTER_JET, sol=SOL_CENTER_JET
left gate: driver(duty), sol=SOL_LEFT_GATE, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60
right gate: driver(duty), sol=SOL_RIGHT_GATE, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60
wheel: driver(duty2), sol=SOL_WHEEL_MOTOR, timeout=TIME_4S, ontime=TIME_500MS, duty_mask=DUTY_MASK_50


#lockup release: driver(duty2), sol=SOL_LOCKUP_RELEASE, timeout=TIME_2S, ontime=TIME_500MS, duty_mask=DUTY_MASK_50



##########################################################################
# General Illumination
##########################################################################
[gi]
0: pf left
1: pf right
2: bb general
3: bb title
4: pf upper

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
Trough: trough coil, trough, init_max_count(6), Trough 6, Trough 5, Trough 4, Trough 3, Trough 2, Trough 1
Lock: lockup release, lockup upper, lockup center, lockup lower
Left Hole: left popper, left popper sw
Right Hole: right popper, right popper sw
BlutoKick: lockup kicker, lockup kicker sw
Escalator: escalator popper, escalator popper sw


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
1K:
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
oyl:oyl o, oyl y, oyl l
inlanes: left inlane, right inlane
poptgts: pop p1, pop o, pop p2, pop e1, pop y, pop e2


##########################################################################
# Lamp effects
##########################################################################
[leffs]


##########################################################################
# Timers
##########################################################################
[timers]
lloop:
rloop:
animal:


##########################################################################
# The default high scores.  Use GC to indicate the grand champion.
# The parameters are the initials followed by the score value.  Periods
# may optionally be used to group digits, but they are not necessary.
# Commas _cannot_ be used for this purpose since they separate parameters.
##########################################################################
[highscores]


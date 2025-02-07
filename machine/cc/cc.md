#--------------------------------------------------------------------------
# Cactus Canyon machine description for FreeWPC 
# (C) Copyright 2012 by Aeneas Verhe
#
# See tools/genmachine for more information about the format of this file.
#--------------------------------------------------------------------------

Title: Cactus Canyon
include platform/wpc/wpc95.md

Pinmame-Zip: cc_13.zip
Pinmame-ROM: cc_g11.1_3

Lamp-Matrix-Width: 18
Lamp-Matrix-Height: 20

##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################
define MACHINE_NUMBER 566
define MACHINE_MAX_BALLS 4
define MACHINE_BALL_SAVE_TIME 2



##########################################################################
# Lamp Description
##########################################################################
[lamps]
11: Rank Stranger, yellow, x(13), y(4)
12: Rank Partner, yellow, x(13), y(5)
13: Rank Deputy, yellow, x(13), y(8)
14: Rank Sheriff, yellow, x(13), y(12)
15: Rank Marshall, yellow, x(13), y(15)
16: Star Motherlode, yellow, x(14), y(8)
17: Left BonusX, white, x(1), y(6)
18: Right BonusX, white, x(1), y(7)
21: Beacon Bounty, white, x(12), y(13)
22: Beacon Jackpot , white, x(12), y(12)
23: Beacon ShootCollect, white, x(11), y(12)
24: Beacon ExtraBallLit, white, x(12), y(10)
25: Saloon Bounty, white, x(2), y(9)
26: Saloon Jackpot, yellow, x(3), y(9)
27: Mine Extra Ball, red, x(5), y(7)
28: Mine Lock, green, x(6), y(7)
31: Badguy3, yellow, x(6), y(10)
32: Badguy1, yellow, x(7), y(5)
33: Left QuickDraw, yellow, x(11), y(3)
34: Right Ramp SoundAlarm, purple, x(10), y(13)
35: Right Ramp ShootOut, purple, x(9), y(13)
36: Right Ramp SavePolly, purple, x(8), y(13)
37: Right Ramp Jackpot, red, x(7), y(13)
38: Right Ramp Combo, white, x(6), y(13)
41: Right Loop Combo, white, x(2), y(11)
42: Right Loop Jackpot, red, x(3), y(11)
43: Right Loop Marksman, blue, x(4), y(11)
44: Right Loop Gunslinger, blue, x(5), y(11)
45: Right Loop Goodshot, blue, x(6), y(11)
46: LRet QuickDraw, yellow, x(14), y(2)
47: Left Gunfight, white, x(17), y(2)
48: Left Outlane Gunfight, red, x(16), y(1)
51: Badguy4, yellow, x(7), y(12)
52: BottomR QuickDraw, yellow, x(11), y(15)
53: TopR QuickDraw, yellow, x(10), y(15)
54: Center Ramp CatchTrain, green, x(7), y(8)
55: Center Ramp StopTrain, green, x(6), y(8)
56: Center Ramp SavePolly, green, x(5), y(8)
57: Center Ramp Jackpot, red, x(4), y(8)
58: Center Ramp Combo, white, x(3), y(8)
61: Left Ramp Whitewater, blue, x(11), y(6)
62: Left Ramp Waterfall, blue, x(10), y(6)
63: Left Ramp SavePolly, blue, x(8), y(6)
64: Left Ramp Jackpot, red, x(7), y(6)
65: Left Ramp Combo, white, x(6), y(6)
66: RRet QuickDraw, yellow, x(14), y(16)
67: ROut Special, red, x(16), y(17)
68: Right Gunfight, white, x(17), y(16)
71: Star Stampede, yellow, x(15), y(4)
72: Star Combo, yellow, x(), y(15)
73: Star HighNoon, yellow, x(17), y(15)
74: Left Loop Combo, white, x(6), y(4)
75: Left Loop Jackpot, red, x(7), y(4)
76: Left Loop Ridem, purple, x(8), y(4)
77: Left Loop Wildride, purple, x(9), y(4)
78: Left Loop BucknBronco, purple, x(10), y(4)
81: Star BartBros, yellow, x(16), y(8)
82: Shoot Again, purple, shoot-again, x(18), y(8)
83: Star Showdown, yellow, x(17), y(4)
84: Badguy2, yellow, x(8), y(7)
88: Start Button, yellow, start, cabinet, x(19), y(1)

##########################################################################
# Switch Description
# The key is in column/row format.  The first parameter must be the switch
# name.  Options can be given in any order:
#    ingame - only service the switch during a game
#    intest - also service the switch in test mode
#    noplay - tripping this switch does NOT mark ball in play
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
11: Right Flipper, button, intest, c_decl(sw_right_button)
12: Left Flipper, button, intest, c_decl(sw_left_button)
13: Start Button, start-button, intest
14: Plumb bob tilt, c_decl(sw_tilt), cabinet, tilt, ingame, noplay
15: Mine Entrance, ingame
16: Left Outlane, ingame
17: Right Inlane, ingame
18: Shooter, shooter, edge, noplay, debounce(TIME_200MS)
21: Slam Tilt, slam-tilt, ingame, cabinet
26: Left Inlane, ingame
27: Right Outlane, ingame
28: QD Right Bottom, standup, ingame
31: Trough Eject, opto, noscore, noplay
32: Trough 1, trough, opto, noscore, noplay
33: Trough 2, trough, opto, noscore, noplay
34: Trough 3, trough, opto, noscore, noplay
35: Trough 4, trough, opto, noscore, noplay
36: Left Loop Bottom, opto, ingame
37: Right Loop Bottom, opto, ingame
41: Mine Popper, opto, edge, ingame
42: Saloon Popper, opto, edge, ingame
44: QD Right Top, standup, ingame
46: Beermug, standup, ingame
47: Left BonusX, ingame
48: Bumpers Exit, ingame
51: Left Sling, ingame, c_decl(sw_sling)
52: Right Sling, ingame, c_decl(sw_sling)
53: Left Jet, ingame, c_decl(sw_jet)
54: Right Jet, ingame, c_decl(sw_jet)
55: Bottom Jet, ingame, c_decl(sw_jet)
56: Right Loop Top, ingame
57: Right BonusX, ingame
58: Left Loop Top, ingame
61: Badguy1, ingame
62: Badguy2, ingame
63: Badguy3, ingame
64: Badguy4, ingame
65: Right Ramp Make, ingame
66: Right Ramp Enter, ingame
67: Skillbowl, ingame
68: Right Ramp Bottom, ingame
71: Train Encoder, noplay, intest, service
72: Train Home, noplay, intest, service
73: Saloon Gate, ingame
75: Bart Face, ingame
77: Mine Home, noplay, intest, service, edge
78: Mine Encoder, noplay, intest, service
82: Center Ramp Enter, ingame
83: Left Ramp Make, ingame
84: Center Ramp Make, ingame
85: Left Ramp Enter, ingame
86: QD Left Top, standup, ingame
87: QD Left Bottom, standup, ingame

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
H1: Autoplunger, nosearch, launch, duty(SOL_DUTY_100), time(TIME_200MS)
H2: Badguy1, duty(SOL_DUTY_50), time(TIME_100MS)
H3: Badguy2, duty(SOL_DUTY_50), time(TIME_100MS)
H4: Badguy3, duty(SOL_DUTY_50), time(TIME_100MS)
H5: Badguy4, duty(SOL_DUTY_50), time(TIME_100MS)
H6: Mine Popper, duty(SOL_DUTY_75), time(TIME_66MS)
H7: Knocker, knocker
H8: Saloon Popper, duty(SOL_DUTY_75), time(TIME_66MS)

L1: Through Eject, ballserve, duty(SOL_DUTY_50), time(TIME_66MS)
L2: Left Sling, duty(SOL_DUTY_50), time(TIME_50MS)
L3: Right Sling, duty(SOL_DUTY_50), time(TIME_50MS)
L4: Left Jet, duty(SOL_DUTY_50), time(TIME_50MS)
L5: Right Jet, duty(SOL_DUTY_50), time(TIME_50MS)
L6: Left Gunfight Post, duty(SOL_DUTY_50), time(TIME_100MS)
L7: Right Gunfight Post, duty(SOL_DUTY_50), time(TIME_100MS)
L8: Bottom Jet, duty(SOL_DUTY_50), time(TIME_50MS)

G1: Mine motor, motor
G2: Mine, flash
G3: Left gun, flash
G4: Right gun, flash
G5: Left loop gate, duty(SOL_DUTY_50), time(TIME_66MS)
G6: Right loop gate, duty(SOL_DUTY_50), time(TIME_66MS)
G8: Beacon, flash

A1: Bank, flash
A2: Saloon, flash
A3: Train, flash
A4: Bronco, flash

F1: Move BartToy, duty(SOL_DUTY_75), time(TIME_33MS)
F4: Move BartHat, duty(SOL_DUTY_75), time(TIME_33MS)
F5: Train Reverse, motor, nosearch
F6: Train Forward, motor, nosearch

[templates]
# This section contains template definitions for device drivers.
# For each device requiring a driver, it specifies the file that
# contains the template code, and any parameters for the specific
# device.
Left Sling: driver(sling), sw=SW_LEFT_SLING, sol=SOL_LEFT_SLING, ontime=3, offtime=16
Right Sling: driver(sling),	sw=SW_RIGHT_SLING, sol=SOL_RIGHT_SLING, ontime=3, offtime=16
Left Jet: driver(jet), sw=SW_LEFT_JET, sol=SOL_LEFT_JET, ontime=3, offtime=16
Right Jet: driver(jet),	sw=SW_RIGHT_JET, sol=SOL_RIGHT_JET, ontime=3, offtime=16
Bottom Jet: driver(jet), sw=SW_BOTTOM_JET, sol=SOL_BOTTOM_JET, ontime=3, offtime=16

Left loop gate: driver(duty), sol=SOL_LEFT_LOOP_GATE, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60
Right loop gate: driver(duty), sol=SOL_RIGHT_LOOP_GATE, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=60

Train toy: driver(bivar), forward_sol=SOL_TRAIN_FORWARD, reverse_sol=SOL_TRAIN_REVERSE

Left Gunfight: driver(duty2), sol=SOL_LEFT_GUNFIGHT_POST, timeout=0, ontime=TIME_66MS, duty_mask=DUTY_MASK_25
Right Gunfight: driver(duty2), sol=SOL_RIGHT_GUNFIGHT_POST, timeout=0, ontime=TIME_66MS, duty_mask=DUTY_MASK_25

BadGuy1: driver(duty2), sol=SOL_BADGUY1, timeout=0, ontime=TIME_50MS, duty_mask=DUTY_MASK_12
BadGuy2: driver(duty2), sol=SOL_BADGUY2, timeout=0, ontime=TIME_50MS, duty_mask=DUTY_MASK_12
BadGuy3: driver(duty2), sol=SOL_BADGUY3, timeout=0, ontime=TIME_50MS, duty_mask=DUTY_MASK_12
BadGuy4: driver(duty2), sol=SOL_BADGUY4, timeout=0, ontime=TIME_50MS, duty_mask=DUTY_MASK_12




##########################################################################
# General Illumination
##########################################################################
[gi]
0: GI1
1: GI2
2: GI3
3: GI4
4: All GI

##########################################################################
# Tests
# These are additional test items that should appear in the TESTS menu.
##########################################################################
[tests]



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
Bronco: Left Loop Ridem, Left Loop Wildride, Left Loop BucknBronco
Sharpshoot: Right Loop Marksman, Right Loop Gunslinger, Right Loop Goodshot
Pollywater: Left Ramp Whitewater, Left Ramp Waterfall,  Left Ramp SavePolly
Pollybank: Right Ramp SoundAlarm, Right Ramp ShootOut, Right Ramp SavePolly
Pollytrain: Center Ramp CatchTrain, Center Ramp StopTrain, Center Ramp SavePolly
Ranks: Rank Stranger, Rank Partner, Rank Deputy, Rank Sheriff, Rank Marshall
Star: Star Motherlode, Star Stampede, Star Combo, Star HighNoon, Star BartBros, Star Showdown
Combos: Left Loop Combo, Left Ramp Combo, Center Ramp Combo, Right Loop Combo, Right Ramp Combo
Jackpots: Left Loop Jackpot, Left Ramp Jackpot, Center Ramp Jackpot, Right Loop Jackpot, Right Ramp Jackpot
Playfield: PF:all
Bonusx: Left BonusX, Right BonusX


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
Trough: Through Eject, Trough Eject, Trough 4, Trough 3, Trough 2, Trough 1, init_max_count(4)
Goldmine: Mine Popper, Mine Popper
Saloon: Saloon Popper, Saloon Popper


#------------------------------------------------------------------------
# The remaining sections describe software aspects, and not the physical
# machine.
#------------------------------------------------------------------------

##########################################################################
# Items for the Feature Adjustments menu.  Parameters indicate the
# type of adjustment and the default value.
##########################################################################
[adjustments]
Disable Train: yes_no, NO
Easy Stars: yes_no, NO
QD Target Hits: integer, 1
Bronco Bumper Hits: integer, 50
Sharpshoot time: integer, 3
Polly train shots: integer, 6
Light Lock Hits: integer, 1
Marshall Wave Time: integer, 5
Polly Mine time: integer, 3


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
##########################################################################
[scores]
10:
100:
200:
20K:
22500:
30K:
40K:
50K:
100K:
150K:
200K:
250K:
300K:
400K:
500K:
750K:
1M:
2M:
3M:
4M:
5M:

##########################################################################
# The default high scores.  Use GC to indicate the grand champion.
# The parameters are the initials followed by the score value.  Periods
# may optionally be used to group digits, but they are not necessary.
# Commas _cannot_ be used for this purpose since they separate parameters.
##########################################################################
[highscores]
GC: MYA, 500.000.000
1: AEN, 400.000.000
2: KAT, 350.000.000
3: MYA, 300.000.000
4: AEN, 250.000.000

##########################################################################
# Per-player bit flags.
##########################################################################
[flags]
gf outlane lit:
outlanes lit:
marshall lit:
gmm bumpers:
gmm eb lit:
bumper ml:
pollymine ml:
saloon bounty lit:
beacon bounty lit:
star stampede:
star highnoon:
star motherlode:
star showdown:
star bartbros:
star combo:
rank stranger:
rank partner:
rank deputy:
rank sheriff:
rank marshall:
bronco started:
river started:
polly bank started:
polly train started:
shshoot started:
shshoot finished:
bronco finished:
polly train finished:
polly bank finished:
polly river finished:
moo bronco:



##########################################################################
# System-wide bit flags.
##########################################################################
[globalflags]
normal mode:
quickdraw running:
gunfight running:
showdown running:
stampede running:
bronco running:
polly river running:
polly bank running:
polly train running:
shshoot running:
keep gates down:
gmm running:
marshall running:
bart running:
hiddenbart running:



##########################################################################
# Display effects
##########################################################################
[deffs]


##########################################################################
# Lamp effects
##########################################################################
[leffs]

##########################################################################
# Fonts used in this game.
##########################################################################
[fonts]
var5:
fixed6:
pcsenior:
misctype:
lithograph:

[timers]


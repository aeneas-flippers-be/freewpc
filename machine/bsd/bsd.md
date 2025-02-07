#--------------------------------------------------------------------------
# Machine description for Bram Stokers Dracula
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
Title: bsd
include platform/wpc/wpc-fliptronic.md

Pinmame-Zip: drac_l1.zip
Pinmame-ROM: drac_l1.rom
#Lamp-Matrix-Width:
#Lamp-Matrix-Height:


##########################################################################
# Use 'define' to emit a plain #define for anything not covered by
# some other means.
##########################################################################

define MACHINE_BSD
define MACHINE_NUMBER 501



##########################################################################
# Lamp Description
# The key is given in column/row format.  The first parameter must be
# the lamp name.  Optionally you can specify a color, and x() and y()
# for the location on the playfield.  Only a subset of lamp colors are
# recognized; see tools/genmachine for details.  Lamp location is
# given in terms of the Lamp-Matrix-Width and Lamp-Matrix-Height.
##########################################################################
[lamps]
16: R Ramp coffin Lock, green
17: Dracula face, white
18: RRamp 2M, orange
21: Coffin Lock 1, white
22: Coffin Lock 2, white
23: dracul_A, orange
24: RRamp 500K, orange
25: RRamp 1M, orange
26: RRamp 2M5, red
27: RRamp 2X, red
28: RRamp 1M5, orange
31: R Lane _Video, red
32: R Lane vIdeo, red
33: R Lane vi_Deo, red
34: R Lane vid_Eo, red
35: R Lane vide_O, red
36: d_Racula, orange
37: LDrain XBball, red
38: LReturn, yellow
41: RReturn mystery, yellow
42: RDrain special, orange
43: Coffin MBall, purple
44: Playfield 2X, green
45: Castle MBall, purple
46: Playfield 3X, green
47: Mist MBall, purple
48: _Dracula, orange
51: Coffin 1, white
52: Coffin 2, white
53: Magnet, white
54: Shoot Again, shoot-again, orange
55: Love Never Dies, ball-save, yellow
56: Coffin 3, white
57: L Ramp Castle Lock, red
58: L Ramp Diverter, green
61: Back L Skill, white
62: Back M Skill, white
63: Back R Skill, white
64: 3 lane L, red
65: 3 lane M, red
66: 3 lane R, red
67: drac_Ula, orange
68: in bumpers, white
71: dra_Cula, orange
72: dracu_La, orange
73: Left 3 Top, orange
74: Left 3 Middle, red
75: Left 3 Bottom, orange
76: Center 3 L, orange
77: Center 3 M, red
78: Center 3 R, orange
81: Rats hole
82: dr_Acula, orange
83: TL Mystery, white
84: TL Mist MB, yellow
85: TL Extra Ball, extra-ball, red
86: TL Castle Jackpot, blue
87: Launch ball, red
88: Start Button, yellow, start, cabinet

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
11: Right Flipper, button, intest, c_decl(sw_right_button)
12: Left Flipper, button, intest, c_decl(sw_left_button)
13: Start Button, yellow, start-button, cabinet, intest
14: Plumb Bob Tilt, c_decl(sw_tilt), cabinet, tilt, ingame, novalid
15: Drop target, debounce(TIME_200MS), edge
16: Drop score
17: Shooter, edge, shooter, novalid, debounce(TIME_200MS)
21: Slam Tilt, slam-tilt, ingame, cabinet
22: Coin Door Closed, noscore, novalid
25: Top3 Left, ingame
26: Top3 Middle, ingame
27: Top3 Right, ingame
28: R Ramp Score
31: Under shooter ramp
34: Launch Button, launch-button, cabinet, novalid
35: Left outlane, ingame
36: Left inlane, ingame
37: Right inlane, ingame
38: Right outlane, ingame
41: Trough 1, noscore, novalid, novalid
42: Trough 2, noscore, novalid, novalid
43: Trough 3, noscore, novalid, novalid
44: Trough 4, noscore, novalid, novalid
48: Outhole, outhole, service, novalid, intest, noscore
51: Video lane, opto
52: Left Magnet pocket, opto
53: Castle Lock 1, opto
54: Castle Lock 2, opto
55: Wireramp Popper, opto
56: Crypt Popper, opto
57: Castle Lock 3, opto
58: Mystery hole
61: Left Jet, ingame, c_decl(sw_jet), novalid
62: Right Jet, ingame, c_decl(sw_jet), novalid
63: Bottom Jet, ingame, c_decl(sw_jet), novalid
64: Left slingshot, ingame, c_decl(sw_sling), novalid
65: Right slingshot, ingame, c_decl(sw_sling), novalid
66: Left 3bank top, ingame, standup
67: Left 3bank middle, ingame, standup
68: Left 3bank bottom, ingame, standup
71: Castle Popper, opto
72: Coffin Popper, opto
73: Opto L ramp entry, opto
77: R ramp up
81: Magnet left
82: Ball on magnet, opto
83: Magnet right
84: L ramp score
85: L ramp diverted
86: Middle 3bank left, ingame, standup
87: Middle 3bank middle, ingame, standup
88: Middle 3bank right, ingame, standup

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
H1: Auto Launch, launch
H2: Coffin Popper, duty(SOL_DUTY_75), time(TIME_66MS)
H3: Castle Popper, duty(SOL_DUTY_75), time(TIME_66MS)
H4: Right ramp down, duty(SOL_DUTY_50), time(TIME_66MS)				#ok
H5: Crypt Popper, duty(SOL_DUTY_100), time(TIME_66MS)  
H6: Wireramp Popper, duty(SOL_DUTY_75), time(TIME_66MS)				# ok
H7: Knocker, knocker, duty(SOL_DUTY_75), time(TIME_50MS), nosearch
H8: Shooter ramp, duty(SOL_DUTY_50), time(TIME_66MS)			#to test hold

#L = low power J127
#### these are all 50v power
L1: Left slingshot, duty(SOL_DUTY_100), time(TIME_33MS)				# ok
L2: Right slingshot, duty(SOL_DUTY_100), time(TIME_33MS)			# ok
L3: Left Jet, duty(SOL_DUTY_75), time(TIME_50MS)
L4: Right Jet, duty(SOL_DUTY_75), time(TIME_50MS)
L5: Bottom Jet, duty(SOL_DUTY_75), time(TIME_50MS)
L6: Right ramp up, duty(SOL_DUTY_50), time(TIME_50MS)				# ok
L7: Outhole, duty(SOL_DUTY_50), time(TIME_133MS)					# ok
L8: Ball Release, ballserve, duty(SOL_DUTY_25), time(TIME_133MS)	# ok

# G = J126 on Power Driver Board
G1: Top R fl, flash
G2: Castle Jackpot fl, flash
G3: 3 bank gl house, flash
G4: TL corner mina, flash
G5: Castle altar fl, flash
G6: L ramp castle lock fl, flash
G7: R ramp 2X fl, flash
G8: Asylym fl, flash

# A = J122 pins 1-2-3-4
#### these are all 20v power
A1: Drop target, duty(SOL_DUTY_50), time(TIME_66MS)		# ok
A2: speaker panel fl, flash							
A3: mist magnet, nosearch, duty(SOL_DUTY_50) 
A4: mist motor, motor, nosearch

# F = J902 on Fliptronic II
#### these are all 50v power
F5: Ramp diverter, duty(SOL_DUTY_100), time(TIME_50MS)			
F6: Right gate, nosearch
F7: Castle lock rlse, duty(SOL_DUTY_100), time(TIME_50MS)	
F8: Left gate, nosearch, duty(SOL_DUTY_100), time(TIME_100MS)


[templates]
Left Sling: driver(sling), sw=SW_LEFT_SLINGSHOT, sol=SOL_LEFT_SLINGSHOT
Right Sling: driver(sling), sw=SW_RIGHT_SLINGSHOT, sol=SOL_RIGHT_SLINGSHOT
Left Jet: driver(jet), sw=SW_LEFT_JET, sol=SOL_LEFT_JET
Right Jet: driver(jet), sw=SW_RIGHT_JET, sol=SOL_RIGHT_JET
Lower Jet: driver(jet), sw=SW_BOTTOM_JET, sol=SOL_BOTTOM_JET
Outhole: driver(outhole), sol=SOL_OUTHOLE, swno=SW_OUTHOLE, swevent=sw_outhole

Ramp Div: driver(duty2), sol=SOL_RAMP_DIVERTER, timeout=TIME_3S, ontime=TIME_33MS, duty_mask=DUTY_MASK_50
Left Gate: driver(duty), sol=SOL_LEFT_GATE, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=TIME_3S
Right Gate: driver(duty), sol=SOL_RIGHT_GATE, ontime=TIME_300MS, duty_ontime=TIME_33MS, duty_offtime=TIME_16MS, timeout=TIME_3S
Drop Target: driver(drop), sol_up=SOL_DROP_TARGET, sol_down=SOL_NOT_DEFINED, sw=SW_DROP_TARGET, sw_event=sw_drop_target

MistMag: driver(mistmagnet), sol=SOL_MIST_MOTOR, up_sw_event=SW_MAGNET_RIGHT, down_sw_event=SW_MAGNET_LEFT



##########################################################################
# General Illumination
##########################################################################
[gi]
0: PF Upper
1: PF Middle
2: PF Lower
3: Insert1
4: Insert2

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
Draculalamps:_Dracula, d_Racula, dr_Acula, dra_Cula, drac_Ula, dracu_La, dracul_A
Videolamps: R Lane _Video, R Lane vIdeo, R Lane vi_Deo, R Lane vid_Eo, R Lane vide_O
Crosslamps: RRamp 2M, RRamp 500K, RRamp 1M, RRamp 2M5, RRamp 1M5, RRamp 2X
Coffindrac: Coffin 1, Coffin 2, Coffin 3




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
Trough: Ball Release, trough, init_max_count(4), \
	Trough 4, Trough 3, Trough 2, Trough 1
Crypt Popper: Crypt Popper, Crypt Popper, init_max_count(0)
Coffin Popper: Coffin Popper, Coffin Popper, init_max_count(0)
Castle Popper: Castle Popper, Castle Popper, init_max_count(0)
Castle Lock: Castle lock release, init_max_count(0), \
	Castle Lock 3, Castle Lock 2, Castle Lock 1
Wireramp Popper: Wireramp Popper, Wireramp Popper, init_max_count(0)

#------------------------------------------------------------------------
# The remaining sections describe software aspects, and not the physical
# machine.
#------------------------------------------------------------------------

##########################################################################
# Items for the Feature Adjustments menu.  Parameters indicate the
# type of adjustment and the default value.
##########################################################################
[adjustments]
Disable Magnet: yes_no, NO


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
Start Ball: MUS_PLUNGER
Tilt Warning: SND_BEHAVEYOURSELF
Tilt: SND_THISTOOEASY

##########################################################################
# A list of all scores needed by the game rules.
##########################################################################
[scores]
5K:
5M:
10M:
20M:
30M:


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

##########################################################################
# Lamp effects
##########################################################################
[leffs]


##########################################################################
# Timers
##########################################################################
[timers]
Asylum behind:
Altar behind:

##########################################################################
# The default high scores.  Use GC to indicate the grand champion.
# The parameters are the initials followed by the score value.  Periods
# may optionally be used to group digits, but they are not necessary.
# Commas _cannot_ be used for this purpose since they separate parameters.
##########################################################################
[highscores]
GC: AEN, 500.000.000
1: MYA, 400.000.000
2: KAT, 350.000.000
3: AEN, 300.000.000
4: MYA, 250.000.000

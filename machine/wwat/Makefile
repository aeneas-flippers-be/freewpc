#
# Game specific Makefile extensions
#
MACHINE_FILE = wwat.md

# Define the name of the GAME_ROM.  This is
# optional; you can delete it and a suitable
# default will be taken.
GAME_ROM_PREFIX = wwatr_l5

# Set ROM_PAGE_COUNT to the number of 16KB pages
# that should be present in the output image.
# The hardware supports a maximum of 64 pages;
# you can't exceed this.
#
# The 'system' will always reside in the uppermost
# two pages.  If the ROM is less than a full 64
# pages, then the pages are numbered from [N..64]
# anyway.
#
# 128KB.....8 pages
# 256KB.....16 pages
# 512KB.....32 pages
# 1MB...... 64 pages
#
ROM_PAGE_COUNT = 32

#################################################
#
# Simulation options.
#
# These options control the way that the game
# ROM is made available to pinmame for testing.
# They are only used during installation into
# the pinmame roms directory.
#
#################################################
MACHINE_MAJOR = 0
MACHINE_MINOR = 1

PINMAME_MACHINE = wwatr_l5
PINMAME_GAME_ROM = wwatr_l5.rom
PINMAME_OTHER_ROMS = ww_u*.l1

IMAGE_MAP += $(M)/ww.ild

#################################################
# Object files exported by this game
#
# GAME_OBJS  = .text page -- 
# the system page.  No decorator needed on function prototypes.
# RTTs must go here.  also place files that are called often here.
#
# GAME_PAGED_OBJS = page 59 =	Preferably, game functions go here.
# This works safely for any file that only uses CALLSET_ENTRY functions, deffs, and leffs.  
# GAME_PAGED_OBJS (probably should have been called GAME1_OBJS) is page 
# 59 (labelled MACHINE in the display at the bottom of the "err" file). 
# Prototypes need __machine__.  The space is shared with "EVENT", which 
# means that it is not as large as the other pages, but since "EVENT" is 
# the machinery behind callsets, files which have lots of CALLSET_ENTRY 
# points are more efficient when placed here. 
#
# GAME_OBJS  = .text page, no labeling or prototype needed 
# GAME_PAGED_OBJS = page 59, labelled MACHINE, prototypes use __machine__ 
# GAME_TEST_OBJS = page 58, no labeling or prototype needed  
# EFFECTS = page 57, 
# COMMON = page 56, , prototypes use __common__
# GAME2_OBJS = page 55, labelled MACHINE2, prototypes use __machine2__
# GAME3_OBJS = page 54, labelled MACHINE3, prototypes use __machine3__
# GAME4_OBJS = page 53, labelled MACHINE4, prototypes use __machine4__
# GAME5_OBJS = page 52, labelled MACHINE5, prototypes use __machine5__
#
# note: if we put tabs in between the file names you will get a linker error
# note: continue line with a '\' --make sure to leave off on last line or you will get a linker error
#GAME_TEST_OBJS =
#GAME_INCLUDES =
################################################### 


# page .text
GAME_OBJS = vars.o bbash.o bigfoothead.o bigfootdiv.o bigfoottgt.o cavehurry.o deffsobj.o jets.o \
kickback.o lock.o riverhurry.o redtgt.o wpoolmodes.o rafts.o

#this is about 30% full from the OS - page 59 
#also called MACHINE_PAGE in the file definition 
GAME_PAGED_OBJS = bigfootcave.o combos.o lanes.o rivertgt.o simpleshots.o

#also called MACHINE2_PAGE - page 55
GAME2_OBJS = dammode.o extraball.o goldrush.o lostmine.o multimill.o mball.o quickmb.o riverclass.o \
skill.o wetwilly.o wizard.o wpmanoverb.o wp5xpf2.o wpwpchall.o

#also called MACHINE3_PAGE - page 54
GAME3_OBJS = amode.o bonus.o deffs3.o leffs.o

#also called MACHINE4_PAGE - page 53
GAME4_OBJS = ww_modes.o
#tester.o

#also called MACHINE5_PAGE - page 52
GAME5_OBJS = 

GAME_TEST_OBJS = 

GAME_INCLUDES =





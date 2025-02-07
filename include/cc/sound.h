/*
* Copyright 2012 Aeneas Verhé
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

#ifndef _MACH_SOUND_H
#define _MACH_SOUND_H

#define SET_02_SND(x) ((2UL << 8) + (x))
#define SET_03_SND(x) ((3UL << 8) + (x))
#define SET_04_SND(x) ((4UL << 8) + (x))
#define SET_05_SND(x) ((5UL << 8) + (x))
#define SET_06_SND(x) ((6UL << 8) + (x))
#define SET_07_SND(x) ((7UL << 8) + (x))
#define SET_08_SND(x) ((8UL << 8) + (x))

//MAYOR = Mayor cheetum
//POLLY = Miss Polly
//BMD = Barmaid
//OLD = Old Cowboy
//BDG = Bad Guy
//BRT = Bart unnamed
//BIB = Bionic Bart
//BUB = Bubba Bart
//BAB = Bandolero Bart
//BGB = Big Bart
//BOS = Boss Bart

/* already default defined
//3E COINDOOR1
//3F COINDOOR2
//40 COINDOOR3
//41 COINDOOR4
D6 ESCAPE KEY                    SET_03_SND(0x)
D7 ENTER MENU                    SET_03_SND(0x)
D8 ATTENTION                    SET_03_SND(0x)
D9 - DD KEYS                    SET_03_SND(0x)
DE FUNNY KEY                    SET_03_SND(0x) ??
*/

//MUSIC
#define MUS_DEFAULT_AT_PLUNGER     0x1
#define MUS_DEFAULT_PLAY           0x2
#define MUS_FASTER_MODE_1          0x3
#define MUS_PART_INTRO_GUNFIGHT    0x4
#define MUS_LOOP_MODE_2            0x5
#define MUS_SHORT_VIOLIN           0x6
#define MUS_FAST_QD_COUNTDOWN      0x7
#define MUS_DEFAULT_MUSIC          0x8
#define MUS_INTRO_GUNFIGHT_TROM    0x9
#define MUS_BADGUY_UP_1            0xB
#define MUS_BADGUY_UP_3            0xD
#define MUS_BADGUY_UP_4            0xF
#define MUS_QUICKDRAW              0x19
#define MUS_TRAIN                  0x1A //train mode
#define MUS_NERVOUS_INTRO          0x1B
#define MUS_WHIP                   0x1C //horse mode ?
#define MUS_TRAIN_LOOP             0x1F //train mode
#define MUS_BG_NEW_MODE_FAST_INTRO 0x2A
#define MUS_DUMDUM_JIHAA           0x2C
#define MUS_NERVOUS_LOOP           0x5F
#define MUS_NERVOUS_LOOP_2         0x60
#define MUS_NERVOUS_LOOP_3         0x62
#define MUS_LONG_RUNNING_SOUND     0x16
#define MUS_BELL_INTRO_MODE_FAST   0x63 //bank ?

//VARIOUS SOUNDS
#define SND_APPLAUSE_1         0xA1
#define SND_APPLAUSE_2         0xA3
#define SND_APPLAUSE_3         0xA5
#define SND_APPLAUSE_JIHAA     0xA7
#define SND_OOH_APPLAUSE       SET_02_SND(0xBC)
#define SND_AAH_APPLAUSE       SET_02_SND(0xBE)

#define SND_BANG               0x17
#define SND_KABOOM             0x69
#define SND_BOOOOM             0xD1
#define SND_BOOOM_2            0xD6
#define SND_BOOM_1             0xF7
#define SND_BOOM_2             0xF9
#define SND_BOOM_3             0xFB
#define SND_BOOM_4             0xFD
#define SND_BOOM_5_FALLING_ROCK 0xFF
#define SND_EXPLOSION_1        SPEECH_SND(0x53)
#define SND_EXPLOSION_2        SPEECH_SND(0x55)
#define SND_THUNDER            SPEECH_SND(0x27)

#define SND_GUNSHOT_1          0x68
#define SND_GUNSHOT_2          0x6D
#define SND_GUNSHOT_3          0x6F
#define SND_FASTSHOT           0x93
#define SND_SHOOTING_BULLET_1  0x9B
#define SND_SHOOTING_BULLET_2  0x9D
#define SND_SHOOTING_BULLET_3  0x9F
#define SND_FASTSHOOTING       0xB5
#define SND_GUNSHOT            0xB7
#define SND_SHOT_1             SPEECH_SND(0x01)
#define SND_SHOT_2             SPEECH_SND(0x03)
#define SND_SHOT_3             SPEECH_SND(0x05)
#define SND_SHOT_4             SPEECH_SND(0x07)
#define SND_BULLETPASS         SPEECH_SND(0x40)
#define SND_PENG_1             SPEECH_SND(0x1F)
#define SND_PENG_2             SPEECH_SND(0x22)
#define SND_PENG_3             SPEECH_SND(0x24)
#define SND_PEW                0x67
#define SND_GUNCLICK           SPEECH_SND(0x67)

#define SND_BOTTLEBLOW         0xA9
#define SND_BLOW               0xAB
#define SND_FLYING_AIR         0x6B
#define SND_BREAKING_GLASS     0x77
#define SND_BREAK_GLASS        SPEECH_SND(0x0B)
#define SND_DRUP_1             0x3B
#define SND_DRUP_2             0x3D

#define SND_FIREWORKS_1        SPEECH_SND(0x37) //replay
#define SND_FIREWORKS_2        SPEECH_SND(0x39)
#define SND_FIREWORKS_3        SPEECH_SND(0x3B)
#define SND_FIREWORKS_4        SPEECH_SND(0x3D)
#define SND_FIREWORKS_5        0x7F

#define SND_DRUMS              0x2B
#define SND_BOUNTY_SND         0x2D
#define SND_CHILLING_INTRO_1   0x58
#define SND_CHILLING_INTRO_2   0x59

#define SND_TADADA_1           0x11
#define SND_TADADA_2           0x14
#define SND_TADADADUM          0x15
#define SND_PWOTPWOT           0x1D
#define SND_TADADADOM_FINISH   0x20
#define SND_TADADUM_HAPPY      0x22
#define SND_DUM                0x24
#define SND_HAPPY_DUM          0x26
#define SND_POMPOMPOM          0x29
#define SND_TADADUM            0x2F
#define SND_DRUMS_2            0x30
#define SND_HIHAT_1            0x32
#define SND_HIHAT_2            0x34
#define SND_HIHAT_3            0x36
#define SND_HIHAT_4            0x38
#define SND_TADADA             0x42
#define SND_TADA               0x44
#define SND_TADA_2             0x46
#define SND_TRUMPET_1          SPEECH_SND(0x29)
#define SND_TRUMPET_2          SPEECH_SND(0x2B)
#define SND_TRUMPET_3          SPEECH_SND(0x2D)

#define SND_METAL_BENG         0x71
#define SND_METAL_BENG_2       0x7B
#define SND_WOOD_CRACK_FALLING 0x65
#define SND_SOFT_CRASH         0x79
#define SND_WHOOP_BENG         0x83
#define SND_CRASH_FALLING      0x95
#define SND_RIKKETIK           0xDD
#define SND_FUNNY_HIT_ECHO     0xEB
#define SND_TA_DING            SPEECH_SND(0x15)
#define SND_BENG               SPEECH_SND(0x17)
#define SND_BENG_LOST          SPEECH_SND(0x1B)
#define SND_BANG_ECHO          SPEECH_SND(0x25)
#define SND_CRACKSHOOT         SPEECH_SND(0x36)
#define SND_METAL_TING         SPEECH_SND(0x5B)
#define SND_THUD               SPEECH_SND(0x5D)
#define SND_GUNSHOT_WOOD       SPEECH_SND(0x65)
#define SND_BUNG               SPEECH_SND(0x89)
#define SND_WOODCRACK          SPEECH_SND(0x35)
#define SND_CRACK              SPEECH_SND(0x5F)
#define SND_CRASH_1            SPEECH_SND(0x61)
#define SND_CRASH_2            SPEECH_SND(0x63)
#define SND_MOTOR_YIHAA        SPEECH_SND(0x1D)

//GAME START
#define SND_POLLY_PLAYER_ONE                  SET_03_SND(0x57) //startbutton press
#define SND_POLLY_PLAYER_TWO                  SET_03_SND(0x58)
#define SND_POLLY_PLAYER_THREE                SET_03_SND(0x59)
#define SND_POLLY_PLAYER_FOUR                 SET_03_SND(0x5A)
#define SND_POLLY_WELCOME_TO_TOWN_STRANGER    SET_03_SND(0x23) //on first ball
#define SND_MAYOR_WELCOME_TO_CC_STRANGER      SET_04_SND(0x4C)
#define SND_MAYOR_CHEETUM_AT_SERVICE          SET_04_SND(0x4D)
#define SND_UND_WELCOME_CAAACTUS_CANYON       SET_05_SND(0x2C)
#define SND_OLD_WELCOME_CC                    SET_04_SND(0xB2)
#define SND_MAYOR_CHEETUM                     SET_04_SND(0x6C)
#define SND_MAYOR_WELCOME_BACK                SET_04_SND(0x6D)
#define SND_BMD_COMIN_LOAD_OFF                SET_07_SND(0xD2)
#define SND_OLD_WANNA_WIN_SHOOT_BADGUYS       SET_04_SND(0xF7)
//SHOOTAGAIN
#define SND_POLLY_SHOOT_AGAIN                 SET_03_SND(0x56)
#define SND_POLLY_TRYAGAIN_BIGFELLOW          SET_03_SND(0x6B)
#define SND_BMD_SHOOT_AGAIN                   SET_07_SND(0xE5)
//BALL END
#define SND_POLLY_COME_BACK_SOON               SET_03_SND(0x6C)
#define SND_DNK_ALL_OVER_CITIZENS_BACK_TO_WORK SET_05_SND(0x8D)
#define SND_BRT_CELEBRITY_VOICES_IMP           SET_05_SND(0xB7)
#define SND_UND_HOPE_TO_SEE_YOU_SOON           SET_05_SND(0x25)
// MOO
#define SND_MOO_1                           SPEECH_SND(0x41)
#define SND_MOO_2                           SPEECH_SND(0x43)
// BONUS ROLLOVERS
#define SND_BONUSX_1                        SET_02_SND(0x6E)
#define SND_BONUSX_2                        SET_02_SND(0x6F)
#define SND_BONUSX_3                        SET_02_SND(0x70)
#define SND_BONUSX_4                        SPEECH_SND(0x20)
#define SND_BONUSX_5                        SPEECH_SND(0x22)
#define SND_BONUSX_6                        SPEECH_SND(0x24)
//RANK UP
#define SND_POLLY_CONGRATULATIONS_STRANGER  SET_03_SND(0x5C)
#define SND_POLLY_CONGRATULATIONS_PARTNER   SET_03_SND(0x5D)
#define SND_POLLY_CONGRATULATIONS_DEPUTY    SET_03_SND(0x5E)
#define SND_POLLY_CONGRATULATIONS_SHERRIF   SET_03_SND(0x5F)
#define SND_POLLY_CONGRATULATIONS_MARSHALL  SET_03_SND(0x60)
#define SND_POLLY_THANKYOU_STRANGER         SET_03_SND(0x66)
#define SND_POLLY_THANKYOU_PARTNER          SET_03_SND(0x67)
#define SND_POLLY_THANKYOU_DEPUTY           SET_03_SND(0x68)
#define SND_POLLY_THANKYOU_SHERRIF          SET_03_SND(0x69)
#define SND_POLLY_THANKYOU_MARSHALL         SET_03_SND(0x6A)
#define SND_MAYOR_CONGRATULATIONS_STRANGER  SET_04_SND(0x77)
#define SND_MAYOR_CONGRATULATIONS_PARTNER   SET_04_SND(0x78)
#define SND_MAYOR_CONGRATULATIONS_DEPUTY    SET_04_SND(0x79)
#define SND_MAYOR_CONGRATULATIONS_SHERRIF   SET_04_SND(0x7A)
#define SND_MAYOR_CONGRATULATIONS_MARSHALL  SET_04_SND(0x7B)
#define SND_OLD_PROMOTED_DEPUTY             SET_04_SND(0xDE)
#define SND_OLD_PROMOTED_SHERRIF            SET_04_SND(0xDF)
#define SND_OLD_PROMOTED_MARSHALL           SET_04_SND(0xE0)
#define SND_MAYOR_CITIZENS_NEW_SHERRIF      SET_04_SND(0x68)
#define SND_MAYOR_TOWNSFALK_NEW_MARSHALL    SET_04_SND(0x69)
#define SND_BMD_NICE_SHOOT_STRANGER         SET_07_SND(0xE7)
#define SND_BMD_NICE_SHOOT_PARTNER          SET_07_SND(0xE8)
#define SND_BMD_NICE_SHOOT_DEPUTY           SET_07_SND(0xE9)
#define SND_BMD_NICE_SHOOT_SHERRIF          SET_07_SND(0xEA)
#define SND_BMD_NICE_SHOOT_MARSHALL         SET_07_SND(0xEB)
// BRONCOS
#define SND_RUNNINGHORSE                   0xB3
#define SND_GALOP_FALLING_AAH              0x73
#define SND_OLD_BOY_GOTTA_HURT             SET_04_SND(0xE6)
#define SND_OLD_HORSE_BREAKING_YOU         SET_04_SND(0xE7)
#define SND_BMD_LIKE_RIDE_HORSE            SET_07_SND(0xD7)
#define SND_MAYOR_FINE_RIDE_SIR            SET_04_SND(0xA3)
#define SND_OLD_RIDEM_COWBOY               SET_04_SND(0xE8)
#define SND_WHIP_RUNNING_HORSES            SPEECH_SND(0x11)
// WATER
#define SND_POLLY_HEADING_FALL             SET_03_SND(0x3D)
#define SND_POLLY_OVER_FALL                SET_03_SND(0x3E)
#define SND_POLLY_GETTIN_ALL_WET           SET_03_SND(0x3F)

#define SND_WATER                          SPEECH_SND(0x97)
#define SND_BLUBLUBLUB                     0xAD
#define SND_UNDERWATER                     0xAF
// MINE - MOTHERLODE
#define SND_POLLY_HELP_IN_MINE             SET_03_SND(0x22) //intro polly
#define SND_POLLY_TRAPPED_IN_MINE          SET_03_SND(0x31)
#define SND_POLLY_HEEELP_MINE_ECHO         SET_03_SND(0x6D)
#define SND_POLLY_SCARED                   SET_03_SND(0x6E)
#define SND_POLLY_LOCK_LIT                 SET_03_SND(0x5B)	//lock lit
#define SND_MAYOR_LOCK_LIT                 SET_04_SND(0xA2)
#define SND_DNK_LOCK_IS_LIT                SET_05_SND(0x97)
#define SND_DNK_LOCK_IS_LIT_SO_AM_I        SET_05_SND(0x98)
#define SND_MAYOR_MINE_RIGHT_OPEN          SET_04_SND(0x9F)
#define SND_GOLDMINE_LOCK_INTRO_CART       0xF1 //intro MB
#define SND_GOLDMINE_RAILCART_PASSING      0xF3
#define SND_CWB_GOOOLD                     SET_02_SND(0x1B)
#define SND_CWB_MIIINE                     SET_02_SND(0x1C)
#define SND_CWB_MULTIBALL                  SET_02_SND(0x18)
#define SND_OLD_MOTHERLODE_LIT             SET_04_SND(0xCB) //motherlode
#define SND_OLD_SHOOT_MINE_FOR_MOTHERLODE  SET_04_SND(0xE1)
#define SND_CWB_MOTHERLODE_YIHAA           SET_02_SND(0x10)
#define SND_CWB_MOTHERLODE_YOOHOO          SET_02_SND(0x15)
#define SND_MAYOR_MOTHERLODE               SET_04_SND(0xA1)
#define SND_OLD_DOUBLE_MOTHERLODE          SET_04_SND(0xE4)
#define SND_CWB_DOUBLE_MOTHERLODE          SET_02_SND(0x1E)
#define SND_CWB_TRIPLE_MOTHERLODE          SET_02_SND(0x1F)
// MINE - EXTRA BALL
#define SND_CWB_EXTRAAA_BALL              SET_02_SND(0x1A)
#define SND_INTRO_EXTRABALL               0x4A
#define SND_MAYOR_EXTRA_BALL_LIT          SET_03_SND(0xFC)
#define SND_MAYOR_SHOOTMINE_EXTRA_BALL    SET_04_SND(0x0C)
#define SND_OLD_EXTRA_BALL_LIT            SET_04_SND(0xEA)
#define SND_BMD_EXTRA_BALL_LIT_HONEY      SET_07_SND(0xDD)
#define SND_BMD_EXTRA_BALL                SET_07_SND(0xE2)
// TRAIN
#define SND_POLLY_TIED_TRACK_CANT_GETUP   SET_03_SND(0x36)
#define SND_POLLY_WHY_ALWAYS_TO_TRACKS    SET_03_SND(0x51)
#define SND_MAYOR_POLLY_TIED_TRACKS_LIKES_IT_XX    SET_04_SND(0xA9)
#define SND_BRT_YOU_CANT_STOP_THIS_TRAIN  SET_06_SND(0x28)
#define SND_POLLY_TRAIN_COMING            SET_03_SND(0x38)
#define SND_POLLY_TRAIN_CLOSER            SET_03_SND(0x39)
#define SND_POLLY_STOP_TRAIN              SET_03_SND(0x37)

#define SND_STEAMTRAIN                    SPEECH_SND(0x0F)
#define SND_TRAIN_WOOSH_1                 0x0F
#define SND_TRAIN_WOOSH                   0xE5
#define SND_SHOOSHOOTRAIN                 0xCA
#define SND_SHOOTRAIN_FAST_2X             0xCB
#define SND_SHOOTRAIN_FAST_4X             0xCF
#define SND_TRAIN_FASTER                  0x1F
//POLLY MODES
#define SND_POLLY_OOH_JUST_IN_TIME        SET_03_SND(0x29) //busy
#define SND_POLLY_SO_GLAD_BACK            SET_03_SND(0x2A)
#define SND_POLLY_SAVE_LITTLE_OL_ME       SET_03_SND(0x2B)
#define SND_POLLY_DO_BE_GENTLEMEN_SAVE_ME SET_03_SND(0x2E)
#define SND_POLLY_HURRY_2X                SET_03_SND(0x2F)
#define SND_POLLY_HUUURRYYYY              SET_03_SND(0x30)
#define SND_POLLY_HELP                    SET_03_SND(0x32)
#define SND_POLLY_HURRY_AGAIN             SET_03_SND(0x33)
#define SND_POLLY_SAVE_ME_AGAIN           SET_03_SND(0x34)
#define SND_POLLY_HELP_ME_2X              SET_03_SND(0x35)
#define SND_POLLY_ABDUCTED_AGAIN          SET_03_SND(0x4A)
#define SND_OLD_MISS_POLLY_IN_TROUBLE     SET_04_SND(0xF2)
#define SND_POLLY_THANK_YOU               SET_03_SND(0x43) //saved
#define SND_POLLY_YOURE_GREATEST          SET_03_SND(0x44)
#define SND_POLLY_YOURE_MY_HERO           SET_03_SND(0x45)
#define SND_POLLY_MY_HERO                 SET_03_SND(0x46)
#define SND_POLLY_QUITE_A_MAN             SET_03_SND(0x47)
#define SND_POLLY_CONGRATULATIONS         SET_03_SND(0x48)
#define SND_POLLY_OOH_BRAVE               SET_03_SND(0x52)
#define SND_POLLY_MY_HERO_ECHO            SET_03_SND(0x6F)
#define SND_POLLY_NICE_SHOOTING           SET_03_SND(0x54)
//SHARPSHOOTER
#define SND_DNK_GOOD_ONE_BUDDY                    SET_05_SND(0x7E)
#define SND_DNK_BUDDY_SHOT_MY_DRINK              SET_05_SND(0x80)
#define SND_DNK_STOP_SHOOTING_DRINK              SET_05_SND(0x81)
#define SND_DNK_YOU_CAN_BURP_DO_THAT_XX            SET_05_SND(0x83)
#define SND_DNK_I_WAS_DRINKING_THAT_THANKYOU    SET_05_SND(0x86)
#define SND_DNK_NEVER_SEEN_NOTHING_LIKE_THAT    SET_05_SND(0x8A)
#define SND_DNK_WHAT_THE                           SET_05_SND(0x8F)
#define SND_DNK_AARGH                              SET_05_SND(0x91)
#define SND_DNK_IM_THIRSTY                     SET_05_SND(0x83)
#define SND_DNK_OOH_AAUW                         SET_05_SND(0x94)
#define SND_OLD_HURRY_OUT_TIME                   SET_04_SND(0xB5)
#define SND_OLD_WELL_NICE_SHOOTIN                  SET_04_SND(0xB9)
#define SND_OLD_SAY_THING_LOADED_OR_NOT         SET_04_SND(0xDC)

#define SND_CRAZY_PIANO_FAST            0x5F
#define SND_CRAZY_PIANO_RUNNING         0x60
#define SND_CRAZY_PIANO_3               0x62
#define SND_BREAKING_GLASS_2            0x87
#define SND_GLASS_BREAKING              SPEECH_SND(0x0B)
// BANK
#define SND_COINS_FALLING                        0x89
#define SND_COIN_ROLLING                         0x81
#define SND_UND_OH_GOOD_MAYHEM_BANK              SET_05_SND(0x1B)
#define SND_MAYOR_BARTBOYS_ROBBING_BANK          SET_04_SND(0xA5)
#define SND_MAYOR_DO_SOMETHING_MONEY_IN_THERE    SET_04_SND(0x6E)
// GUNFIGHT - QUICKDRAW - BADGUYS
#define SND_MAYOR_QUICKDRAW_LIT             SET_04_SND(0x0D)    //quickdraw lit
#define SND_UND_OH_GOODY_QUICKDRAW_LIT      SET_05_SND(0x18)
#define SND_UND_QUICKDRAW_GOOD_BUSINESS     SET_05_SND(0x19)
#define SND_BMD_QD_LIT                      SET_07_SND(0xF8)
#define SND_MAYOR_GUNFIGHT_LIT              SET_04_SND(0x0E)    //gunfight lit
#define SND_OLD_GUNFIGHT_LIT                SET_04_SND(0xD5)
#define SND_OLD_GUNFIGHT_LIT_REMINDER       SET_04_SND(0xD6)
#define SND_OLD_SMELL_GUNFIGHT_BREWING      SET_04_SND(0xD1)
#define SND_UND_THERES_GONNA_BE_GUNFIGHT    SET_05_SND(0x1A)
#define SND_MAYOR_OK_SON_LETS_GUNFIGHT      SET_03_SND(0xEC)	//gunfight start
#define SND_MAYOR_DONTMOVE_GUNFIGHT         SET_04_SND(0x05)
#define SND_BMD_LOOKS_LIKE_GF               SET_07_SND(0xF9)
#define SND_BDG_TIME_GUNFIGHT_LAWMAN        SET_07_SND(0x4B)
#define SND_BDG_LETS_GUNFIGHT               SET_07_SND(0x4F)
#define SND_GF_READY                        SET_06_SND(0x0A)    //gunfight start
#define SND_GF_SET                          SET_06_SND(0x0B)
#define SND_GF_GET_READY                    SET_06_SND(0x0C)
#define SND_BRT_DRAW                        SET_05_SND(0xE3)
#define SND_POLLY_GETHIM_BLOW_HEAD_OFF      SET_03_SND(0x4F)    //during badguy shootouts
#define SND_MAYOR_BADGUY_OUTTHERE           SET_04_SND(0x7E)
#define SND_MAYOR_SHOOT_BADGUY              SET_04_SND(0x7F)
#define SND_MAYOR_GET_THAT_BAD_GUY          SET_04_SND(0x81)
#define SND_BMD_HIT_BADGUY                  SET_07_SND(0xFA)
#define SND_OLD_GET_BADGUY                  SET_04_SND(0xD9)
#define SND_OLD_NAIL_BADGUY_LAWMAN          SET_04_SND(0xFA)
#define SND_OLD_SHOOT_BADGUY_2X             SET_04_SND(0xFD)
#define SND_DNK_SHOOT_THAT_BURP_BADGUY_XX   SET_05_SND(0x88)
#define SND_BRT_YEAH_SHOOT_BADGUY           SET_07_SND(0x1C)
#define SND_BDG_YOU_CANT_SHOOT              SET_06_SND(0x0E)
#define SND_BDG_COMON_TUFFGUY               SET_06_SND(0x10)
#define SND_BDG_IM_OVER_HERE                SET_06_SND(0x11)
#define SND_BDG_COMON_TAKE_BEST_SHOT        SET_06_SND(0x12)
#define SND_BDG_OH_YOU_MISSED_HEHE          SET_06_SND(0x1B)
#define SND_BDG_IM_STILL_STANDING           SET_06_SND(0x1C)
#define SND_BDG_YOU_MISSED_HEHE             SET_06_SND(0x1D)
#define SND_BDG_HEHE                        SET_06_SND(0x27)

#define SND_MAYOR_NICE_SHOOTING_SIR         SET_04_SND(0x91)	// end shooting
#define SND_MAYOR_QUITE_ACT_SIXSHOOTERS     SET_04_SND(0x92)
#define SND_MAYOR_4TH_JULY_GOPHERSHOOT      SET_04_SND(0x94)
#define SND_OLD_AINT_SEEN_MANY_HOLES        SET_04_SND(0xD2)
#define SND_UND_DEAD_RINGER_HAHA            SET_05_SND(0x26)
#define SND_BMD_DIDNT_LIKE_DEADBEAT         SET_07_SND(0xD3)
#define SND_BMD_WHAT_YOU_PACKIN             SET_07_SND(0xD5)
#define SND_BMD_LIKE_COLT_45                SET_07_SND(0xDF)
#define SND_BMD_AMAZIN                      SET_07_SND(0xD8)
#define SND_UND_LOOK_AT_BODYCOUNT_THERE_GOES_WEEKEND    SET_05_SND(0x17)
#define SND_UND_OH_GOODY_SHOOT_ALL          SET_05_SND(0x1C)
// DROPTGT MULTIBALL
//#define SND_MAYOR_VIGIL_VILLAIN           SET_04_SND(0x)  //todo NOT FOUND anymore ??
#define SND_MAYOR_SHOOT_EVERYTHING          SET_03_SND(0xEB)
#define SND_BMD_SHOOT_ANYTHING              SET_07_SND(0xE4)
#define SND_DNK_LOOKOUT_GUYS_HAVE_GUNS      SET_05_SND(0x79)
#define SND_MAYOR_JUST_SHOOTEM              SET_04_SND(0x8D)
#define SND_MAYOR_VARIOUS_NOGOODNIKS        SET_04_SND(0x85)
#define SND_MAYOR_SHOOT_SCURVY_SCOUNDRAL    SET_04_SND(0x83)
#define SND_MAYOR_SHOOT_ANYTHING_POPSUP     SET_04_SND(0x93)
#define SND_UND_RESPECTABLE_BODYCOUNT_INDEED SET_05_SND(0x1D)
#define SND_UND_DROPPING_LIKE_FLIES         SET_05_SND(0x23)
#define SND_UND_SO_MANY_BODIES_LITTLE_TIME  SET_05_SND(0x24)
#define SND_UND_SHOOTING_IS_KILLING_ME      SET_05_SND(0x29)
#define SND_OLD_SHOOT_ALL_BADGUYS           SET_04_SND(0xEB)
#define SND_BDG_YOU_SHOT_MY_BROTHER         SET_07_SND(0x4C)
#define SND_BDG_WAS_MY_BROTHER              SET_07_SND(0x4D)
#define SND_BDG_YOU_HURT_MY_BROTHER         SET_07_SND(0x4E)
//JACKPOTS
#define SND_CWB_JACKPOT_HEHE                    SET_02_SND(0x11)
#define SND_CWB_JACKPOT                         SET_02_SND(0x12)
#define SND_CWB_JACKPOT_YIHAA                   SET_02_SND(0x14)
#define SND_POLLY_JACKPOT                       SET_03_SND(0x53)
#define SND_MAYOR_JACKPOT                       SET_04_SND(0x0F)
#define SND_OLD_JACKPOT                         SET_04_SND(0xC2)
#define SND_DNK_JACKPOT_WHOOPIE                 SET_05_SND(0x96)
#define SND_DNK_JACKPOT_DRINK_TO_THAT           SET_05_SND(0x99)
#define SND_BRT_JACKPOT_DANGIT                  SET_06_SND(0x16)
#define SND_BMD_JACKPOT                         SET_07_SND(0xE1)
// BOUNTYS
#define SND_MAYOR_BOUNTY_WAITING                SET_03_SND(0xF4)
#define SND_MAYOR_BOUNTY_LIT                    SET_03_SND(0xF5)
#define SND_MAYOR_YOUR_BOUNTY_FRIEND            SET_03_SND(0xF6)
#define SND_MAYOR_BOUNTY_COLL                   SET_04_SND(0x12)
#define SND_MAYOR_COLLECT_BOUNTY_SON            SET_04_SND(0x13)
// FINAL GAME WON
#define SND_MAYOR_HAD_ENOUGH_OF_BARTBOYS       SET_04_SND(0x80)
#define SND_MAYOR_KEY_OUR_CITY                 SET_03_SND(0xEF)
#define SND_MAYOR_JOB_HERE_DONE                SET_03_SND(0xF0)
#define SND_MAYOR_THANKYOU_CLEANING_CC         SET_03_SND(0xF2)
// STAMPEDE
#define SND_CWB_STAMPEDE_MULTIBALL_YIHAA       SET_02_SND(0x13)
#define SND_OLD_ITS_A_STAMPEDE                 SET_04_SND(0xEC)
// SHOWDOWN
#define SND_CWB_SHOWDOWN                       SET_02_SND(0x1D)
#define SND_MAYOR_OH_MY_SHOWDOWN               SET_03_SND(0xED)
// HIGH NOON
#define SND_MAYOR_OHNO_ITS_HIGH_NOON           SET_03_SND(0xEE)
// MARSHALL MULTIBALL
#define SND_CWB_MARSHALL_MULTIBALL             SET_02_SND(0x20)
// GENERAL SHOT INSTRUCTIONS
#define SND_MAYOR_ONLY_4_LIGHTS_TO_COMPLETE_STAR SET_04_SND(0x07)
#define SND_MAYOR_3_LIGHTS                      SET_04_SND(0x08)
#define SND_MAYOR_2_LIGHTS                      SET_04_SND(0x09)
#define SND_MAYOR_1_LIGHT                       SET_04_SND(0x0A)
#define SND_MAYOR_GETUP_CENTER_RAMP_SIR         SET_04_SND(0x8F)
#define SND_MAYOR_SHOOT_SALOON                  SET_04_SND(0x01)
#define SND_MAYOR_SHOOT_RIGHT_RAMP              SET_04_SND(0x02)
#define SND_MAYOR_NICE_LOOPING_SIR              SET_04_SND(0x60)
#define SND_MAYOR_LEFT_RAMP_WIDE_OPEN           SET_04_SND(0x5E)
#define SND_MAYOR_RIGHT_RAMP_SIR                SET_04_SND(0x5F)
#define SND_OLD_HEADUP_LEFT_RAMP                SET_04_SND(0xF3)
#define SND_OLD_SHOOT_CENTER_RAMP               SET_04_SND(0xF4)
#define SND_OLD_HEAD_RIGHT_RAMP                 SET_04_SND(0xF5)
#define SND_MAYOR_TIME_ONE_MORE_SHOT            SET_04_SND(0x95)
#define SND_MAYOR_SUGGEST_HURRY                 SET_04_SND(0x97)
#define SND_MAYOR_REPLAY                        SET_04_SND(0x03)
#define SND_MAYOR_SPECIAL                       SET_04_SND(0x04)
#define SND_MAYOR_FREE_GAME                     SET_04_SND(0x06)
#define SND_BRT_TILT                            SET_05_SND(0xC0)
// MODE BAD
#define SND_MAYOR_CHECK_SIGHTS_WEAPON            SET_04_SND(0xAE)
#define SND_MAYOR_SURE_ITS_LOADED_SIR            SET_04_SND(0xAF)
#define SND_MAYOR_TOO_CLOSE_COMFORT              SET_04_SND(0x57)
#define SND_MAYOR_NOBODY_PANIC                   SET_04_SND(0x6A)
#define SND_MAYOR_DONT_STAND_THERE_DO_SOMETHING  SET_04_SND(0xAC)
#define SND_CWB_CHECK_SIGHTS_THING               SET_05_SND(0x00)
// MODE WON
#define SND_MAYOR_CONGRATULATIONS_SIR            SET_04_SND(0x74)
#define SND_MAYOR_CONGRATULATIONS                SET_04_SND(0x76)
#define SND_MAYOR_THIS_CALLS_DRINK               SET_04_SND(0x5C)
#define SND_MAYOR_SAY_PRETTY_GOOD_EYE            SET_04_SND(0x5D)
#define SND_MAYOR_JOB_WELL_DONE                  SET_04_SND(0x6F)

//VARIOUS
#define SND_MAYOR_BADGUY_1                       SET_04_SND(0x10)
#define SND_MAYOR_BADGUY_2                       SET_04_SND(0x11)
#define SND_MAYOR_OOOWH                          SET_04_SND(0x56)
#define SND_OLD_LAUGH_COUGH                      SET_04_SND(0xB0)
#define SND_OLD_HEHEHE                           SET_04_SND(0xBA)
#define SND_OLD_WHOOHOO                          SET_04_SND(0xDB)
#define SND_OLD_DONT_MOVE                        SET_04_SND(0xF1)

// ALL BARTS
#define SND_BRT_YIHAA                           SET_07_SND(0x9E)
#define SND_BRT_YEEE                            SET_07_SND(0x9F)
#define SND_BRT_YIHAA_2                         SET_07_SND(0xA0)
#define SND_BRT_WIPPY                           SET_07_SND(0xA1)
#define SND_BRT_YIHOO1                          SET_07_SND(0xA2)
#define SND_BRT_YIHOO2                          SET_07_SND(0xA3)
#define SND_BRT_YIHOO3                          SET_07_SND(0xA4)
#define SND_BRT_YIHOO4                          SET_07_SND(0xA5)
#define SND_BRT_YIHOO5                          SET_07_SND(0xA7)
#define SND_BRT_YIHOO6                          SET_07_SND(0xAA)
#define SND_BRT_OOOH                            SET_07_SND(0xAE)
//BIG BART
#define SND_BGB_MESS_WITH_ME_WILL_YA            SET_05_SND(0xAA) //Big Bart start
#define SND_BGB_NAME_BIG_BART                   SET_05_SND(0xBA)
#define SND_BGB_NOBODYS_HOME_GO_AWAY            SET_07_SND(0x3D)
#define SND_BGB_SHOOT_INITIALS_IN_YA_LAWMAN     SET_05_SND(0xB1)
#define SND_BGB_AAW                             SET_06_SND(0xB4) //BGB hit
#define SND_BGB_AAW_THAT_HURT                   SET_05_SND(0xB6)
#define SND_BGB_AAW_TELLYA_THAT_HURT            SET_05_SND(0xB8)
#define SND_BGB_AAW_DANGIT                      SET_05_SND(0xB9)
#define SND_BGB_THINK_DOING_PELGRIM             SET_05_SND(0xBB)
#define SND_BGB_IM_DONE_FOR                     SET_05_SND(0xBC) //BGB defeated
#define SND_BGB_ALL_FOLKS                       SET_05_SND(0xBD)
#define SND_BGB_BIRDS_DONE_NOW                  SET_05_SND(0xBE)
// BANDOLERO BART
#define SND_BAB_DONT_THINK_SEE_YA_I_DO             SET_07_SND(0x09) // start BaB
#define SND_BAB_MESSING_BANDOLERO_BART             SET_07_SND(0x0D)
#define SND_BAB_HIT_BROADSIDE_BURRITO              SET_07_SND(0x0F) // BaB during fight
#define SND_BAB_BORROW_SHOOT_BETTER                SET_07_SND(0x10)
#define SND_BAB_OH_WONT_HURT                       SET_07_SND(0x0C)
#define SND_BAB_COMEON_LONE_RANGER                 SET_07_SND(0x1D)
#define SND_BAB_OOOH_BENG                          SET_07_SND(0x1F)
#define SND_BAB_OH_YOU_GOT_ME                      SET_07_SND(0x20)
#define SND_BAB_BEEN_SHOT                          SET_07_SND(0x12)
#define SND_BAB_OH_THINK_BEEN_HIT                  SET_07_SND(0x0B)
#define SND_BAB_AAW_BRIDGEWORK                     SET_07_SND(0x14)
#define SND_BAB_AW_BRIDGEWORK                      SET_07_SND(0x1A)
#define SND_BAB_SEE_YOUR_PRETTY_GOOD               SET_07_SND(0x16) // BaB defeated
#define SND_BAB_OOH_AIRCONDITIONED                 SET_07_SND(0x0E)
#define SND_BAB_LOOK_BLOOD_WIFE_KILL_ME            SET_07_SND(0x11)
#define SND_BAB_ADIOS_AMIGO_TIME_SIESTA            SET_07_SND(0x15)
//BUBBA BART
#define SND_BUB_MESS_BUBBA_YOU                      SET_07_SND(0x6E) // bubba start
#define SND_BUB_BUBBA_MESS_YOU_UP                   SET_07_SND(0x7D)
#define SND_BUB_BUBBA_SHINY_BALL                    SET_07_SND(0x71)
#define SND_BUB_BUBBY_HIT                           SET_07_SND(0x6C) // bubba hits
#define SND_BUB_BUBBY_MAD_NOW                       SET_07_SND(0x6D)
#define SND_BUB_SHINY_BALL_HURT                     SET_07_SND(0x72)
#define SND_BUB_AAW                                 SET_07_SND(0x75)
#define SND_BUB_OOW                                 SET_07_SND(0x76)
#define SND_BUB_OOW_2                               SET_07_SND(0x78)
#define SND_BUB_OOW_3                               SET_07_SND(0x7A)
#define SND_BUB_ME_BUBBA_YOU_DAD                    SET_07_SND(0x7B)
#define SND_BUB_BENG                                SET_07_SND(0x7E)
#define SND_BUB_YOU_DAD                             SET_07_SND(0x7F)
#define SND_BUB_OH_BUBBA_HIT                        SET_08_SND(0x98)
#define SND_BUB_BUBBA_SLEEP_NOW                     SET_07_SND(0x7C) //bubba defeated
#define SND_BUB_BUBBA_MESS_PANTS                    SET_07_SND(0x6F)
#define SND_BUB_BUBBA_COOKOO                        SET_07_SND(0x70)
//Bart
#define SND_BRT_HANKERING_LEAD                  SET_05_SND(0xDD) //Bart start
#define SND_BRT_LOOKS_COMPANY                   SET_05_SND(0xE0)
#define SND_BRT_ASKING_FOR_IT                   SET_05_SND(0xE4)
#define SND_BRT_SHOW_ME_YOUR_STUFF              SET_06_SND(0x0D)
#define SND_BRT_MY_TOWN_LAWMAN                  SET_06_SND(0x08)
#define SND_BRT_GO_GET_HIM                      SET_05_SND(0xF0)
#define SND_BRT_GET_THAT_LAWMAN                 SET_05_SND(0xF5)
#define SND_BRT_BANG_HURT_A_LITTLE              SET_05_SND(0xAB) //Bart hit
#define SND_BRT_NOTHING_BUT_LITTLE_HOLE         SET_05_SND(0xAC)
#define SND_BRT_MESSING_WRONG_HOMBRE            SET_05_SND(0xAE)
#define SND_BRT_NOTHING_BUT_SCRATCH             SET_06_SND(0x0F)
#define SND_BRT_AAW_I_SAID                      SET_05_SND(0xB0)
#define SND_BRT_AUW                             SET_05_SND(0x05)
#define SND_BRT_OOHWOWOW                        SET_06_SND(0x06)
#define SND_BRT_OH_HOT_LEAD                     SET_06_SND(0x13)
#define SND_BRT_OK_IM_INJURED_ENOUGH            SET_06_SND(0x14)
#define SND_BRT_AAW                             SET_06_SND(0x17)
#define SND_BRT_AAAW                            SET_06_SND(0x18)
#define SND_BRT_AAH_OWOWOW                      SET_06_SND(0x19)
#define SND_BRT_LOOK_OUT                        SET_06_SND(0x26)
#define SND_BRT_BROKE_FAV_TOY                   SET_05_SND(0xFD)
#define SND_BRT_YOU_SHOT_MY_BROTHER             SET_05_SND(0xFF)
#define SND_BRT_OOW                             SET_05_SND(0xDF)
#define SND_BRT_OH_NO                           SET_05_SND(0xE5)
#define SND_BRT_OOH                             SET_05_SND(0xE6)
#define SND_BRT_OOH2                            SET_05_SND(0xE7)
#define SND_BRT_NEVER_LIKED_HIM_ANYWAY          SET_06_SND(0x02) //Bart done
#define SND_BRT_OH_SHUTUP                       SET_06_SND(0x09)
#define SND_BRT_YOU_SHOT_EVERYBODY              SET_06_SND(0x1A)
#define SND_BRT_ON_TO_NEXT_TOWN_BOYS            SET_06_SND(0x15)
#define SND_BRT_YOU_NEVER_CATCH_US              SET_06_SND(0x29)
#define SND_BRT_HEAD_FOR_HILLS                  SET_06_SND(0x2A)
#define SND_BRT_BETTER_LUCK_NEXT_TIME           SET_05_SND(0xE1)
#define SND_BRT_WELL_BE_BACK_LAWMAN             SET_05_SND(0xE2)
#define SND_BRT_TILL_WE_MEET_AGAIN              SET_05_SND(0xEF)
// Boss Bart
#define SND_BOS_WERE_BARTBOYS_AND_IM_BOSS    SET_07_SND(0x3A) //BOSS Bart intro
#define SND_BOS_LOOK_HERE_SHERRIF_OF_WEEK    SET_07_SND(0x3B)
#define SND_BOS_LOVE_SMELL_LEAD_MORNING      SET_07_SND(0x3C)
#define SND_BOS_GOODY_TARGET_PRACTISE        SET_07_SND(0x3F)
#define SND_BOS_PREPARE_FOR_DESTRUCTION_MY_FRIEND SET_06_SND(0x1E)
#define SND_BOS_PREPARE_FOR_PAIN_LAWMAN      SET_06_SND(0x2F)
#define SND_BOS_NO_MORE_MR_NICE_GUY          SET_06_SND(0x1F)
#define SND_BOS_MY_SECRET_WEAPON             SET_06_SND(0x20)
#define SND_BOS_TOUGH_GUY_DEAL_WITH_THIS     SET_06_SND(0x21)
#define SND_BOS_ITS_YOU_AND_ME               SET_06_SND(0x25)
#define SND_BOS_OH_JUST_BOUGHT_THAT_THING    SET_06_SND(0x22) // BOSS shield broke
#define SND_BOS_YOU_BROKE_MY_TOY             SET_06_SND(0x23)
#define SND_BOS_DONT_MAKE_THEM_LIKE_USED_TO  SET_06_SND(0x24)
#define SND_BOS_GONNA_GET_MONEY_BACK         SET_06_SND(0x31)
#define SND_BOS_HAHAHA                       SET_06_SND(0x2B) // BOSS hitting him
#define SND_BOS_MOEHAHAH                     SET_06_SND(0x2C)
#define SND_BOS_MOEHAHAHAH                   SET_06_SND(0x2D)
#define SND_BOS_YOUR_ASKIN_FOR_IT            SET_06_SND(0x2E)
#define SND_BOS_WHY_YA_DO_THAT               SET_06_SND(0x30)
#define SND_BOS_ALLRIGHT_I_HAD_IT            SET_06_SND(0x32)
#define SND_BOS_OH_IM_HIT                    SET_07_SND(0x40)
#define SND_BOS_JUST_FLESHWOUND              SET_07_SND(0x41)
#define SND_BOS_NEVER_USED_FINGER_ANYWAY     SET_07_SND(0x43)
#define SND_BOS_OH_YOU_GOTME                 SET_02_SND(0x00)
#define SND_BOS_BART_AAUW                    SET_02_SND(0x06)
#define SND_BOS_BART_OWOWOWOWW               SET_02_SND(0x09)
#define SND_BOS_COUGH                        SET_02_SND(0x64)
#define SND_BOS_BART_AAH_FALLING             SET_02_SND(0x07) // BOSS victory
#define SND_BOS_BART_OH_IM_A_GONER           SET_02_SND(0x01)
#define SND_BOS_DYING_1                      SET_02_SND(0x65)
#define SND_BOS_DYING_2                      SET_02_SND(0x66)
#define SND_BOS_DUYING_3_OOW                 SET_02_SND(0x67)
#define SND_BOS_THINK_JUST_REST_BIT          SET_07_SND(0x44)
#define SND_BOS_WELL_BOYS_IM_GONER           SET_07_SND(0x45)
#define SND_BOS_NICE_KNOWING_YA_BOYS         SET_07_SND(0x46)
#define SND_BOS_BETTER_THAN_HE_LOOKS_BOYS    SET_07_SND(0x48)
#define SND_BOS_GIMME_NICE_PLOT_BOOTHILL     SET_07_SND(0x49)
#define SND_BOS_SEE_SIX_FEET_UNDER           SET_07_SND(0x4A)
//BIONIC BART
#define SND_BIB_IM_BIOB_UNIT                    SET_08_SND(0x34) //BioB start
#define SND_BIB_PREPARE_ANNIHALITION            SET_08_SND(0x36)
#define SND_BIB_TIME_PAYBACK_LAWMAN             SET_08_SND(0x37)
#define SND_BIB_YOU_DENTED_ARMOR                SET_08_SND(0x38) //BioB busy
#define SND_BIB_SCRAMBLING_MEM_BANKS            SET_08_SND(0x3A)
#define SND_BIB_NOT_FEEL_GOOD                   SET_08_SND(0x3B)
#define SND_BIB_HOLE_MACHINERY                  SET_08_SND(0x3C)
#define SND_BIB_AAW                             SET_08_SND(0x3D)
#define SND_BIB_OUCH_THAT_HURT                  SET_08_SND(0x3E)
#define SND_BIB_AAW_2                           SET_08_SND(0x3F)
#define SND_BIB_VOIDED_WARRANTY                 SET_08_SND(0x41)
#define SND_BIB_NOT_TRU_YET                     SET_08_SND(0x43)
#define SND_BIB_SERVICE_REPR                    SET_08_SND(0x44)
#define SND_BIB_PINBALLS_NOT_PHASE              SET_08_SND(0x47)
#define SND_BIB_HUMID                           SET_08_SND(0x48)
#define SND_BIB_EAT_TIRE                        SET_08_SND(0x4A)
#define SND_BIB_WARNING                         SET_08_SND(0x4B)
#define SND_BIB_IM_NEW_SHERRIF                  SET_08_SND(0x46) //BioB won
#define SND_BIB_HASTALA_VISTA                   SET_08_SND(0x35)
#define SND_BIB_SYSTEMS_SHUTING_DOWN            SET_08_SND(0x39) //you won
#define SND_BIB_GAME_OVER                       SET_08_SND(0x4C)
#define SND_MACHINE_NOISE   	        0x85
#define SND_HEAVY_THUMP_BIOB_FOOTSTEPS  0x8D
#define SND_METAL_ALARM                 0x8F
#define SND_METAL_ALARM_2            	0x91
#define SND_ROBO_MOVING_SOUND           0x97
#define SND_APPROACH_MISSILE    	    0xC3
#define SND_MISSILE_HIT                 0xC5
#define SND_DINO_HIT                    0xC8
#define SND_COMPUTERBLIPS               0x7D
#define SND_LASER_BOOM                  0xD9

#endif /* _MACH_SOUND_H */

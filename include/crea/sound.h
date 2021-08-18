/*
 *	Popeye sound definition 2020 by Aeneas Verhe
 *
 *
 */
#ifndef _MACH_SOUND_H
#define _MACH_SOUND_H










/*

	#define MUS_RAFT1			0x03
	#define MUS_RAFT2			0x04
	#define MUS_RAFT3			0x05
	#define MUS_RAFT4			0x06
	#define MUS_RAFT5			0x07
	#define MUS_RAFT6			0x08
	#define MUS_RAFT7			0x09
	#define MUS_RAFT8			0x0A
#define MUS_RAFT9			0x0B
	#define MUS_GAMEOVER		0x0C #enter initials

#define MUS_HURRYUP_MANOVERB	0x0D
	#define MUS_MULTIBALL			0x0E 	#mball start tune
#define MUS_BIGFBLUFFMODE		0x0F		#mball after jackpot ?

	#define MUS_WPOOL_2		0x10
	#define MUS_MANOVERB_1		0x11
	#define MUS_HURMODE_RELOCK1		0x12
	#define MUS_HURRYMODE2		0x13
	#define MUS_HURMODE_RELOCK2		0x14
	#define MUS_MODE_SLOW_1		0x15
	#define MUS_MODE_FRENZY_1		0x16
#define MUS_HURMODE_RELOCK3_TIMEOUT		0x17

	#define SND_EXTRABALL	0x18
	#define SND_100MIL		0x19

	#define SND_TRIPLE_JP	0x1A
	#define SND_DOUBLE_JP	0x1B
	#define SND_JP			0x1C
	#define SND_BF1			0x1D

	#define SND_BF_LAUGH	0x1E
#define SND_WWATER		0x1F
	#define SND_GAMEOVER	0x30

	#define MUS_RAFT1_2		0x31
	#define MUS_RAFT2_2		0x32
	#define MUS_RAFT3_2		0x33
	#define MUS_RAFT4_2		0x34
	#define MUS_RAFT5_2		0x35
	#define MUS_RAFT6_2		0x36
	#define MUS_RAFT7_2		0x37
	#define MUS_RAFT8_2		0x38
	#define MUS_RAFT9_2		0x39

#define MUS_PLUNGER_2 	0x3A
	#define MUS_MANOVERB_2 	0x3B  like 0x11 
	#define MUS_HURRY_MODE3 	0x3C  #much faster	#wet willy 1
	#define MUS_HURRY_MODE4 	0x3D  #much faster	#wet willy 2
	#define MUS_HURRY_MODE5 	0x3E  #much faster
	#define MUS_HURRY_MODE6 	0x3F  #much faster
	#define MUS_HURRY_MODE7 	0x40  #much faster
	#define MUS_HURRY_MODE8 	0x41  #much faster
	#define MUS_HURRY_MODE9 	0x42  #much faster

#define MUS_RELOCKBALL	0x43		#hurry up relaunch ? or wet willy last
#define MUS_RELOCKBALL2	0x44		#hurry up relaunch
#define MUS_GAMEOVERSTARTLOOP	0x44 	#bonus

	#define MUS_MULTIBALL_2		0x45

#define MUS_RELOCKBALL3		0x46
	#define MUS_FRENZY_2		0x47
#define MUS_FRENZY_3		0x48
#define MUS_FRENZY_4		0x49

#define MUS_HURRY_MODE10 	0x4A  #much faster


	#define SND_ALARM		0x80
	#define SND_WEIRD1		0x83
	#define SND_ROCK_WATER	0x84
#define SND_HIGH		0x85


	#define SND_ENTERWP1		0x86

#define SND_UNKNOWN		0x87
#define SND_UNKNOWN2	0x88
#define SND_UNKNOWN3	0x89

#define SND_PING		0x8A
#define SND_PING3LOOP		0x8B
#define SND_PINGHIGH		0x8C
#define SND_PINGHIGH2		0x8D
	#define SND_PINGBASS1		0x8E
	#define SND_PINGBASS2		0x8F
	#define SND_PINGBASS3		0x90
	#define SND_PINGBASS4		0x91
	#define SND_PINGBASSSHORTLOOP	0x92


	#define SND_SPLASH_1	0x93
	#define SND_SPLASH_2	0x94
	#define SND_SPLASH_3	0x95
	#define SND_SPLASH_4	0x96
	#define SND_SPLASH_5	0x97
	#define SND_LOCK_1		0x98
	#define SND_LOCK_2		0x99
	#define SND_LOCK_3		0x9A
#define SND_LOCK_4		0x9B
	#define SND_SPLASH_6	0x9C

	#define SND_BGARDEN_1	0x9D
	#define SND_BGARDEN_2	0x9E
	#define SND_BGARDEN_3	0x9F
	#define SND_BGARDEN_4	0xA0
	#define SND_BGARDEN_5	0xA1
	#define SND_BGARDEN_6	0xA2
	#define SND_BGARDEN_7	0xA3
	#define SND_BGARDEN_8	0xA4
	#define SND_BGARDEN_9	0xA5
	#define SND_BGARDEN_10	0xA6
	#define SND_BGARDEN_11	0xA7
	#define SND_BGARDEN_12	0xA8
	#define SND_BGARDEN_13	0xA9
	#define SND_BGARDEN_14	0xAA
	#define SND_BGARDEN_15	0xAB
	#define SND_BGARDEN_16	0xAC
	#define SND_BGARDEN_17	0xAD
	#define SND_BGARDEN_18	0xAE

	#define SND_BAD_1	0xAF
	#define SND_BAD_2	0xB0
#define SND_BAD_3	0xB1

	#define SND_OK_1	0xB2
	#define SND_OK_2	0xB3
	#define SND_OK_3	0xB4
	#define SND_OK_4	0xB5
#define SND_BF_LAUGH_1	0xB6
	#define SND_SPLASH	0xB7
#define SND_BFMATCH	0xB8

	#define SND_OK_5	0xB9

	#define SND_BGARDEN_COIN_1	0xBA
	#define SND_BGARDEN_COIN_2	0xBB
	#define SND_BGARDEN_COIN_3	0xBC
	#define SND_BGARDEN_COIN_4	0xBD
	#define SND_BGARDEN_COIN_5	0xBE
	#define SND_BGARDEN_COIN_6	0xBF
	#define SND_BGARDEN_COIN_7	0xC0
	#define SND_BGARDEN_COIN_8	0xC1
	#define SND_BGARDEN_COIN_9	0xC2
	#define SND_BGARDEN_COIN_10	0xC3
	#define SND_BGARDEN_COIN_11	0xC4
	#define SND_BGARDEN_COIN_12	0xC5

	#define SND_OK_6	0xC6

#define SND_WEIRD1	0xC7
#define SND_WEIRD2	0xC8
#define SND_WEIRD3	0xC9
#define SND_WEIRDSHORTLOOP	0xCA
#define SND_WEIRD4	0xCB
#define SND_WEIRDHIGH1	0xCC
#define SND_WEIRDBASSLOOP	0xCD
#define SND_WEIRD5	0xCE
#define SND_WEIRD6	0xCF

	#define SND_WEIRD100MIL	0xD0

#define SND_BONG	0xD1
#define SND_SHORT	0xD2
#define SND_SHORT2	0xD3

#define SND_WWATER_2		0xD4

	#define SND_BONUSTING1	0xD5
	#define SND_BONUSTING2	0xD6
	#define SND_BONUSTING3	0xD7
	#define SND_BONUSTING4	0xD8

#define SND_SHORTLOOP	0xD9
#define SND_BENG	0xDA
#define SND_DENGECHO	0xDB
	#define SND_SPLASH_7	0xDC

#define SND_EXTRABALL_2	0xDD

	#define SND_EBSOUND	0xDE
#define SND_BENG	0xDF
#define SND_WIZZ	0xE0

#define SND_WATRR	0xE1
	#define SND_OK_7	0xE2
#define SND_OK_8	0xE3
#define SND_BENG	0xE5
	#define SND_WHISTLE	0xE6
	#define SND_OKNICE	0xE7
#define SND_OKNICE_2	0xE8
	#define SND_CAMERASOUND	0xE9
#define SND_OK_9	0xEA

#define SND_BOULDERS1	0xEB
#define SND_BOULDERS1	0xEC
#define SND_BOULDERS1	0xED

 rom 2

	#define SND_IAMWETWILLY		0x0101
	#define SND_SCREAM1		0x0102
#define SND_SCREAM2		0x0103
	#define SND_BOWLINGBALL		0x0104
	#define SND_SCREAM3		0x0105
	#define SND_SCREAM4		0x0106
	#define SND_SCREAM5		0x0107
	#define SND_SCREAM6		0x0108
	#define SND_DOG		0x0109
#define SND_HOWDY		0x010A
	#define SND_INSANITYFALLS	0x010B
	#define SND_LEFTLEFT		0x010C
	#define SND_RIGHTRIGHT		0x010D
	#define SND_RIDEWPOOL		0x010E

	#define SND_MANOVERB		0x010F
	#define SND_GRABONTOHIM		0x0110
	#define SND_GETHOLDOFHIM	0x0111

	#define SND_5TIMESFUN		0x0111

	#define SND_NICEPEDDLPART	0x0114
	#define SND_GOODGOINGPART	0x0115

	#define SND_SPIRITRIVER		0x0116

#define SND_JP2				0x0117
#define SND_DOUBLEJP2		0x0118
#define SND_TRIPLEJP2		0x0119

	#define SND_WELCOMEWETWILLYS	0x011A

	#define SND_CLASS2RIVER		0x011B
	#define SND_CLASS3RIVER		0x011C
	#define SND_CLASS4RIVER		0x011D
	#define SND_CLASS5RIVER		0x011E
	#define SND_CLASS6RIVER		0x011F


	#define SND_BOULDERGARDEN	0x0120
	#define SND_SPINECHILLER	0x0121
#define SND_YWNOWAYOUT		0x0122
	#define SND_YWDISDROP		0x0123
#define SND_YWBOOMBEND		0x0124
#define SND_YWBIGFOOTBLUFF	0x0125
#define SND_BOULDERGARDEN2	0x0126
#define SND_SPINECHILLER2	0x0127
	#define SND_NOWAYOUT		0x0128
	#define SND_DISDROP			0x0129
	#define SND_BOOMBEND		0x012A
	#define SND_BIGFOOTBLUFF	0x012B

	#define SND_DANGLOSTANOTHER		0x012C
	#define SND_GETEXTRABALL		0x012D
#define SND_EXTRABALL		0x012E

#define SND_100MIL		0x012F
	#define SND_YAWIENER		0x0130
	#define SND_WWATER		0x0131
#define SND_LAUGHLOCK		0x0132
	#define SND_YOUFSECRPASS	0x0113
#define SND_BGFT1		0x0134
#define SND_BGFT2		0x0135
#define SND_BGFT3		0x0136
#define SND_BGFT4		0x0137
#define SND_BGFT5		0x0138

	#define SND_ANYBODYLIGHT		0x0139
	#define SND_GOTFLASHLIGHT		0x013A
	#define SND_WHICHWAYGO		0x013B
	#define SND_ITSGOLDRUSH		0x013C
#define SND_YIEHAA		0x013D
#define SND_LETSGO		0x013E
	#define SND_HOWDYFOLKS		0x013F
	#define SND_HERESMAP		0x0140
	#define SND_THISDOORLOCKED		0x0141
	#define SND_TRYTHISKEY		0x0142

	#define SND_HEYFLASHLIGHT	0x0143
	#define SND_HEYMAP	0x0144
	#define SND_HEYKEY	0x0145
	#define SND_HEYCAMERA	0x0146

	#define SND_FEMALE_YEAH1	0x0147
	#define SND_FEMALE_YEAH2	0x0148
	#define SND_FEMALE_YEAH3	0x0149
	#define SND_FEMALE_YEAH4	0x014A
	#define SND_FEMALE_YEAH5	0x014B
	#define SND_FEMALE_YEAH6	0x014C

	#define SND_BGFT_GR1	0x014D
	#define SND_BGFT_GR2	0x014E


	#define SND_ARETHEREYET	0x014F
	#define SND_DOG1	0x0150
#define SND_WWYAHOO	0x0152
#define SND_WWYAHOO2	0x0153
#define SND_WWYAHOO3	0x0154
#define SND_WWYAHOO4	0x0155
	#define SND_WWYAHOO5	0x0156
	#define SND_WWHELP	0x0158

#define SND_HOWDYWET	0x0159

	#define SND_YIHA	0x015B
	#define SND_YOW	0x015C
	#define SND_SCREAM	0x015D
	#define SND_SCREAM2	0x015E
	#define SND_YOW2	0x015F
	#define SND_YIHA2	0x0160
	#define SND_YAW	0x0161
	#define SND_YIAW	0x0162
	#define SND_DOG2	0x0163
	#define SND_MAW	0x0164
	#define SND_YAW2	0x0165


	#define SND_ITSABOULDERBASH	0x0166

	#define SND_BGFT_LAUGH1	0x0167
	#define SND_BGFT_LAUGH2	0x0168
	#define SND_BGFT_LAUGH3	0x0169
	#define SND_BGFT_LAUGH4	0x016A
	#define SND_BGFT_LAUGH5	0x016B
	#define SND_BGFT_LAUGH6	0x016C
	#define SND_BGFT_LAUGH7	0x016D
	#define SND_BGFT_LAUGH8	0x016E
	#define SND_BGFT_LAUGH9	0x016F
	#define SND_BGFT_LAUGH10	0x0170
	#define SND_BGFT_LAUGH11	0x0171
	#define SND_BGFT_LAUGH12	0x0172

	#define SND_WWGOTHIM	0x0173
	#define SND_WWGREATSHOT	0x0174
	#define SND_HEADFORBIGFOOTBLUFF	0x0175
	#define SND_HEADFORBLINKENLIGHT	0x0176
	#define SND_WWHOWDYFOLKS	0x0177
#define SND_HOWDYPARTNER	0x0178
	#define SND_NICEMOVE	0x0179

	#define SND_OOHMULTIMILL	0x017A
	#define SND_WAYTOGO			0x017B
	#define SND_OOH				0x017C
	#define SND_MULTIMILL		0x017D


	#define SND_COW	0x017E
	#define SND_HEYAWCOW	0x017F
*/

#endif /* _MACH_SOUND_H */


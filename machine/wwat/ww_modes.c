
/* CALLSET_SECTION (ww_modes, __machine4__) */

#include <freewpc.h>

//local variables
__local__ U8 ww_modes_completed;

CALLSET_ENTRY (ww_modes, start_player) 	{
	ww_modes_completed = 0x0;  // clear
}//end of function

__boolean get_ww_mode (U8 mode_flag) {
		if (ww_modes_completed & mode_flag) return TRUE;
		else return FALSE;
}//end of function

void set_ww_mode (U8 mode_flag) {
		ww_modes_completed |= mode_flag;  // flag or unflag the bit
}//end of function



/* James stuff below */

/*
//clear out flags for claw - but not others
void reset_dm_mode (void) {
		dm_modes_completed &= 0xE0;
}//end of function

void set_dm_mode2 (U8 mode_flag) {
		dm_modes_completed2 |= mode_flag;  // flag or unflag the bit
}//end of function

__boolean get_dm_mode2 (U8 mode_flag) {
		if (dm_modes_completed2 & mode_flag) return TRUE;
		else return FALSE;
}//end of function

*/






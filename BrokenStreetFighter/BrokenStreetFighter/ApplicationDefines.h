// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// ApplicationDefines.h

#ifndef APPLICATIONDEFINES_H
#define APPLICATIONDEFINES_H

#include "InputHandler.h"

// INCLUDES
struct ControlLayout
{
	Key* Up;
	Key* Left;
	Key* Right;
	Key* Punch;
	Key* Block;
};


// DEFINES
#define	PLAYER_COUNT	2
#define	CONTROL_DELAY	15



// ENUMS
enum e_GameState {
	e_START = 0, e_INGAME, e_END
};


// ETCS

#endif
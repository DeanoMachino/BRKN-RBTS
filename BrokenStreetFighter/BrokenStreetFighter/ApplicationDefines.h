// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// ApplicationDefines.h

#ifndef APPLICATIONDEFINES_H
#define APPLICATIONDEFINES_H

#include "InputHandler.h"

// INCLUDES
struct ControlLayout {
	Key* Up;
	Key* Left;
	Key* Right;
	Key* Weak;
	Key* Heavy;
};


// DEFINES
#define	PLAYER_COUNT	2
#define CONTROL_LAYOUTS	1
#define	CONTROL_DELAY	15
#define GRAVITY			0
#define FRICTION		1
#define AIR_RESISTANCE	2
#define MOVE_SPEED		0
#define JUMP_SPEED		20


// ENUMS
enum e_GameState {
	e_START = 0, e_INGAME, e_END
};

enum e_Direction {
	e_LEFT = 0, e_RIGHT
};

enum e_WinState {
	e_PLAYER_1_WIN = 0, e_PLAYER_2_WIN, e_ONGOING
};

enum e_AttackType {
	e_WEAK = 0, e_HEAVY
};

// ETCS

#endif
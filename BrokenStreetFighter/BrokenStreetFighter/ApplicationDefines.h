// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// ApplicationDefines.h

#ifndef APPLICATIONDEFINES_H
#define APPLICATIONDEFINES_H

// INCLUDES
#include "InputHandler.h"


// STRUCTS
struct ControlLayout {
	Key* Up;
	Key* Left;
	Key* Right;
	Key* Weak;
	Key* Heavy;
};

struct AABB {
	sf::Vector2f max;
	sf::Vector2f min;
};


// DEFINES
#define	PLAYER_COUNT		2
#define CONTROL_LAYOUTS		2
#define	CONTROL_DELAY		15
#define GRAVITY				2
#define FRICTION			1
#define AIR_RESISTANCE		0.1
#define MOVE_SPEED			7.5
#define JUMP_SPEED			20

#define RESOLUTION_X		1400
#define RESOLUTION_Y		768
#define STAGE_MIN			10
#define STAGE_MAX			RESOLUTION_X - 10
#define FLOOR_Y				RESOLUTION_Y - 100


// ENUMS
enum e_GameState {
	e_START = 0, e_INGAME, e_END
};

enum e_Direction {
	e_LEFT = 0, e_RIGHT
};

enum e_WinState {
	e_PLAYER_0_WIN = 0, e_PLAYER_1_WIN, e_ONGOING
};

enum e_AttackType {
	e_WEAK = 0, e_HEAVY, e_NO_ATTACK
};

// ETCS

#endif
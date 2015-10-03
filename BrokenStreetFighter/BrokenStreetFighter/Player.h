// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "GameObj.h"
#include "ApplicationDefines.h"

class Player : public GameObj {
public:
	Player();
	~Player();

	bool Initialise(InputHandler* hInput);
	void Update(InputHandler* hInput);
	void ChangeControls(InputHandler* hInput);

protected:


private:
	void HandleInput(InputHandler* hInput);
	void RepositionPlayer();

	void Move(e_Direction d);
	void Jump();
	void Attack(e_AttackType at);

	ControlLayout* controls[CONTROL_LAYOUTS];
	ControlLayout* currentControls;
	int layout;

	sf::Vector2f velocity;

	bool inAir;
	bool attacking;
};

#endif
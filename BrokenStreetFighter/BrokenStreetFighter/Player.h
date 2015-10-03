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

	bool Initialise(InputHandler* hInput, int i, sf::Vector2f p);
	
	void Update(InputHandler* hInput);
	void ChangeControls(InputHandler* hInput);
	void Knockback(e_Direction d, e_AttackType at);
	void DepleteHealth(e_AttackType at);

	AABB boundingBox;
	e_AttackType attacking;
	//bool justAttacked;
	float attackDelay;
	bool dead;

protected:


private:
	void InitialiseControls(InputHandler* hInput, int i);

	void HandleInput(InputHandler* hInput);
	void RepositionPlayer();

	void UpdateAABB();

	void Move(e_Direction d);
	void Jump();
	void Attack(e_AttackType at);

	ControlLayout controls[CONTROL_LAYOUTS];
	ControlLayout* currentControls;
	int layout;

	sf::Vector2f velocity;

	bool inAir;
	bool knockback;
	int health;
};

#endif
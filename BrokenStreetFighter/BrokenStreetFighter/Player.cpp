// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Player.cpp

#include "Player.h"

Player::Player() {
	inAir = false;
	attacking = false;
}

Player::~Player() {
}

bool Player::Initialise(InputHandler* hInput) {
	layout = 0;
	return true;
}

void Player::Update(InputHandler* hInput) {
	HandleInput(hInput);
	RepositionPlayer();
}

void Player::ChangeControls(InputHandler* hInput) {
	++layout;
	if(layout > (CONTROL_LAYOUTS - 1)) {
		layout = 0;
	}
	
	currentControls = controls[layout];
}


void Player::HandleInput(InputHandler* hInput) {
	// JUMP
	if(currentControls->Up->pressed && currentControls->Up->changed) {
		Jump();
	}
	// MOVE LEFT
	if(currentControls->Left->pressed) {
		Move(e_LEFT);
	}
	// MOVE RIGHT
	if(currentControls->Right->pressed) {
		Move(e_RIGHT);
	}
	// WEAK ATTACK
	if(currentControls->Weak->pressed && currentControls->Weak->changed) {
		Attack(e_WEAK);
	}
	// HEAVY ATTACK
	if(currentControls->Heavy->pressed && currentControls->Heavy->changed) {
		Attack(e_HEAVY);
	}
}

void Player::RepositionPlayer() {
	// POSITION X
	Position.x += velocity.x;
	if(inAir) {			// If currently in air
		if(velocity.x > 0) {	// If moving right
			velocity.x -= AIR_RESISTANCE;
			if(velocity.x < 0) {	// If velocity has flipped
				velocity.x = 0;
			}
		} else {				// If moving left
			velocity.x += AIR_RESISTANCE;
			if(velocity.x > 0) {	// If velocity has flipped
				velocity.x = 0;
			}
		}
	} else {
		if(velocity.x > 0) {	// If moving right
			velocity.x -= FRICTION;
			if(velocity.x < 0) {	// If velocity has flipped
				velocity.x = 0;
			}
		} else {				// If moving left
			velocity.x += FRICTION;
			if(velocity.x > 0) {	// If velocity has flipped
				velocity.x = 0;
			}
		}
	}

	// POSITION Y
	Position.y += velocity.y;
	velocity.y += GRAVITY;
}

void Player::Move(e_Direction d) {
	if(!inAir) {
		if(d == e_LEFT) {
			velocity.x = -MOVE_SPEED;
		} else {
			velocity.x = MOVE_SPEED;
		}
	}
}

void Player::Jump() {
	if(!inAir) {
		velocity.y = JUMP_SPEED;
	}
}

void Player::Attack(e_AttackType at) {
	if(!attacking) {
		if(at == e_WEAK) {
			// weak attack stuff
		} else {
			// heavy attack stuff
		}
	}
}
// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Player.cpp

#include "Player.h"

Player::Player() {
}

Player::~Player() {
}

bool Player::Initialise(InputHandler* hInput, int i, sf::Vector2f p) {
	Position = p;
	Width = 52;
	Height = 52;
	inAir = false;
	attacking = false;
	layout = 0;

	InitialiseControls(hInput, i);
	return true;
}

void Player::InitialiseControls(InputHandler* hInput, int i) {
	switch(i) {
		case 0:
			controls[0].Left = hInput->getKey(e_KEYBOARD, sf::Keyboard::A);
			controls[0].Right = hInput->getKey(e_KEYBOARD, sf::Keyboard::D);
			controls[0].Up = hInput->getKey(e_KEYBOARD, sf::Keyboard::W);
			controls[0].Weak = hInput->getKey(e_KEYBOARD, sf::Keyboard::E);
			controls[0].Heavy = hInput->getKey(e_KEYBOARD, sf::Keyboard::Q);

			controls[1].Left = hInput->getKey(e_KEYBOARD, sf::Keyboard::D);
			controls[1].Right = hInput->getKey(e_KEYBOARD, sf::Keyboard::A);
			controls[1].Up = hInput->getKey(e_KEYBOARD, sf::Keyboard::S);
			controls[1].Weak = hInput->getKey(e_KEYBOARD, sf::Keyboard::Q);
			controls[1].Heavy = hInput->getKey(e_KEYBOARD, sf::Keyboard::E);

			currentControls = &controls[0];
			break;
		case 1:
			controls[0].Left = hInput->getKey(e_KEYBOARD, sf::Keyboard::Left);
			controls[0].Right = hInput->getKey(e_KEYBOARD, sf::Keyboard::Right);
			controls[0].Up = hInput->getKey(e_KEYBOARD, sf::Keyboard::Up);
			controls[0].Weak = hInput->getKey(e_KEYBOARD, sf::Keyboard::RShift);
			controls[0].Heavy = hInput->getKey(e_KEYBOARD, sf::Keyboard::RControl);

			controls[1].Left = hInput->getKey(e_KEYBOARD, sf::Keyboard::Right);
			controls[1].Right = hInput->getKey(e_KEYBOARD, sf::Keyboard::Left);
			controls[1].Up = hInput->getKey(e_KEYBOARD, sf::Keyboard::Down);
			controls[1].Weak = hInput->getKey(e_KEYBOARD, sf::Keyboard::RControl);
			controls[1].Heavy = hInput->getKey(e_KEYBOARD, sf::Keyboard::RShift);

			currentControls = &controls[0];
			break;
	}
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
	
	currentControls = &controls[layout];
}


void Player::HandleInput(InputHandler* hInput) {
	if(hInput->isKeyPressed(e_KEYBOARD, sf::Keyboard::Return)) {
		ChangeControls(hInput);
	}
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
	if(Position.y >= FLOOR_Y) {
		Position.y = FLOOR_Y;
		inAir = false;
	}

	// Set sprite position
	animatedSprite.setPosition(Position.x - (Width / 2), Position.y);
}

void Player::Move(e_Direction d) {
	// Move player
	if(!inAir) {
		if(d == e_LEFT) {
			velocity.x = -MOVE_SPEED;
		} else {
			velocity.x = MOVE_SPEED;
		}
	}
}

void Player::Jump() {
	// Jump
	if(!inAir) {
		inAir = true;
		velocity.y = -JUMP_SPEED;
	}
}

void Player::Attack(e_AttackType at) {
	// Attack
	if(!attacking) {
		if(at == e_WEAK) {
			// weak attack stuff
		} else {
			// heavy attack stuff
		}
		attacking = true;
	}
}
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
	Width = 52*5;
	Height = 52*5;
	velocity = sf::Vector2f(0.0f, 0.0f);

	health = 100;
	dead = false;
	inAir = false;
	isPunchingW = false;
	isPunchingH = false;
	
	isAttacking = false;
	attackType = e_NO_ATTACK;
	AttackTimer.restart();
	knockback = false;

	layout = 0;
	time = 0;
	InitialiseControls(hInput, i);
	Update(hInput);
	return true;
}

void Player::InitialiseControls(InputHandler* hInput, int i) {
	switch(i) {
		case 0:
			controls[0].Left = hInput->getKey(e_KEYBOARD, sf::Keyboard::A);
			controls[0].Right = hInput->getKey(e_KEYBOARD, sf::Keyboard::D);
			controls[0].Up = hInput->getKey(e_KEYBOARD, sf::Keyboard::W);
			controls[0].Weak = hInput->getKey(e_KEYBOARD, sf::Keyboard::LShift);
			controls[0].Heavy = hInput->getKey(e_KEYBOARD, sf::Keyboard::LControl);

			controls[1].Left = hInput->getKey(e_KEYBOARD, sf::Keyboard::D);
			controls[1].Right = hInput->getKey(e_KEYBOARD, sf::Keyboard::A);
			controls[1].Up = hInput->getKey(e_KEYBOARD, sf::Keyboard::S);
			controls[1].Weak = hInput->getKey(e_KEYBOARD, sf::Keyboard::LControl);
			controls[1].Heavy = hInput->getKey(e_KEYBOARD, sf::Keyboard::LShift);

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
	if (animatedSprite.m_currentFrame >= 5 && isPunchingH == true){
		isPunchingH = false;
	}
	if (animatedSprite.m_currentFrame >= 4 && isPunchingW == true){
		isPunchingW = false;
	}
	
	if (flipped == true && needFlipped == true){
		PlayerTexFlipped();
	}
	else if (flipped == false && needFlipped == true){
		PlayerTex();
	}

	if(AttackTimer.getElapsedTime() >= sf::seconds(ATTACK_DELAY)) {
		attackType = e_NO_ATTACK;
	}

	HandleInput(hInput);
	RepositionPlayer();
	animatedSprite.play(*currentAnimation);
}

void Player::ChangeControls(InputHandler* hInput) {
	++layout;
	if(layout > (CONTROL_LAYOUTS - 1)) {
		layout = 0;
	}

	currentControls = &controls[layout];
}

void Player::Knockback(e_Direction d, e_AttackType at) {
	sf::Vector2f strength;
	if(at == e_WEAK) {
		strength = sf::Vector2f(KNOCKBACK_WEAK_X, KNOCKBACK_WEAK_Y);
	} else {
		strength = sf::Vector2f(KNOCKBACK_HEAVY_X, KNOCKBACK_HEAVY_Y);
	}

	if(d == e_LEFT) {
		strength.x = -strength.x;
	}

	velocity = strength;
	knockback = true;
}

void Player::DepleteHealth(e_AttackType at) {
	switch(at) {
		case e_WEAK:
			health -= 5;
			break;
		case e_HEAVY:
			health -= 10;
			break;
	}
	if(health <= 0) {
		dead = true;
	}
}


void Player::HandleInput(InputHandler* hInput) {
	if(AttackTimer.getElapsedTime() >= sf::seconds(ATTACK_DELAY)) {
		isAttacking = false;
	}
	if(hInput->isKeyPressed(e_KEYBOARD, sf::Keyboard::Return)) {
		ChangeControls(hInput);
	}
	if(!knockback) {
		// JUMP
		if(currentControls->Up->pressed && currentControls->Up->changed) {
			Jump();
		}
		// HEAVY ATTACK
		if(currentControls->Heavy->pressed && currentControls->Heavy->changed) {
			Attack(e_HEAVY);
			currentAnimation = &hardPunchAni;
			isPunchingH = true;
		} else
		// WEAK ATTACK
		if(currentControls->Weak->pressed && currentControls->Weak->changed) {
			Attack(e_WEAK);
			currentAnimation = &lightPunchAni;
			isPunchingW = true;
		} else
		// MOVE LEFT
		if(currentControls->Left->pressed) {
			Move(e_LEFT);
			if (flipped == true && (isPunchingW == false || isPunchingH == false)){
				currentAnimation = &walkFowardAni;
			}
			else currentAnimation = &walkBackwardsAni;
		}else
		// MOVE RIGHT
		if(currentControls->Right->pressed) {
			Move(e_RIGHT);
			if (flipped == true && (isPunchingW == false || isPunchingH == false)){
				currentAnimation = &walkBackwardsAni;
			}
			else currentAnimation = &walkFowardAni;
		}else if (isPunchingW == false && isPunchingH == false){
			currentAnimation = &idleAni;
		}
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

	if(Position.x - (Width / 2) < STAGE_MIN) {
		Position.x = STAGE_MIN + (Width / 2);
		velocity.x = 0;
	}if(Position.x + (Width / 2) > STAGE_MAX) {
		Position.x = STAGE_MAX - (Width / 2);
		velocity.x = 0;
	}

	// POSITION Y
	Position.y += velocity.y;
	velocity.y += GRAVITY;
	
	if(Position.y >= FLOOR_Y) {
		Position.y = FLOOR_Y;
		inAir = false;
		knockback = false;
	} else {
		inAir = true;
	}

	// Set sprite position
	UpdateAABB();
	animatedSprite.setPosition(boundingBox.min.x, boundingBox.min.y);
}

void Player::UpdateAABB() {
	boundingBox.max.x = Position.x + (Width / 2);
	boundingBox.max.y = Position.y;
	
	boundingBox.min.x = Position.x - (Width / 2);
	boundingBox.min.y = Position.y - Height;
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
	if(AttackTimer.getElapsedTime() >= sf::seconds(ATTACK_DELAY) && !isAttacking) {
		isAttacking = true;
		AttackTimer.restart();
		if(at == e_WEAK) {
			attackType = e_WEAK;
			// weak attack stuff
		} else {
			attackType = e_HEAVY;
			// heavy attack stuff
		}
	}
}
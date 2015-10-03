// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ==========================
// GameObj.h

#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <vector>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "AnimatedSprite.hpp"
#include <iostream>

class GameObj {
public:
	GameObj();
	virtual ~GameObj();

	
	sf::Vector2f Position;
	sf::Sprite player;
	AnimatedSprite animatedSprite;

	float Width;
	float Height;
	bool visible;
	bool collide;
	bool animated;

	void SetTexture();
	void SetUpSprite();
	void SetAnimations();

protected:
	sf::Texture texture;
	Animation walkFowardA;
	Animation walkBackwardsA;
	Animation IdleA;

	Animation* currentAnimation;

};

#endif
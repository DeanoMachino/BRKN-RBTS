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
	bool flipped;
	bool needFlipped;

	void SetTexture();

	void PlayerTexFlipped();
	void PlayerTex();
	void SetUpSprite();
	void SetAnimations(sf::Texture* texture);
	void SetupStaticSprite(sf::Vector2f Position);
	sf::Sprite background;
	sf::Sprite player1_healthbarB;
	sf::Sprite player2_healthbarB;



protected:
	sf::Texture playertexture;
	sf::Texture playertextureFlipped;
	sf::Texture CurrentPlayerTex;
	sf::Texture backgroundtexture;
	sf::Texture player1_healthbarBTex;
	sf::Texture player2_healthbarBTex;


	Animation* currentAnimation;


	Animation walkFowardAni;
	Animation walkBackwardsAni;
	Animation idleAni;
	Animation hardPunchAni;
	Animation lightPunchAni;
	Animation deathAni;

	

	bool scaleSet;
	bool scaleSet2;
};

#endif
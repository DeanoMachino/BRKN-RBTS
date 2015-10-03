// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// GameObj.cpp

#include "GameObj.h"

GameObj::GameObj(){
	Position.x = (512);
	Position.y = (384);
	SetTexture();
}

GameObj::~GameObj(){

}

void GameObj::SetTexture(){
	//sf::Texture texture;
	if (!texture.loadFromFile("bin/AGDSjam_spritesheet.png")){
		std::cout << "Failed to Load Player Spritesheet" << std::endl;
	}
	//player.setTexture(texture);
	SetAnimations();
}

void GameObj::SetUpSprite(){
	//AnimatedSprite animatedSprite();
	animatedSprite.setFrameTime(sf::seconds(0.1));
	animatedSprite.play();
	animatedSprite.setLooped(true);
	animatedSprite.setPosition(Position);
}

void GameObj::SetAnimations(){
	walkFowardA.setSpriteSheet(texture);
	walkFowardA.addFrame(sf::IntRect(0, 52, 52, 52));	//52/52
	walkFowardA.addFrame(sf::IntRect(52, 52, 52, 52));	//52/52
	walkFowardA.addFrame(sf::IntRect(104, 52, 52, 52));	//52/52
	walkFowardA.addFrame(sf::IntRect(156, 52, 52, 52));	//52/52



	currentAnimation = &walkFowardA;
	animatedSprite.setAnimation(*currentAnimation);
}
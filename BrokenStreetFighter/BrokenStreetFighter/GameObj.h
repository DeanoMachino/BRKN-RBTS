#pragma once
// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ==========================
//GameObj.h

#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <vector>
#include <SFML\Window.hpp>
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>

class GameObj {
public:
	GameObj();
	~GameObj();

	sf::Texture texture_;

	void SetTexture();


};



#endif
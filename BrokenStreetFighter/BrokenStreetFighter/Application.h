// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Application.h

#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationDefines.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "GameObj.h"

class Application {
public:
	Application();
	~Application();


	void Run();

protected:


private:
	e_GameState currentState;
	void Initialise();
	sf::Clock frameClock;
	sf::Time frameTime;
	void ManageEvents(sf::RenderWindow* window);
	void Process(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);

	void DetectCollisions();

	InputHandler hInput;
	GameObj player[2];				// CHANGE TO TYPE PLAYER CLASS
};

#endif
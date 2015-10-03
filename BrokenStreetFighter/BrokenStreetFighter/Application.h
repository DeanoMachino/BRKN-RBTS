// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Application.h

#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationDefines.h"

class Application {
public:
	Application();
	~Application();

	void Run();

protected:


private:
	e_GameState currentState;
	void Initialise();
	void ManageEvents();
	void Process(e_GameState currentState);
	void Render(e_GameState currentState);

	sf::ContextSettings settings;
	sf::RenderWindow window;

	InputHandler hInput;

};

#endif
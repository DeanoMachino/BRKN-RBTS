// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Application.h

#include "InputHandler.h"
#include "GameObj.h"
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
	e_GameState CurrentState;
	void Initialise();
	void GetInput();
	void Process(e_GameState CurrentState);
	void Render(e_GameState CurrentState);
	GameObj Player;
	InputHandler ih;

};

#endif
// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Application.h

#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
public:
	Application();
	~Application();

	void Run();

protected:


private:
	void Initialise();
	void GetInput();
	void Process();
	void Render();

};

#endif
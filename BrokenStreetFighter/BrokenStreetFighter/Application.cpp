// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Application.cpp

#include "Application.h"

Application::Application() {
	Initialise();
}

Application::~Application() {
}

void Application::Run() {
	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

	// Game loop
	while(window.isOpen()) {
		ManageEvents(&window);		// Get events (input, etc.)
		Process(&window);			// Handle game logic, main mechanics
		Render(&window);			// Display graphics
	}
}

void Application::Initialise() {
	currentState = e_START;
}

void Application::ManageEvents(sf::RenderWindow* window) {
	sf::Event event;
	// Sifts through all events
	while(window->pollEvent(event)) {
		// Check event type
		switch(event.type) {
			case sf::Event::Closed:					// Window closed
				window->close();
				break;
			case sf::Event::KeyPressed:				// Keyboard down
				hInput.KeyPressed(e_KEYBOARD, event.key.code);
				break;
			case sf::Event::KeyReleased:			// Keyboard up
				hInput.KeyReleased(e_KEYBOARD, event.key.code);
				break;
			case sf::Event::MouseButtonPressed:		// Mouse down
				hInput.KeyPressed(e_MOUSE, event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:	// Mouse up
				hInput.KeyReleased(e_MOUSE, event.mouseButton.button);
				break;
			case sf::Event::MouseMoved:				// Mouse moved
				hInput.MouseMoved(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
				break;
			case sf::Event::MouseWheelMoved:		// Mouse wheel scrolled
				hInput.MouseWheelMoved(event.mouseWheel.delta);
				break;
			case sf::Event::MouseEntered:			// Mouse entered window
				hInput.MouseInWindow(true);
				break;
			case sf::Event::MouseLeft:				// Mouse left window
				hInput.MouseInWindow(false);
				break;
		}
	}
}

void Application::Process(sf::RenderWindow* window) {
	switch(currentState) {
		case e_START:
			// RETURN - Start game
			if(hInput.isKeyPressed(e_KEYBOARD, sf::Keyboard::Return)) {
				currentState = e_INGAME;
			}
			// ESCAPE - Close game
			if(hInput.isKeyPressed(e_KEYBOARD, sf::Keyboard::Escape)) {
				window->close();
			}
			break;
		case e_INGAME:
			// Check win state
			// if still in play, continue
			// else change state


			for(int i = 0; i < PLAYER_COUNT; ++i) {
				// PLAYER CONTROLS HERE
				// Pass input handler into method within Player
				// 
			}


			// Collision detection here
			// AABB

			
			// if timer == 0
			// change control schemes (method within player class)
			
			

			break;
		case e_END:
			// ESCAPE - Close game
			if(hInput.isKeyPressed(e_KEYBOARD, sf::Keyboard::Escape)) {
				window->close();
			}

			// RETURN - Start game again
			if(hInput.isKeyPressed(e_KEYBOARD, sf::Keyboard::Return)) {
				currentState = e_START;
			}
			break;
	}
}

void Application::Render(sf::RenderWindow* window) {
	window->clear();

	sf::CircleShape shape(100.f);		//placeholder

	switch(currentState) {
		case e_START:
			// Render background


			// Render foreground
			shape.setFillColor(sf::Color::Green);
			window->draw(shape);

			// Render UI

			break;
		case e_INGAME:
			// Render background
			shape.setFillColor(sf::Color::Blue);
			

			// Render foreground
			window->draw(shape);

			// Render UI

			break;
		case e_END:
			// Render background
			

			// Render foreground
			window->draw(shape);

			// Render UI

			break;
	}

	window->display();
}
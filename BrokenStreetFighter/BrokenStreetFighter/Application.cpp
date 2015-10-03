// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Application.cpp

#include <SFML\Graphics.hpp>
#include "Application.h"

Application::Application() {
}

Application::~Application() {
}

void Application::Run() {
	Initialise();

	// placeholder
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// Game loop
	while(window.isOpen()) {
		switch(currentState) {
			case e_START:
				Process(currentState);
				Render(currentState);
				break;

			case e_INGAME:
				ManageEvents();
				Process(currentState);
				Render(currentState);
				break;

			case e_END:
				ManageEvents();
				Process(currentState);
				Render(currentState);
				break;
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}

void Application::Initialise() {
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(1024, 768), "BrokenStreetFighter");

	currentState = e_START;
}

void Application::ManageEvents() {
	sf::Event event;
	while(window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				hInput.KeyPressed(e_KEYBOARD, event.key.code);
				break;
			case sf::Event::KeyReleased:
				hInput.KeyReleased(e_KEYBOARD, event.key.code);
				break;
			case sf::Event::MouseButtonPressed:
				hInput.KeyPressed(e_MOUSE, event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				hInput.KeyReleased(e_MOUSE, event.mouseButton.button);
				break;
			case sf::Event::MouseMoved:
				hInput.MouseMoved(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
				break;
			case sf::Event::MouseWheelMoved:
				hInput.MouseWheelMoved(event.mouseWheel.delta);
				break;
			case sf::Event::MouseEntered:
				hInput.MouseInWindow(true);
				break;
			case sf::Event::MouseLeft:
				hInput.MouseInWindow(false);
				break;
		}
	}
}

void Application::Process(e_GameState currentState) {
}

void Application::Render(e_GameState currentState) {

}
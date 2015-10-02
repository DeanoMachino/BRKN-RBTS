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
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Broken Street Fighter");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}

void Application::Initialise() {

}

void Application::GetInput() {

}

void Application::Process() {

}

void Application::Render() {

}
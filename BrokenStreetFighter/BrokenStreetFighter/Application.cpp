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
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_X, RESOLUTION_Y), "Lol");
	window.setFramerateLimit(60);

	// Game loop
	while(window.isOpen()) {
		frameTime = frameClock.restart();
		ManageEvents(&window);		// Get events (input, etc.)
		Process(&window);			// Handle game logic, main mechanics
		Render(&window);			// Display graphics
	}
}

void Application::Initialise() {
	currentState = e_START;
	winState = e_ONGOING;

	fullscreen = false;

	Players[0].SetUpSprite();
	Players[0].flipped = false;
	Players[0].Initialise(&hInput, 0, sf::Vector2f(400, 400));
	Players[1].SetUpSprite();
	Players[1].PlayerTexFlipped();
	Players[1].flipped = true;
	Players[1].Initialise(&hInput, 1, sf::Vector2f(800, 400));
}

void Application::ManageEvents(sf::RenderWindow* window) {
	sf::Event event;

	hInput.KeyResetChanged();
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
	
	// Switch between fullscreen and windowed mode
	/*if(hInput.isKeyReleased(e_KEYBOARD, sf::Keyboard::F11)) {
		switch(fullscreen) {
			case false:
				fullscreen = true;
				window->create(sf::VideoMode(RESOLUTION_X, RESOLUTION_Y), "Lol", sf::Style::Fullscreen);
				break;
			case true:
				fullscreen = false;
				window->create(sf::VideoMode(RESOLUTION_X, RESOLUTION_Y), "lol");
		}
	}*/

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
			if(winState != e_ONGOING) {
				currentState = e_END;
			} else {

				LocationComparison();
				for(int i = 0; i < PLAYER_COUNT; ++i) {
					Players[i].Update(&hInput,i);
				}


				// Collision detection here
				// AABB


				// if timer == 0
				// change control schemes (method within player class)

				break;
			}
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
			//shape.setFillColor(sf::Color::Blue);
			// Render foreground
			Players[0].animatedSprite.update(frameTime);
			//window->draw(shape);
			window->draw(Players[0].animatedSprite);		

			Players[1].animatedSprite.update(frameTime);
			window->draw(Players[1].animatedSprite);
			
			for(int i = 0; i < PLAYER_COUNT; ++i) {
				// render player
			}
			
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


void Application::LocationComparison(){
	float x_a = Players[0].Position.x;
	float x_b = Players[1].Position.x;

	if (x_a > x_b && (Players[0].flipped == false && Players[1].flipped == true)){
		Players[0].flipped = true;
		Players[1].flipped = false;
		Players[0].needFlipped = true;
		Players[1].needFlipped = true;
	}
	else if (x_a < x_b && (Players[0].flipped == true && Players[1].flipped == false)){
		Players[0].flipped = false;
		Players[1].flipped = true;
		Players[0].needFlipped = true;
		Players[1].needFlipped = true;
	}
}
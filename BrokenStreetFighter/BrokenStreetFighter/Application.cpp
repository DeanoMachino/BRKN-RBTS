// BrokenStreetFighter
// ADGS Game Jam - October 2015
// Dean, Matt & Sidney
// ===============================
// Application.cpp

#include "Application.h"

Application::Application() {
	Initialise();
	InitialiseText();
}

Application::~Application() {
}

void Application::Run() {
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_X, RESOLUTION_Y), "PLACEHOLDER", sf::Style::Fullscreen);
	//sf::RenderWindow window(sf::VideoMode(RESOLUTION_X, RESOLUTION_Y), "PLACEHOLDER");
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
	gameStarted = false;

	Players[0].SetUpSprite();
	Players[0].flipped = false;
	Players[0].Initialise(&hInput, 0, sf::Vector2f(PLAYER_1_START, FLOOR_Y));
	Players[1].SetUpSprite();
	Players[1].PlayerTexFlipped();
	Players[1].flipped = true;
	Players[1].Initialise(&hInput, 1, sf::Vector2f(PLAYER_2_START, FLOOR_Y));
}

void Application::InitialiseText() {
	if(!MainFont.loadFromFile("bin/Fonts/joystix_monospace.ttf")) {
		// FREAK OUT
	}
	//SetText(&GameLogo, MainFont, "Malfunction", sf::Color::White, sf::Vector2f(0,0), 75);

	// START SCREEN
	GameLogo.setFont(MainFont);
	GameLogo.setColor(sf::Color::White);
	GameLogo.setCharacterSize(75);
	GameLogo.setString("PLACEHOLDER");
	GameLogo.setPosition((RESOLUTION_X / 2) - (GameLogo.getGlobalBounds().width / 2), RESOLUTION_Y / 4);

	StartScreenInfo1.setFont(MainFont);
	StartScreenInfo1.setColor(sf::Color::White);
	StartScreenInfo1.setCharacterSize(25);
	StartScreenInfo1.setString("Press <return> to start.");
	StartScreenInfo1.setPosition((RESOLUTION_X / 2) - (StartScreenInfo1.getGlobalBounds().width / 2), RESOLUTION_Y * 0.8);

	// IN GAME
	CountdownText.setFont(MainFont);
	CountdownText.setColor(sf::Color::White);
	CountdownText.setCharacterSize(100);
	CountdownText.setString("3");
	CountdownText.setPosition((RESOLUTION_X / 2) - (CountdownText.getGlobalBounds().width / 2), RESOLUTION_Y / 2);

	TimerText.setFont(MainFont);
	TimerText.setColor(sf::Color::White);
	TimerText.setCharacterSize(40);
	TimerText.setString("00");
	TimerText.setPosition((RESOLUTION_X / 2) - (TimerText.getGlobalBounds().width / 2), 0);

	Player1Text.setFont(MainFont);
	Player1Text.setColor(sf::Color::White);
	Player1Text.setCharacterSize(25);
	Player1Text.setString("Player 1");
	Player1Text.setPosition(10, 0);

	Player2Text.setFont(MainFont);
	Player2Text.setColor(sf::Color::White);
	Player2Text.setCharacterSize(25);
	Player2Text.setString("Player 2");
	Player2Text.setPosition((RESOLUTION_X - (Player2Text.getGlobalBounds().width)), 0);

	// END SCREEN
	WinnerText.setFont(MainFont);
	WinnerText.setColor(sf::Color::White);
	WinnerText.setCharacterSize(100);
	WinnerText.setString("A winner is you!");
	WinnerText.setPosition((RESOLUTION_X / 2) - (WinnerText.getGlobalBounds().width / 2), RESOLUTION_Y / 2);
}

void Application::SetText(sf::Text* text, sf::Font font, const sf::String string, sf::Color color, sf::Vector2f position, float charSize) {
	text->setFont(font);
	text->setColor(color);
	text->setCharacterSize(charSize);
	text->setString(string);
	text->setPosition(position);
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
	switch(currentState) {
		case e_START:
			// RETURN - Start game
			if(hInput.isKeyPressed(e_KEYBOARD, sf::Keyboard::Return)) {
				currentState = e_INGAME;
				StartTimer.restart();
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
				if(gameStarted == false) {		// If game not started yet
					if(StartTimer.getElapsedTime() >= sf::seconds(START_COUNTDOWN)) {		// If countdown has finished
						gameStarted = true;
						ControlChangeTimer.restart();
					}
				} else {
					// Update player classes
					for(int i = 0; i < PLAYER_COUNT; ++i) {
						Players[i].Update(&hInput);
					}
					
					LocationComparison();
					for(int i = 0; i < PLAYER_COUNT; ++i) {
						Players[i].Update(&hInput);
					}

					// Collision detection
					DetectCollisions();

					if(ControlChangeTimer.getElapsedTime() >= sf::seconds(CONTROL_CHANGE_DELAY)) {
						for(int i = 0; i < PLAYER_COUNT; ++i) {
							Players[i].ChangeControls(&hInput);
							ControlChangeTimer.restart();
						}
					}

					// Check win condition
					if(Players[0].dead) {
						currentState = e_END;
						winState = e_PLAYER_1_WIN;
					} else if(Players[1].dead) {
						currentState = e_END;
						winState = e_PLAYER_0_WIN;
					}
					break;
				}
			}
		case e_END:
			// ESCAPE - Close game
			if(hInput.isKeyPressed(e_KEYBOARD, sf::Keyboard::Escape)) {
				window->close();
			}

			// RETURN - Start game again
			if(hInput.isKeyPressed(e_KEYBOARD, sf::Keyboard::Return)) {
				Initialise();
			}
			break;
	}
}

void Application::Render(sf::RenderWindow* window) {
	window->clear();

	switch(currentState) {
		case e_START:
			// Render background

			// Render foreground
		
			// Render UI
			window->draw(GameLogo);
			window->draw(StartScreenInfo1);

			break;
		case e_INGAME:
			// Render background

			// Render foreground
			for(int i = 0; i < PLAYER_COUNT; ++i) {
				Players[i].animatedSprite.update(frameTime);
				window->draw(Players[i].animatedSprite);
			}
			
			// Render UI
			if(!gameStarted) {
				int count = 4 - StartTimer.getElapsedTime().asSeconds();
				CountdownText.setString(std::to_string(count));
				CountdownText.setPosition((RESOLUTION_X / 2) - (CountdownText.getGlobalBounds().width / 2), RESOLUTION_Y * 0.35);
				if(count != 0) {
					window->draw(CountdownText);
				}
			}

			window->draw(TimerText);
			window->draw(Player1Text);
			window->draw(Player2Text);

			break;
		case e_END:
			// Render background
			
			// Render foreground

			// Render UI
			window->draw(WinnerText);
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

void Application::DetectCollisions() {
	if(GetCollision(Players[0], Players[1])) {		// If collision
		if(Players[0].isAttacking && Players[0].attackType != e_NO_ATTACK) {
			// Damage enemy player
			Players[1].DepleteHealth(Players[0].attackType);
			// Knock player back
			if(Players[0].boundingBox.min.x < Players[1].boundingBox.min.x) {
				Players[1].Knockback(e_RIGHT, Players[1].attackType);
			} else {
				Players[1].Knockback(e_LEFT, Players[1].attackType);
			}
			Players[0].isAttacking = false;
		}
		if(Players[1].isAttacking && Players[1].attackType != e_NO_ATTACK) {
			// Damage enemy player
			Players[0].DepleteHealth(Players[1].attackType);
			// Knock player back
			if(Players[1].boundingBox.min.x < Players[0].boundingBox.min.x) {
				Players[0].Knockback(e_RIGHT, Players[0].attackType);
			} else {
				Players[0].Knockback(e_LEFT, Players[0].attackType);
			}
			Players[1].isAttacking = false;
		}
	}
}

bool Application::GetCollision(Player p1, Player p2) {
	if(p1.boundingBox.min.x > p2.boundingBox.max.x)	return false;
	if(p1.boundingBox.max.x < p2.boundingBox.min.x)	return false;
	if(p1.boundingBox.min.y > p2.boundingBox.max.y)	return false;
	if(p1.boundingBox.max.y < p2.boundingBox.min.y)	return false;

	return true;
}

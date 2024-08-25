#include <iostream>
#include "ZombieArena.h"
#include "Player.h"


int main()
{
    // Game State enum class
	enum class GameState{PAUSED, LEVELING_UP, GAME_OVER, PLAYING};
	// Starting Game State
	GameState gameState = GameState::GAME_OVER;
	// Getting screen resolution for the game window
	sf::Vector2f resolution;
	resolution.x = 1920; //sf::VideoMode::getDesktopMode().width;
	resolution.y = 1080; //sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Surviver", sf::Style::Titlebar);
	// Create SFML view for the main player view
	sf::View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// Game clock for calulating deltaTime
	sf::Clock clock;
	// Time alapsed for Game State
	sf::Time gameTimeTotal;
	// Mouse postion relative to the world
	sf::Vector2f mouseWorldPosition;
	// Mouse relative to the window screen
	sf::Vector2i mouseScreenPosition;
	// Creating a Player intance
	Player player;
	// Creating the arena bounderies
	sf::IntRect arena;
	// Creating Background
	sf::VertexArray background;
	sf::Texture textureBackground;
	textureBackground.loadFromFile("graphics/background_sheet.png");
	

	// Game Loop
	while (window.isOpen())
	{
		/*
		**********************************
		*		  Input Handling
		**********************************
		*/
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				// Pausing the game
				if (event.key.code == sf::Keyboard::Return && gameState == GameState::PLAYING)
				{
					gameState == GameState::PAUSED;
				}
				else if (event.key.code == sf::Keyboard::Return && gameState == GameState::PAUSED)
				{
					gameState == GameState::PLAYING;
					// Restart play clock
					clock.restart();
				}
				else if (event.key.code == sf::Keyboard::Return && gameState == GameState::GAME_OVER)
				{
					gameState == GameState::LEVELING_UP;
					std::cout << "Game Leveling Up\n";
				}
				if (gameState == GameState::PLAYING)
				{
					std::cout << "Game Playing\n";
				}
			}
		}// End of Event polling
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		// Handling Player controls
		if (gameState == GameState::PLAYING)
		{
			// WASD controller
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { player.MoveUp(); }
			else { player.StopUp(); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { player.MoveDown(); }
			else { player.StopDown(); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { player.MoveLeft(); }
			else { player.StopLeft(); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { player.MoveRight(); }
			else { player.StopRight(); }
		}// End of Player Controller
		// Player Leveling
		if (gameState == GameState::LEVELING_UP)
		{
			//Player Level controls
			if (event.key.code == sf::Keyboard::Num1) { gameState == GameState::PLAYING; }
			if (event.key.code == sf::Keyboard::Num2) { gameState == GameState::PLAYING; }
			if (event.key.code == sf::Keyboard::Num3) { gameState == GameState::PLAYING; }
			if (event.key.code == sf::Keyboard::Num4) { gameState == GameState::PLAYING; }
			if (event.key.code == sf::Keyboard::Num5) { gameState == GameState::PLAYING; }
			if (event.key.code == sf::Keyboard::Num6) { gameState == GameState::PLAYING; }
			if (gameState == GameState::PLAYING)
			{
				arena.width     = 500;
				arena.height    = 500;
				arena.left      = 0;
				arena.top       = 0;
				int tileSize    = CreateBackground(background, arena);
				player.Spawn(arena, resolution, tileSize);
				clock.restart();
			}
		}// End of Player leveling
		/*
		**********************************
		*		 Updating Frame
		**********************************
		*/
		if (gameState == GameState::PLAYING)
		{
			// Defining deltaTime
			sf::Time dt = clock.restart();
			gameTimeTotal += dt;
			float deltaTime = dt.asSeconds();
			// Mouse Position
			mouseScreenPosition = sf::Mouse::getPosition(window);
			mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);
			// Update Player
			player.Update(deltaTime, mouseWorldPosition);
			sf::Vector2f playerPosition(player.GetCenter());
			// Center view around the player
			mainView.setCenter(player.GetCenter());
		}// End Updating
		/*
		**********************************
		*		   Drawing
		**********************************
		*/
		if (gameState == GameState::PLAYING)
		{
			window.clear();
			window.setView(mainView);
			window.draw(background, &textureBackground);
			window.draw(player.GetSprite());
		}
		if (gameState == GameState::LEVELING_UP)
		{

		}
		if (gameState == GameState::PAUSED)
		{

		}
		if (gameState == GameState::GAME_OVER)
		{

		}
		window.display();
	}// Exit Game Loop

	return 0;
}
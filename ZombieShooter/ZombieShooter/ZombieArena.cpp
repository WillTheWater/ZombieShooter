#include <SFML/Graphics.hpp>
#include "ZombieArena.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"



using namespace sf;

int main()
{
	// Here is the instance of TextureHolder
	TextureHolder holder;

	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
	// Start with the GAME_OVER state
	State state = State::GAME_OVER;


	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Titlebar);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	// Create the background
	VertexArray background;
	// Load the texture for our background vertex array
	Texture textureBackground = TextureHolder::GetTexture(
		"graphics/background_sheet.png");

	// Prepare for a horde of zombies
	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = NULL;

	// 100 bullets should do
	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	// When was the fire button last pressed?
	Time lastPressed;

	// Hide the mouse pointer and replace it with crosshair
	
	Image crosshairCursor;
	crosshairCursor.loadFromFile("graphics/crosshair.png");
	Cursor crosshairs;
	crosshairs.loadFromPixels(crosshairCursor.getPixelsPtr(), crosshairCursor.getSize(),{ 0,0 });
	window.setMouseCursor(crosshairs);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	// About the game
	int score = 0;
	int hiScore = 0;

	// The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
				}

				if (state == State::PLAYING)
				{
					// Reloading
					if (event.key.code == Keyboard::R)
					{
						if (bulletsSpare >= clipSize)
						{
							// Plenty of bullets. Reload.
							bulletsInClip = clipSize;
							bulletsSpare -= clipSize;
						}
						else if (bulletsSpare > 0)
						{
							// Only few bullets left
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;
						}
						else
						{
							// More here soon?!
						}
					}

				}

			}
		}// End event polling


		 // Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.MoveUp();
			}
			else
			{
				player.StopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.MoveDown();
			}
			else
			{
				player.StopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.MoveLeft();
			}
			else
			{
				player.StopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.MoveRight();
			}
			else
			{
				player.StopRight();
			}
			// Fire a bullet
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (gameTimeTotal.asMilliseconds()
					- lastPressed.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
				{

					// Pass the centre of the player 
					// and the centre of the cross-hair
					// to the shoot function
					bullets[currentBullet].shoot(
						player.GetCenter().x, player.GetCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;

					bulletsInClip--;
				}

			}// End fire a bullet


		}// End WASD while playing

		 // Handle the levelling up state
		if (state == State::LEVELING_UP)
		{
			// Handle the player levelling up
			if (event.key.code == Keyboard::Num1)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num5)
			{
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6)
			{
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				// Prepare thelevel
				// We will modify the next two lines later
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				// Pass the vertex array by reference 
				// to the createBackground function
				int tileSize = CreateBackground(background, arena);

				// Spawn the player in the middle of the arena
				player.Spawn(arena, resolution, tileSize);

				// Configure the pick-ups
				healthPickup.SetArena(arena);
				ammoPickup.SetArena(arena);

				// Create a horde of zombies
				numZombies = 10;

				// Delete the previously allocated memory (if it exists)
				delete[] zombies;
				zombies = createHorde(numZombies, arena);
				numZombiesAlive = numZombies;

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
		}// End levelling up

		 /*
		 ****************
		 UPDATE THE FRAME
		 ****************
		 */
		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;
			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			// Set the crosshair to the mouse world location
			//spriteCrosshair.setPosition(mouseWorldPosition);

			// Update the player
			player.Update(dtAsSeconds, Mouse::getPosition());

			// Make a note of the players new position
			Vector2f playerPosition(player.GetCenter());

			// Make the view centre around the player				
			mainView.setCenter(player.GetCenter());

			// Loop through each Zombie and update them
			for (int i = 0; i < numZombies; i++)
			{
				if (zombies[i].IsAlive())
				{
					zombies[i].Update(dt.asSeconds(), playerPosition);
				}
			}

			// Update any bullets that are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}

			// Update the pickups
			healthPickup.Update(dtAsSeconds);
			ammoPickup.Update(dtAsSeconds);

			// Collision detection
			// Have any zombies been shot?
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < numZombies; j++)
				{
					if (bullets[i].isInFlight() &&
						zombies[j].IsAlive())
					{
						if (bullets[i].getPosition().intersects
						(zombies[j].GetPosition()))
						{
							// Stop the bullet
							bullets[i].stop();

							// Register the hit and see if it was a kill
							if (zombies[j].Hit()) {
								// Not just a hit but a kill too
								score += 10;
								if (score >= hiScore)
								{
									hiScore = score;
								}

								numZombiesAlive--;

								// When all the zombies are dead (again)
								if (numZombiesAlive == 0) {
									state = State::LEVELING_UP;
								}
							}

						}
					}

				}
			}// End zombie being shot

			 // Have any zombies touched the player			
			for (int i = 0; i < numZombies; i++)
			{
				if (player.GetPosition().intersects
				(zombies[i].GetPosition()) && zombies[i].IsAlive())
				{

					if (player.Hit(gameTimeTotal))
					{
						// More here later
					}

					if (player.GetHealth() <= 0)
					{
						state = State::GAME_OVER;

					}
				}
			}// End player touched

			 // Has the player touched health pickup
			if (player.GetPosition().intersects
			(healthPickup.GetPosition()) && healthPickup.IsSpawned())
			{
				player.IncreaseHealthLevel(healthPickup.GotIt());

			}

			// Has the player touched ammo pickup
			if (player.GetPosition().intersects
			(ammoPickup.GetPosition()) && ammoPickup.IsSpawned())
			{
				bulletsSpare += ammoPickup.GotIt();

			}


		}// End updating the scene

		 /*
		 **************
		 Draw the scene
		 **************
		 */

		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(background, &textureBackground);

			// Draw the zombies
			for (int i = 0; i < numZombies; i++)
			{
				window.draw(zombies[i].GetSprite());
			}

			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}
			}


			// Draw the player
			window.draw(player.GetSprite());

			// Draw the pick-ups, if currently spawned
			if (ammoPickup.IsSpawned())
			{
				window.draw(ammoPickup.GetSprite());
			}
			if (healthPickup.IsSpawned())
			{
				window.draw(healthPickup.GetSprite());
			}


			//Draw the crosshair
			//window.draw(spriteCrosshair);

		}

		if (state == State::LEVELING_UP)
		{
		}

		if (state == State::PAUSED)
		{
		}

		if (state == State::GAME_OVER)
		{
		}

		window.display();

	}// End game loop

	return 0;
}
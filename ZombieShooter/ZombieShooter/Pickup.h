#pragma once
#include <SFML/Graphics.hpp>
class Pickup
{
public:
	Pickup(int type);

	// Prepar a new pickup
	void SetArena(sf::IntRect arena);

	void Spawn();

	// Check the position of a pickup
	sf::FloatRect GetPosition();

	// Get the sprite for drawing
	sf::Sprite GetSprite();

	// Let the pickup update itself each frame
	void Update(float elapsedTime);

	// Is this pickup currently spawned
	bool IsSpawned();

	// Get the pickup
	int GotIt();

	//Upgrade value of pickup
	void Upgrade();

private:
	// Start value for health pickups
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	// The sprite that represets the pickup
	sf::Sprite m_Sprite;

	// The area it exists in
	sf::IntRect m_Arena;

	// how much the pick is worth
	int m_Value;

	// What type of pickup
	// 1 = health, 2 = ammo
	int m_Type;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDespawn;
	float m_SecondsToLive;
	float m_SecondsToWait;	
};


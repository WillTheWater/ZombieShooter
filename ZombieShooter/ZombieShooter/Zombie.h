#pragma once
#include <SFML/Graphics.hpp>

class Zombie
{	
public:
	bool						Hit();
	bool						IsAlive();
	void						Spawn(float startX, float startY, int type, int seed);
	sf::FloatRect				GetPosition();
	sf::Sprite					GetSprite();
	void						Update(float elapsedTime, sf::Vector2f playerLocation);

private:
	// Speed of each zombie type
	const float					m_BloaterSpeed = 40;
	const float					m_ChaserSpeed = 80;
	const float					m_CrawlerSpeed = 20;
	// Health of each zombie type
	const float					m_BloaterHealth = 5;
	const float					m_ChaserHealth = 1;
	const float					m_CrawlerHealth = 3;
	// Speed varriance
	const int					m_MaxVarriance = 30;
	const int					m_Offset = 101 - m_MaxVarriance;

	sf::Vector2f				m_Position;
	sf::Sprite					m_Sprite;
	float						m_Speed;
	float						m_Health;
	bool						m_Alive;
};


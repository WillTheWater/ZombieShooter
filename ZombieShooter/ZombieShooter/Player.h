#pragma once
#include "SFML/Graphics.hpp"
class Player
{
public:
	Player();
	void					Spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
	void					ResetPlayerStats();
	bool					Hit(sf::Time timeHit);
	sf::Time				GetLastHitTime();
	sf::FloatRect			GetPosition();
	sf::Vector2f			GetCenter();
	float					GetRotation();
	sf::Sprite				GetSprite();
	void					MoveLeft();
	void					MoveRight();
	void					MoveUp();
	void					MoveDown();
	void					Update(float elapsedTime, sf::Vector2i mouseWorldPosition);
	void					UpgradeSpeed();
	void					UpgradeHealth();
	void					IncreaseHealthLevel(int amount);
	int						GetHealth();
	void					StopLeft();
	void					StopRight();
	void					StopUp();
	void					StopDown();

private:
	const float				m_StartSpeed = 200;
	const float				m_StartHealth = 100;
	sf::Vector2f			m_Position;
	sf::Sprite				m_Sprite;
	sf::Texture				m_Texture;
	sf::Vector2f			m_Resolution;
	sf::IntRect				m_Arena;
	int						m_TileSize;
	bool					m_UpPressed;
	bool					m_DownPressed;
	bool					m_LeftPressed;
	bool					m_RightPressed;
	int						m_Health;
	int						m_MaxHealth;
	sf::Time				m_LastHit;
	float					m_Speed;
};


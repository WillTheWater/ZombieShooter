#pragma once
#include "SFML/Graphics.hpp"
class Player
{
public:
	Player();
	void Spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
	bool Hit(sf::Time timeHit);
	void ResetPlayerStats();
	sf::Time GetLastHitTime();
	sf::FloatRect GetPosition();
	sf::Vector2f GetCenter();
	float GetRotation();
	sf::Sprite GetSprite();
	int GetHealth();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void StopLeft();
	void StopRight();
	void StopUp();
	void StopDown();
	void Update(float elapsedTime, sf::Vector2i mousePosition);
	void UpgradeSpeed();
	void UpgradeHealth();
	void IncreaseHealthLevel(int amount);

private:
	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
	sf::Vector2f m_ScreenResolution;
	sf::IntRect m_Arena;
	sf::Time m_LastHit;
	float m_Speed;
	const float m_StartSpeed = 200;
	const float m_StartHealth = 100;
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
	int m_Health;
	int m_TileSize;
	int m_MaxHealth;
};


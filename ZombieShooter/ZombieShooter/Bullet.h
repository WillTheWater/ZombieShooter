#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	void						Stop();
	bool						IsInFlight();
	void						Shoot(float startX, float startY, float xTarget, float yTarget);
	sf::FloatRect				GetPosition();
	sf::RectangleShape			GetShape();
	void						Update(float elapsedTime);

private:
	sf::Vector2f				m_Position;
	sf::RectangleShape			m_BulletShape;
	bool						m_InFlight = false;
	float						m_BulletSpeed = 1000.f;
	float						m_BulletDistanceX;
	float						m_BulletDistanceY;
	float						m_MaxX;
	float						m_MinX;
	float						m_MaxY;
	float						m_MinY;
};


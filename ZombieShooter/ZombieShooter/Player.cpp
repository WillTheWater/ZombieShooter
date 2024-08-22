#include "Player.h"

Player::Player()
{
	m_Speed     = m_StartSpeed;
	m_Health    = m_StartHealth;
	m_MaxHealth = m_StartHealth;
	m_Texture.loadFromFile("graphics/player.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(25, 25);
}

void Player::Spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
	m_Position.x          = arena.width / 2.f;
	m_Position.y          = arena.height / 2.f;
	m_Arena.left          = arena.left;
	m_Arena.width         = arena.width;
	m_Arena.top           = arena.top;
	m_Arena.height        = arena.height;
	m_TileSize            = tileSize;
	m_ScreenResolution    = resolution;
	m_ScreenResolution.x  = resolution.x;
	m_ScreenResolution.y  = resolution.y;
}

void Player::ResetPlayerStats()
{
	m_Speed     = m_StartSpeed;
	m_Health    = m_StartHealth;
	m_MaxHealth = m_StartHealth;
}

sf::Time Player::GetLastHitTime()
{
	return m_LastHit;
}


bool Player::Hit(sf::Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else { return false; }
}
sf::FloatRect Player::GetPosition()
{
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f Player::GetCenter()
{
	return m_Position;
}

float Player::GetRotation()
{
	return m_Sprite.getRotation();
}

sf::Sprite Player::GetSprite()
{
	return m_Sprite;
}

int Player::GetHealth()
{
	return m_Health;
}

void Player::MoveLeft()
{
	m_LeftPressed = true;
}

void Player::MoveRight()
{
	m_RightPressed = true;
}

void Player::MoveUp()
{
	m_UpPressed = true;
}

void Player::MoveDown()
{
	m_DownPressed = true;
}

void Player::StopLeft()
{
	m_LeftPressed = false;
}

void Player::StopRight()
{
	m_RightPressed = false;
}

void Player::StopUp()
{
	m_UpPressed = false;
}

void Player::StopDown()
{
	m_DownPressed = false;
}

void Player::Update(float elapsedTime, sf::Vector2i mousePosition)
{
	if (m_UpPressed) { m_Position.y -= m_Speed * elapsedTime; }
	if (m_DownPressed) { m_Position.y += m_Speed * elapsedTime; }
	if (m_RightPressed) { m_Position.x += m_Speed * elapsedTime; }
	if (m_LeftPressed) { m_Position.x -= m_Speed * elapsedTime; }
	m_Sprite.setPosition(m_Position);
	if (m_Position.x > m_Arena.width - m_TileSize) { m_Position.x = m_Arena.width - m_TileSize; }
	if (m_Position.x < m_Arena.left + m_TileSize) { m_Position.x = m_Arena.left + m_TileSize; }
	if (m_Position.y > m_Arena.height - m_TileSize) { m_Position.y = m_Arena.height - m_TileSize; }
	if (m_Position.y < m_Arena.top + m_TileSize) { m_Position.y = m_Arena.top + m_TileSize; }
	float facingAngle = atan2(mousePosition.y - m_ScreenResolution.y / 2.f,
		                      mousePosition.x - m_ScreenResolution.x / 2.f);
	facingAngle = (facingAngle * 180.0f) / 3.14159265f;
	m_Sprite.setRotation(facingAngle);
}

void Player::UpgradeSpeed()
{
	m_Speed += (m_StartSpeed * 0.2f);
}

void Player::UpgradeHealth()
{
	m_MaxHealth += (m_MaxHealth * 0.2f);
}

void Player::IncreaseHealthLevel(int amount)
{
	m_Health += amount;
	if (m_Health > m_MaxHealth) { m_Health = m_MaxHealth; }
}


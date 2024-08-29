#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

bool Zombie::Hit()
{
    m_Health--;
    if (m_Health < 0)
    {
        m_Alive = false;
        m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
        return true;
    }
    return false;
}

bool Zombie::IsAlive()
{
    return m_Alive;
}

void Zombie::Spawn(float startX, float startY, int type, int seed)
{
    switch (type)
    {
    case 0:
        // Bloater
        m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
        m_Speed = 40;
        m_Health = 5;
        break;
    case 1:
        // Chaser
        m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
        m_Speed = 70;
        m_Health = 1;
        break;
    case 2:
        // Crawler
        m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
        m_Speed = 20;
        m_Health = 3;
        break;
    }
    // Mod speed to make zombie unique
    srand((int)time(0) * seed);
    float modifier = (rand() % m_MaxVarriance) + m_Offset;
    modifier /= 100;
    m_Speed *= modifier;

    // Position
    m_Position.x = startX;
    m_Position.y = startY;
    m_Sprite.setOrigin(25, 25);
    m_Sprite.setPosition(m_Position);
}

sf::FloatRect Zombie::GetPosition()
{
    return m_Sprite.getGlobalBounds();
}

sf::Sprite Zombie::GetSprite()
{
    return m_Sprite;
}

void Zombie::Update(float elapsedTime, sf::Vector2f playerLocation)
{
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;
    if (playerX > m_Position.x)
    {
        m_Position.x = m_Position.x + m_Speed * elapsedTime;
    }
    if (playerY > m_Position.y)
    {
        m_Position.y = m_Position.y + m_Speed * elapsedTime;
    }
    if (playerX < m_Position.x)
    {
        m_Position.x = m_Position.x - m_Speed * elapsedTime;
    }
    if (playerY < m_Position.y)
    {
        m_Position.y = m_Position.y - m_Speed * elapsedTime;
    }
    m_Sprite.setPosition(m_Position);
    float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.141;
    m_Sprite.setRotation(angle);
}

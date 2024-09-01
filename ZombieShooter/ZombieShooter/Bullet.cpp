#include "Bullet.h"

Bullet::Bullet()
{
    m_BulletShape.setSize(sf::Vector2f{ 2,2 });
}

void Bullet::Stop()
{
    m_InFlight = false;
}

bool Bullet::IsInFlight()
{
    return m_InFlight;
}

void Bullet::Shoot(float startX, float startY, float xTarget, float yTarget)
{
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;

    float gradient = (startX - xTarget) / (startY - yTarget);
    if (gradient < 0) { gradient *= -1; }
    float ratioXY = m_BulletSpeed / (1 + gradient);
    m_BulletDistanceY = ratioXY;
    m_BulletDistanceX = ratioXY * gradient;
    if (xTarget < startX) { m_BulletDistanceX *= -1; }
    if (yTarget < startY) { m_BulletDistanceY *= -1; }
    float range = 1000;
    m_MinX = startX - range;
    m_MaxX = startX + range;
    m_MinY = startY - range;
    m_MaxY = startY + range;
    m_BulletShape.setPosition(m_Position);
}

sf::FloatRect Bullet::GetPosition()
{
    return m_BulletShape.getGlobalBounds();
}

sf::RectangleShape Bullet::GetShape()
{
    return m_BulletShape;
}

void Bullet::Update(float elapsedTime)
{
    m_Position.x += m_BulletDistanceX * elapsedTime;
    m_Position.y += m_BulletDistanceY * elapsedTime;
    m_BulletShape.setPosition(m_Position);
    if (m_Position.x < m_MinX || m_Position.x > m_MaxX || m_Position.y < m_MinY || m_Position.y > m_MaxY)
    {
        m_InFlight = false;
    }
}

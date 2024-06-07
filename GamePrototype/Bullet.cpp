#include "pch.h"
#include "Bullet.h"
#include "Character.h"

using namespace utils;

Bullet::Bullet(Point2f startPos, Vector2f direction) :
	m_Pos{ startPos },
	m_MovingVector{ direction }
{

}

void Bullet::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Pos.x, m_Pos.y, 0.f);
		SetColor(Color4f{ 1.f,1.f,1.f,1.f });
		FillEllipse(0.f,0.f, 3.f, 3.f);
	}
	glPopMatrix();
}

Character* Bullet::Update(const float elapsedSec, std::vector<Character*> enemies)
{
	Move(elapsedSec);
	Character* pCharacter = CheckHit(enemies);
	m_DeathTimer += elapsedSec;
	return pCharacter;
}

Character* Bullet::CheckHit(std::vector<Character*> enemies)
{
	std::vector<std::vector<Point2f>> enemyModels{};
	HitInfo hitInfo{};
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemyModels.push_back(enemies[i]->GetModelGeometry());
	}
	for (size_t i = 0; i < enemies.size(); i++)
	{
		for (size_t angle = 0; angle < 2 * M_PI; angle += M_PI / 2)
		{
			Point2f rayEndPoint{
				m_Pos.x + (float)cos(angle)*3.f,
				m_Pos.y + (float)sin(angle)*3.f
			};
			if (Raycast(enemyModels[i], m_Pos, rayEndPoint, hitInfo))
			{
				return enemies[i];
			}
		}
	}
	return nullptr;
}

float Bullet::GetDeathTimer()
{
	return m_DeathTimer;
}

void Bullet::Move(const float elapsedSec)
{
	m_Pos += m_MovingVector * m_Speed * elapsedSec;
}

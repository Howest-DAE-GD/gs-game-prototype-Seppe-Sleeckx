#include "pch.h"
#include "Bomb.h"
#include "Character.h"

using namespace utils;

Bomb::Bomb(Point2f startPos, Vector2f direction) :
	m_Pos{startPos},
	m_MovingVector{direction},
	m_DeathTimer{3.f}
{

}

void Bomb::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Pos.x, m_Pos.y, 0.f);
		SetColor(*m_pColor);
		FillEllipse(0.f, 0.f, 55.f, 55.f);
	}
	glPopMatrix();
}

std::vector<int> Bomb::Update(const float elapsedSec, std::vector<Character*> enemies, const std::vector<std::vector<Point2f>>& mapVertices)
{
	Move(elapsedSec);
	utils::HitInfo hitInfo{};
	bool hit{ false };
	// With environment
	for (int index{}; index < mapVertices.size(); ++index)
	{
		for (float angle{}; angle < 2 * M_PI; angle += M_PI / 2)
		{
			Point2f rayEndPoint{
				m_Pos.x + (float)cos(angle) * 3.f,
				m_Pos.y + (float)sin(angle) * 3.f
			};
			if (Raycast(mapVertices[index], m_Pos, rayEndPoint, hitInfo))
			{
				if (hitInfo.normal.y != 0.f)
				{
					m_MovingVector.y *= -1;
				}
				if (hitInfo.normal.x != 0.f)
				{
					m_MovingVector.x *= -1;
				}
			}
		}
	}
	std::vector<int> hitEnemies{};
	if (m_DeathTimer <= 1.f)
	{
		hitEnemies = CheckHit(enemies);
		Explode();
	}
	m_DeathTimer -= elapsedSec;
	return hitEnemies;
}

float Bomb::IsExploded()
{
	if (m_DeathTimer <= 0.f)
	{
		return true;
	}
	return false;
}

void Bomb::Move(const float elapsedSec)
{
	if (m_DeathTimer > 1.f)
	{
		m_Pos += m_MovingVector * m_Speed * elapsedSec;
	}
}

std::vector<int> Bomb::CheckHit(std::vector<Character*> enemies)
{
	Circlef circle{ m_Pos, 80.f };
	std::vector<int> hitEnemies{};
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (IsPointInCircle(enemies[i]->GetPosition(), circle))
		{
			hitEnemies.push_back(i);
		}
	}
	return hitEnemies;
}

void Bomb::Explode()
{
	if (*m_pColor == Color4f{1.f,1.f,1.f,1.f})
	{
		delete m_pColor;
		m_pColor = new Color4f{ 0.5f,0.f,0.f,1.f };
	}
	else
	{
		delete m_pColor;
		m_pColor = new Color4f{ 1.f,1.f,1.f,1.f };
	}
}
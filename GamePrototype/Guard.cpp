#include "pch.h"
#include "Guard.h"
#include "utils.h"

using namespace utils;

Guard::Guard(Point2f startpos, Color4f color) :
	Character(startpos, color),
	m_VisionCone{ new VisionCone{100, 40} }
{

}

Guard::~Guard()
{
	delete m_VisionCone;
}

void Guard::Draw() const
{
	glPushMatrix();
	{
		if (m_VisionConeVisibility)
		{
			glTranslatef(m_Position.x, m_Position.y, 0.f);
			m_VisionCone->Draw();
		}
	}
	glPopMatrix();
	Character::Draw();
}

void Guard::ChangeDirection(Vector2f newDirection)
{
	m_VisionCone->ChangeDirection(newDirection);
	Character::ChangeDirection(newDirection);
}

bool Guard::SpotTarget(Color4f& targetColor, Point2f targetPos, const std::vector<std::vector<Point2f>>& collisionVertices)
{
	if (m_VisionCone->IsPointInCone(targetPos, m_Position) && targetColor != m_Color)
	{
		HitInfo hitInfo{};
		for (int index{}; index < collisionVertices.size(); ++index)
		{
			if (Raycast(collisionVertices[index], m_Position, targetPos, hitInfo))
			{
				float distanceToTarget = sqrt(pow(targetPos.x - m_Position.x, 2) + pow(targetPos.y - m_Position.y, 2));
				if (distanceToTarget <= hitInfo.lambda)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return false;
}
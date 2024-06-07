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

bool Guard::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& collisionVertices)
{
	return Character::Update(elapsedSec, collisionVertices);
}

void Guard::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		m_VisionCone->Draw();
	}
	glPopMatrix();
	Character::Draw();
}

void Guard::ChangeDirection(Vector2f newDirection)
{
	m_VisionCone->ChangeDirection(newDirection);
	Character::ChangeDirection(newDirection);
}

bool Guard::SpotTarget(Character& target)
{
	if (!(target.m_Color.r == m_Color.r && target.m_Color.g == m_Color.g && target.m_Color.b == m_Color.b))
	{
		double startAngle{ atan2(m_VisionCone->m_FacingVector.y, m_VisionCone->m_FacingVector.x) };
		double endAngle{ startAngle - atan2(m_VisionCone->m_VisionWidth / 2, m_VisionCone->m_VisionLength) };
		startAngle += atan2(m_VisionCone->m_VisionWidth / 2, m_VisionCone->m_VisionLength);
		utils::HitInfo hitInfo{};
		std::vector<Point2f> targetGeometry{ target.GetModelGeometry() };
		for (double angle{ startAngle }; angle > endAngle; angle -= M_PI / 4.f)
		{
			Point2f rayEndPoint{
				m_Position.x + (float)cos(angle) * m_VisionCone->m_VisionLength - (float)sin(angle) * m_VisionCone->m_VisionWidth / 2,
				m_Position.y + (float)sin(angle) * m_VisionCone->m_VisionLength - (float)cos(angle) * m_VisionCone->m_VisionWidth / 2
			};
			if (Raycast(targetGeometry, m_Position, rayEndPoint, hitInfo))
			{
				return true;
			}

		}
	}
	return false;
}
#include "pch.h"
#include "Character.h"
#include <utils.h>
#include "KeyboardManager.h"
#include <vector>
#include <iostream>
using namespace utils;

Character::Character(Point2f startpos, Color4f color, float speed) :
	m_Position{ startpos },
	m_Color{ color },
	m_Model{ Rectf{-10.f, -10.f, 20.f, 20.f } },
	m_MovingVector{},
	m_Speed{speed}
{

}

void Character::Move(float elapsedSec)
{
	m_Position += m_MovingVector *m_Speed * elapsedSec;
}

void Character::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		SetColor(m_Color);
		DrawRect(m_Model);
	}
	glPopMatrix();
}

bool Character::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& collisionVertices)
{
	//Collision
	Move(elapsedSec);
	utils::HitInfo hitInfo{};
	bool hit{ false };
	// With environment
	for (int index{}; index < collisionVertices.size(); ++index)
	{
		for (float angle{}; angle < 2*M_PI; angle += M_PI/2)
		{
			Point2f rayEndPoint{
				m_Position.x + (float)cos(angle) * (m_Model.width / 2),
				m_Position.y + (float)sin(angle) * (m_Model.height / 2)
			};
			if (Raycast(collisionVertices[index], m_Position, rayEndPoint, hitInfo))
			{
				MoveBackInsideBounds(elapsedSec,hitInfo);
				return true;
			}
		}
	}
	return false;
}

void Character::MoveBackInsideBounds(const float elapsedSec, utils::HitInfo& hitInfo)
{
	//m_Position += hitInfo.normal * hitInfo.lambda;
	m_Position += hitInfo.normal * ((m_Position - hitInfo.intersectPoint).Length());
	
}

void Character::ChangeDirection(Vector2f newDirection)
{
	if (newDirection != Vector2f{0,0})
	{
		m_MovingVector = newDirection / newDirection.Length();
	}
	else
	{
		m_MovingVector = Vector2f{ 0,0 };
	}
}

const std::vector<Point2f> Character::GetModelGeometry() const
{
	const std::vector<Point2f> returnValue{
		Point2f{m_Position.x + m_Model.left, m_Position.y + m_Model.bottom},
		Point2f{m_Position.x + m_Model.left + m_Model.width, m_Position.y + m_Model.bottom},
		Point2f{m_Position.x + m_Model.left + m_Model.width, m_Position.y + m_Model.bottom + m_Model.height},
		Point2f{m_Position.x + m_Model.left, m_Position.y + m_Model.bottom + m_Model.height}
	};
	return returnValue;
}

Point2f Character::GetPosition()
{
	Point2f centrePosition{
		m_Position.x + 5.f,
		m_Position.y + 5.f
	};
	return centrePosition;
}

void Character::SetPosition(Point2f pos)
{
	m_Position = pos;
}

Vector2f Character::GetDirection()
{
	return m_MovingVector;
}

const Rectf Character::GetModelRect()
{
	Rectf rect = m_Model;
	rect.left = m_Position.x;
	rect.bottom = m_Position.y;
	return rect;
}

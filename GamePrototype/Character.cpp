#include "pch.h"
#include "Character.h"
#include "utils.h"

using namespace utils;

Character::Character(Point2f startpos, Color4f color) :
	m_Position{ startpos },
	m_Color{ color }
{

}

void Character::Move(Vector2f vector)
{
	m_Position += vector;
}

void Character::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		SetColor(m_Color);
		DrawRect(m_Model);
	}
	glPopMatrix();
	
}
#include "pch.h"
#include "Guard.h"
#include "utils.h"

using namespace utils;

Guard::Guard(Point2f startpos) :
	Character(startpos, Color4f(0.f, 0.f, 1.f, 1.f)),
	m_visionCone{}
{

}

void Guard::Update()
{
	float angle = atan2(m_FacingDirection.y, m_FacingDirection.x);
	m_visionCone[0] = Point2f{ m_FacingDirection.x - 50 * cos(angle), m_FacingDirection.y - 20 * sin(angle) };
	m_visionCone[1] = Point2f{ m_FacingDirection.x + 50 * cos(angle), m_FacingDirection.y + 20 * sin(angle) };
}

void Guard::Move(Vector2f vector)
{
	m_FacingDirection = vector;
	m_Position += vector;
}

void Guard::Draw()
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		SetColor(Color4f(1.f, 0.f, 1.f, 1.f));
		DrawPolygon(m_visionCone);
	}
	glPopMatrix();
	Character::Draw();
}
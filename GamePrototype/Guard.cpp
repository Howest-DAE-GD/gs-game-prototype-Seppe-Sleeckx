#include "pch.h"
#include "Guard.h"
#include "utils.h"

using namespace utils;

Guard::Guard(Point2f startpos) :
	Character(startpos, Color4f(0.f, 0.f, 1.f, 1.f)),
	m_VisionCone{ new VisionCone{0.f, 100} }
{

}

void Guard::Update(float elapsedSec)
{
	Character::Update(elapsedSec);
}

void Guard::Draw() const
{

	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glRotatef(m_VisionCone->m_FacingDirection, 0.f, 0.f, 1.f);
		m_VisionCone->Draw();
	}
	glPopMatrix();
	Character::Draw();
}

void Guard::ChangeDirection(float angle)
{
	m_VisionCone->ChangeDirection(angle);
}

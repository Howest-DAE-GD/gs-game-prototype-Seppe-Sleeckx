#include "pch.h"
#include "Orb.h"


Orb::Orb() :
	m_Circle{
	Point2f{(float)(rand() % 1000),(float)(rand() % 500)},
	5.f
	}
{

}
Orb::Orb(Point2f pos) :
	m_Circle{pos, 5.f}
{

}

bool Orb::CheckHit(Character* target)
{
	return utils::IsOverlapping(target->GetModelRect(), m_Circle);
}

void Orb::SetNewPosition()
{
	m_Circle.center.x = rand() % 2000;
	m_Circle.center.y = rand() % 1000;
}

void Orb::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Circle.center.x, m_Circle.center.y, 0.f);
		utils::SetColor(Color4f{ 1.f,1.f,0.f,1.f });
		utils::FillEllipse(Point2f{0,0}, 5.f, 5.f);
	}
	glPopMatrix();
}

Point2f Orb::GetPosition()
{
	return m_Circle.center;
}
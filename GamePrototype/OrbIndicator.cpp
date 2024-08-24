#include "pch.h"
#include "OrbIndicator.h"
#include "Orb.h"

OrbIndicator::OrbIndicator(Point2f screenCenter, Orb* target) :
	Arrow(screenCenter, 100.f, new Color4f{ 1.f,1.f,0.f,1.f }),
	m_pTarget{target}
{

}

OrbIndicator::~OrbIndicator()
{

}

void OrbIndicator::Draw()
{
	if (m_pTarget!= nullptr)
	{
		Arrow::Draw();
	}
}

void OrbIndicator::UpdateAngle(Point2f originPos)
{
	if (m_pTarget != nullptr)
	{
		SetAngle(atan2f(m_pTarget->GetPosition().y - originPos.y, m_pTarget->GetPosition().x - originPos.x));
	}
}

void OrbIndicator::AssignNewTarget(Orb* newTarget)
{
	m_pTarget = newTarget;
}
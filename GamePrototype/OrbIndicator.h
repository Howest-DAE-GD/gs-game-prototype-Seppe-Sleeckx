#pragma once
#include "Arrow.h"

class Orb;

class OrbIndicator : public Arrow
{
public:
	OrbIndicator(Point2f startPos, Orb* target = nullptr);
	~OrbIndicator();

	virtual void Draw() override;
	void UpdateAngle(Point2f originPos);
	void AssignNewTarget(Orb* newTarget);

private:
	Orb* m_pTarget;
};


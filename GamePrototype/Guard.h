#pragma once
#include "Character.h"
#include "VisionCone.h"
#include <vector>

class Guard : public Character
{
public:
	Guard(Point2f startpos);
	void Update(float elapsedSec);
	virtual void Draw() const override;
	virtual void ChangeDirection(float angle);

private:
	VisionCone* m_VisionCone;
};


#pragma once
#include "Character.h"
#include <vector>

class Guard : public Character
{
public:
	Guard(Point2f startpos);
	void Update();
	virtual void Move(Vector2f vector) override;
	virtual void Draw() override;

private:
	Vector2f m_FacingDirection;
	std::vector<Point2f> m_visionCone;
};


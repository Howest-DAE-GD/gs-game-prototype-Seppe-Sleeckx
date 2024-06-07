#pragma once
#include "Character.h"

class Orb
{
public:
	Orb();
	Orb(Point2f pos);

	bool CheckHit(Character* target);
	void SetNewPosition();
	Point2f GetPosition();

	void Draw() const;


private:
	Circlef m_Circle;
};


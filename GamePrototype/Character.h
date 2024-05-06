#pragma once
#include "Vector2f.h"

class Character
{
public:
	Character(Point2f startpos, Color4f color, float speed=40.f);
	
	void Move();
	virtual void Draw() const;
	virtual void Update(float elapsedSec);

protected:
	float m_Speed;
	Vector2f m_MovingVector;
	Point2f m_Position;
	Rectf m_Model;
	Color4f m_Color;
};


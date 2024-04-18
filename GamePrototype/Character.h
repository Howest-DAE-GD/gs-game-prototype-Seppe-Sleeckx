#pragma once
#include "Vector2f.h"

class Character
{
public:
	Character(Point2f startpos, Color4f color);
	
	virtual void Move(Vector2f vector);
	virtual void Draw();

protected:
	Point2f m_Position;
	Rectf m_Model;
	Color4f m_Color;
};


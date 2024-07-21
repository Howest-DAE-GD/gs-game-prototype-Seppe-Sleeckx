#pragma once
#include "pch.h"
#include <utils.h>
using namespace utils;

class Arrow
{
public:
	Arrow(Point2f startpos, float length, Color4f* color, float angle = 0.f);

	~Arrow();

	virtual void Draw();
	void Rotate(float angle);
	void SetAngle(float angle);

private:

	Point2f m_StartPos;
	float m_Angle;
	const float m_Length;
	const Color4f* m_Color;
};


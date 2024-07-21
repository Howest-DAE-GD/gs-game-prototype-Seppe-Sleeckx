#include "pch.h"
#include "Arrow.h"

Arrow::Arrow(Point2f startpos, float length, Color4f* color, float angle) :
	m_StartPos{ startpos },
	m_Angle{ angle },
	m_Length{ length },
	m_Color{ color }
{

}

Arrow::~Arrow()
{
	delete m_Color;
}

void Arrow::Draw()
{
	SetColor(*m_Color);
	Point2f endPoint{ m_StartPos.x + cosf(m_Angle) * m_Length, m_StartPos.y + sinf(m_Angle) * m_Length };
	DrawLine(m_StartPos, endPoint);
	float leftAngle{ m_Angle + 15.f };
	Point2f leftEndPoint{ endPoint.x + 20.f * cosf(leftAngle), endPoint.y + 20.f * sinf(leftAngle) };
	DrawLine(endPoint, leftEndPoint);
	float rightAngle{ m_Angle - 15.f };
	Point2f rightEndPoint{ endPoint.x + 20.f * cosf(rightAngle), endPoint.y + 20.f * sinf(rightAngle) };
	DrawLine(endPoint, rightEndPoint);
}

void Arrow::Rotate(float angle)
{
	m_Angle += angle;
	if (m_Angle > 360.f)
	{
		m_Angle -= 360;
	}
	else if (m_Angle < 0.f)
	{
		m_Angle += 360;
	}
}

void Arrow::SetAngle(float angle)
{
	m_Angle = angle;
}
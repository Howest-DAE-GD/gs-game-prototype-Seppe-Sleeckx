#pragma once
#include "pch.h"
#include "utils.h"
#include <vector>
#include <iostream>

using namespace utils;


struct VisionCone
{
	explicit VisionCone(int visionLenghth, int visionWidth, Color4f color = Color4f{ 1.f,0.f,0.f,1.f }) :
		m_Color{ color },
		m_VisionLength{ visionLenghth },
		m_VisionWidth{ visionWidth },
		m_VisionConeGeometry{
			Point2f{},
			Point2f{(float)visionLenghth, (float)(visionWidth / 2)},
			Point2f{(float)visionLenghth, (float)(-visionWidth / 2)}
		},
		m_FacingVector{Vector2f{1,0}}
	{
	}

	~VisionCone()
	{
		delete[] m_VisionConeGeometry;
	}

	void Draw() const
	{
		SetColor(m_Color);
		DrawPolygon(m_VisionConeGeometry, 3);
	}

	void Rotate()
	{
		float angle{ atan2(m_FacingVector.y, m_FacingVector.x) };
		m_VisionConeGeometry[1] = Point2f{
			(float)m_VisionLength * cos(angle) + (float)(m_VisionWidth / 2) * -sin(angle),
			(float)m_VisionLength * sin(angle) + (float)(m_VisionWidth / 2) * cos(angle)
		};
		m_VisionConeGeometry[2] = Point2f{
			(float)m_VisionLength * cos(angle) + (float)(-m_VisionWidth / 2) * -sin(angle),
			(float)m_VisionLength * sin(angle) + (float)(-m_VisionWidth / 2) * cos(angle)
		};
	}

	void ChangeDirection(Vector2f newDirection)
	{
		if (newDirection.Length() != 0 && m_FacingVector != newDirection)
		{
			m_FacingVector = newDirection;
			Rotate();
		}
	}


	Color4f m_Color;
	Point2f m_VisionConeGeometry[3];
	Vector2f m_FacingVector;
	int m_VisionLength;
	int m_VisionWidth;
};
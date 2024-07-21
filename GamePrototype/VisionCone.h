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


	bool IsPointInCone(Point2f target, Point2f OwnPos)
	{
		Point2f p1 = m_VisionConeGeometry[0] + OwnPos;
		Point2f p2 = m_VisionConeGeometry[1] + OwnPos;
		Point2f p3 = m_VisionConeGeometry[2] + OwnPos;
		float coneArea{ abs(p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.x * p3.y - p2.x * p1.y - p3.x * p2.y) / 2 }; //Area of visionCone
		float SumTargetArea{ abs(target.x * p2.y + p2.x * p3.y + p3.x * target.y - target.x * p3.y - p2.x * target.y - p3.x * p2.y) / 2 }; //Area of p1, p2 and target
		SumTargetArea += abs(p1.x * target.y + target.x * p3.y + p3.x * p1.y - p1.x * p3.y - target.x * p1.y - p3.x * target.y) / 2; // Area of p2, p3 and target
		SumTargetArea += abs(p1.x * p2.y + p2.x * target.y + target.x * p1.y - p1.x * target.y - p2.x * p1.y - target.x * p2.y) / 2; //Area of p3,p1 and target
		if (SumTargetArea == coneArea)
		{
			return true;
		}
		return false;
	}


	Color4f m_Color;
	Point2f m_VisionConeGeometry[3];
	Vector2f m_FacingVector;
	int m_VisionLength;
	int m_VisionWidth;
};
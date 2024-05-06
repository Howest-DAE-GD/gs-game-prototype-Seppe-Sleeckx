#pragma once
#include "pch.h"
#include "utils.h"
#include <vector>
#include <iostream>

using namespace utils;


struct VisionCone
{
	explicit VisionCone(float facingDirection, int visionLenghth, Color4f color = Color4f{ 1.f,0.f,0.f,1.f }) :
		m_Color{ color },
		m_FacingDirection{ facingDirection },
		m_VisionLength{ visionLenghth },
		m_VisionConeGeometry{ Point2f{}, Point2f{}, Point2f{} }
	{
		m_VisionConeGeometry[1] = Point2f{ (float)m_VisionLength * (float)cos(facingDirection), 0.5f * m_VisionLength * (float)sin(facingDirection+20.f) };
		m_VisionConeGeometry[2] = Point2f{ (float)m_VisionLength * (float)cos(facingDirection), 0.5f * m_VisionLength * (float)sin(facingDirection-20.f) };
	}

	void Draw() const
	{
		SetColor(m_Color);
		DrawPolygon(m_VisionConeGeometry);
	}

	void ChangeDirection(float angle)
	{
		m_FacingDirection = angle;
	}

	Color4f m_Color;
	std::vector<Point2f> m_VisionConeGeometry;
	int m_VisionLength;
	float m_FacingDirection;
};
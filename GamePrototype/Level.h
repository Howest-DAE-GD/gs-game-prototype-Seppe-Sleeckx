#pragma once
#include "pch.h"
#include "utils.h"
#include <vector>
#include "SVGParser.h"

using namespace utils;
struct Level
{
	Level()
	{
		SVGParser::GetVerticesFromSvgFile("Map.svg", m_Vertices);
	}

	void Draw() const
	{
		SetColor(Color4f{ 0.f,0.f,0.f,1.f });
		for (size_t i = 0; i < m_Vertices.size(); i++)
		{
			DrawPolygon(m_Vertices[i]);
		}
	}
	std::vector<std::vector<Point2f>> m_Vertices;
};
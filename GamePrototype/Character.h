#pragma once
#include "Vector2f.h"
#include "pch.h"
#include <vector>
#include <utils.h>

class Character
{
public:
	//Constuctor
	Character(Point2f startpos, Color4f color, float speed=120.f);

	//rest
	virtual void Move(float elapsedSec);
	virtual void Draw() const;
	virtual bool Update(float elapsedSec, const std::vector<std::vector<Point2f>>& mapVertices);
	virtual void ChangeDirection(Vector2f newDirection);
	Vector2f GetDirection();
	Point2f GetPosition();
	void SetPosition(Point2f pos);
	const std::vector<Point2f> GetModelGeometry() const;
	const Rectf GetModelRect();
	Color4f m_Color;
	
protected:
	float m_Speed;
	Vector2f m_MovingVector;
	Point2f m_Position;
	Rectf m_Model;
	void MoveBackInsideBounds(const float elapsedSec, utils::HitInfo& hitInfo);
};


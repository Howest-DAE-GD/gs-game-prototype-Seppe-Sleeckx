#pragma once
#include "Character.h"
#include "VisionCone.h"
#include <vector>

class Guard final: public Character
{
public:
	Guard(Point2f startpos, Color4f color);
	~Guard();
	virtual void Draw() const override;
	virtual void ChangeDirection(Vector2f newDirection) override;
	bool SpotTarget(Color4f& targetColor, Point2f targetPos, const std::vector<std::vector<Point2f>>& collisionVertices);

	float cooldownTimer{};
private:
	VisionCone* m_VisionCone;
};


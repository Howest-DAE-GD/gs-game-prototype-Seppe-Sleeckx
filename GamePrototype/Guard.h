#pragma once
#include "Character.h"
#include "VisionCone.h"
#include <vector>

class Guard final: public Character
{
public:
	Guard(Point2f startpos, Color4f color);
	~Guard();
	virtual bool Update(float elapsedSec, const std::vector<std::vector<Point2f>>& collisionVertices) override;
	virtual void Draw() const override;
	virtual void ChangeDirection(Vector2f newDirection) override;
	bool SpotTarget(Character& target);

	float cooldownTimer{};
private:
	VisionCone* m_VisionCone;
};


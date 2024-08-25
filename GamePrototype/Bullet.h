#pragma once
#include <utils.h>
class Character;

class Bullet
{
public:
	Bullet(Point2f startPos, Vector2f direction);

	void Draw();
	Character* Update(const float elapsedSec, std::vector<Character*> enemies, const std::vector<std::vector<Point2f>>& mapVertices);
	float GetDeathTimer();
	void Move(const float elapsedSec);

private:
	Character* CheckHit(std::vector<Character*> enemies);

	Point2f m_Pos;
	Vector2f m_MovingVector;
	const float m_Speed{ 500.f };
	float m_DeathTimer{};
};


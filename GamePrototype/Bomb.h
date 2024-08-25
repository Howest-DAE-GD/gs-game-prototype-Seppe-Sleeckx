#pragma once
#include <utils.h>
class Character;

class Bomb
{
public:
	Bomb(Point2f startPos, Vector2f direction);

	void Draw();
	std::vector<int> Update(const float elapsedSec, std::vector<Character*> enemies, const std::vector<std::vector<Point2f>>& mapVertices);
	float IsExploded();
	void Move(const float elapsedSec);
	bool m_KilledGuards{ false };
private:
	std::vector<int> CheckHit(std::vector<Character*> enemies);
	void Explode();

	Color4f* m_pColor{ new Color4f{1.f,1.f,1.f,1.f} };
	Point2f m_Pos;
	Vector2f m_MovingVector;
	const float m_Speed{ 200.f };
	float m_DeathTimer{};
	
};


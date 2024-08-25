#pragma once
#include "Guard.h"
#include "NPCManager.h"
#include <vector>

class GuardManager final
{
public:
	GuardManager(int amountOfGuards, Character* target);
	~GuardManager();

	bool Update(float elapsedSec, const std::vector<std::vector<Point2f>>& mapVertices);
	void Draw();
	void Draw(int index);
	int AmountOfGuards();
	void AddGuards(int amount, Color4f& color);
	Point2f GetGuardPosition(int index);

	std::vector<Character*> GetGuardPtrs();

private:
	std::vector<NPCManager*> m_Guards;
	Color4f GuardColors[3]{
		Color4f{0.f,1.f,0.f,1.f},
		Color4f{0.f,0.f,1.f,1.f},
		Color4f{0.5f,0.1f,0.9f,1.f}
	};
	Character* m_Target;
};


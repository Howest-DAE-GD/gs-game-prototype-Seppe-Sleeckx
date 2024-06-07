#pragma once
#include "Character.h"
class NPCManager
{
public:
	NPCManager(Character* const character );
	~NPCManager();

	void Update(const float elapsedSec, const std::vector<std::vector<Point2f>> mapVertices);
	virtual void Draw();
	Character* const GetCharacterPtr();

private:
	void SetRandomDirection();
	Point2f m_LastPosition;
	Character* m_pCharacter;
};


#include "pch.h"
#include "NPCManager.h"

#pragma region Constructor/Destructor
NPCManager::NPCManager(Character* const character):
	m_pCharacter{character}
{
	SetRandomDirection();
}

NPCManager::~NPCManager()
{
	delete m_pCharacter;
}
#pragma endregion

void NPCManager::Update(const float elapsedSec, const std::vector<std::vector<Point2f>> mapVertices)
{
	const bool characterCollided{ m_pCharacter->Update(elapsedSec, mapVertices) };

	//end
	if (characterCollided)
	{
		SetRandomDirection();
	}
	else if (m_LastPosition.x == m_pCharacter->GetPosition().x && m_LastPosition.y == m_pCharacter->GetPosition().y)
	{
		SetRandomDirection();
	}
	m_LastPosition = m_pCharacter->GetPosition();
}

void NPCManager::Draw()
{
	m_pCharacter->Draw();
}

void NPCManager::SetRandomDirection()
{
	const float x{ (float)(rand() % 3) - 1 };
	const float y{ (float)(rand() % 3) - 1 };
	m_pCharacter->ChangeDirection(Vector2f{ x,y });
}

Character* const NPCManager::GetCharacterPtr()
{
	return m_pCharacter;
}
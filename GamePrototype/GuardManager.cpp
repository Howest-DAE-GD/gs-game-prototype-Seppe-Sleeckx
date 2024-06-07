#include "pch.h"
#include "GuardManager.h"

GuardManager::GuardManager(int amountOfGuards, Character* target) :
	m_Target{ target }
{
	for (size_t i = 0; i < amountOfGuards; i++)
	{
		Point2f position{
			(float)(rand() % 2000),
			(float)(rand() % 1000)
		};
		if ((position - target->GetPosition()).Length() < 120)
		{
			position.x += 120;
		}
		Color4f color{
			GuardColors[rand() % 2]
		};
		m_Guards.push_back(new NPCManager{ new Guard{position, color } });
	};
}

GuardManager::~GuardManager()
{
	for (size_t i = 0; i < m_Guards.size(); i++)
	{
		delete m_Guards[i];
	}
}


bool GuardManager::Update(float elapsedSec, const std::vector<std::vector<Point2f>>& mapVertices)
{
	bool spotted{ false };
	for (size_t i = 0; i < m_Guards.size(); i++)
	{
		m_Guards[i]->Update(elapsedSec,mapVertices);
		if (static_cast<Guard*>(m_Guards[i]->GetCharacterPtr())->SpotTarget(*m_Target))
		{
			spotted = true;
			break;
		}
	}
	return spotted;
}

void GuardManager::Draw()
{
	for (size_t i = 0; i < m_Guards.size(); i++)
	{
		m_Guards[i]->Draw();
	}
}


std::vector<Character*> GuardManager::GetGuardPtrs()
{
	std::vector<Character*> guardPtrs{};
	for (size_t i = 0; i < m_Guards.size(); i++)
	{
		guardPtrs.push_back(m_Guards[i]->GetCharacterPtr());
	}
	return guardPtrs;
}

void GuardManager::AddGuards(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		Point2f position{
			(float)(rand() % 2000),
			(float)(rand() % 1000)
		};
		if ((position - m_Target->GetPosition()).Length() < 120)
		{
			position.x += 120;
		}
		Color4f color{
			GuardColors[rand() % 2]
		};
		m_Guards.push_back(new NPCManager{ new Guard{position, color } });
	}
}

void GuardManager::Draw(int index)
{
	m_Guards[index]->Draw();
}

int GuardManager::AmountOfGuards()
{
	return m_Guards.size();
}

Point2f GuardManager::GetGuardPosition(int index)
{
	return m_Guards[index]->GetCharacterPtr()->GetPosition();
}
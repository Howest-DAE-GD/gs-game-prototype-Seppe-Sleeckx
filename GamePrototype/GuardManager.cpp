#include "pch.h"
#include "GuardManager.h"

GuardManager::GuardManager(int amountOfGuards, Character* target) :
	m_Target{ target }
{
	for (size_t i = 0; i < amountOfGuards; i++)
	{
		Point2f position{
			(float)(rand() % 1900 + 50),
			(float)(rand() % 900 + 50)
		};
		if ((position - target->GetPosition()).Length() < 120)
		{
			position.x += 120;
		}
		Color4f color{
			GuardColors[rand() % 3]
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
	for (size_t i = 0; i < m_Guards.size(); i++)
	{
		m_Guards[i]->Update(elapsedSec,mapVertices);
		if (static_cast<Guard*>(m_Guards[i]->GetCharacterPtr())->SpotTarget(m_Target->m_Color,m_Target->GetPosition(),mapVertices))
		{
			return true;
		}
	}
	return false;
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

void GuardManager::AddGuards(int amount, Color4f& color)
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
		Color4f guardColor{
			GuardColors[rand() % 3]
		};
		if (color != Color4f{ 1.f,0.5f,0.f,1.f })
		{
			while (guardColor == color)
			{
				guardColor = GuardColors[rand() % 3];
			}
		}
		Guard* guard{ new Guard{position, guardColor } };
		m_Guards.push_back(new NPCManager{ guard });
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

void GuardManager::RemoveGuards(std::vector<int> guards)
{
	if (guards.size()>0)
	{
		for (size_t i = 0; i < guards.size(); i++)
		{
			delete m_Guards[guards[i]];
			m_Guards.erase(m_Guards.begin() + guards[i]);
		}
	}
}
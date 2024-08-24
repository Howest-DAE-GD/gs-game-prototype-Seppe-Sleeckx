#include "pch.h"
#include "PlayerManager.h"
#include "InputManager.h"
#include "Bullet.h"
#include "OrbIndicator.h"
#include "Guard.h"

PlayerManager::PlayerManager(InputManager* pInputManager, Character* pCharacter, const Rectf& viewport) :
	m_pCharacter{ pCharacter },
	m_pInputManager{ pInputManager },
	m_pBullet{ nullptr },
	m_pOrbIndicator{ new OrbIndicator{Point2f{viewport.width / 2.f - m_pCharacter->GetModelRect().width/2, viewport.height / 2.f - m_pCharacter->GetModelRect().height / 2}}}
{

}

PlayerManager::~PlayerManager()
{
	delete m_pCharacter;
	delete m_pInputManager; 
	if (m_pBullet != nullptr)
	{
		delete m_pBullet;
	}
}

void PlayerManager::Update(const float elapsedSec, std::vector<Character*> enemies, const std::vector<std::vector<Point2f>>& mapVertices, Point2f cameraPosition, const Rectf& viewPort)
{
	Vector2f playerDirection = Vector2f{ 0,0 };
	if (m_pInputManager->IsKeyActive(SDL_SCANCODE_A))
	{
		playerDirection.x -= 1.f;
	}
	if (m_pInputManager->IsKeyActive(SDL_SCANCODE_D))
	{
		playerDirection.x += 1.f;
	}
	if (m_pInputManager->IsKeyActive(SDL_SCANCODE_W))
	{
		playerDirection.y += 1.f;
	}
	if (m_pInputManager->IsKeyActive(SDL_SCANCODE_S))
	{
		playerDirection.y -= 1.f;
	}
	m_pCharacter->ChangeDirection(playerDirection);
	if (m_pBullet != nullptr)
	{
		Character* pHitCharacter= m_pBullet->Update(elapsedSec, enemies);
		if (pHitCharacter != nullptr)
		{
			ChangeCharacter(pHitCharacter);
			for (size_t i = 0; i < enemies.size(); i++)
			{
				if (enemies[i]->m_Color ==m_pCharacter->m_Color)
				{
					static_cast<Guard*> (enemies[i])->m_VisionConeVisibility = false;
				}
				else
				{
					static_cast<Guard*> (enemies[i])->m_VisionConeVisibility = true;
				}
			}
		}
		else if (m_pBullet->GetDeathTimer() > 3.f)
		{
			delete m_pBullet;
			m_pBullet = nullptr;
		}

	}
	else if (m_pInputManager->IsMouseButtonPressed(InputManager::MouseButtonName::LEFT_CLICK))
	{
		Vector2f direction{
				m_pInputManager->GetMousePosition().x - viewPort.width / 2,
				m_pInputManager->GetMousePosition().y - viewPort.height / 2
		};

		m_pBullet = new Bullet(m_pCharacter->GetPosition(), direction.Normalized());
	}
	m_pCharacter->Update(elapsedSec, mapVertices);
	m_pInputManager->Update(elapsedSec);
	m_pOrbIndicator->UpdateAngle(GetPosition());
}

void PlayerManager::Draw()
{
	m_pCharacter->Draw();
	if (m_pBullet != nullptr)
	{
		m_pBullet->Draw();
	}
}

void PlayerManager::DrawOrbIndicator()
{
	m_pOrbIndicator->Draw();
}

void PlayerManager::ChangeCharacter(Character* pCharacter)
{
	Point2f oldPos = m_pCharacter->GetPosition();
	m_pCharacter->SetPosition(pCharacter->GetPosition());
	pCharacter->SetPosition(oldPos);
	m_pCharacter->m_Color = pCharacter->m_Color;
	Vector2f oldDirection = m_pCharacter->GetDirection();
	m_pCharacter->ChangeDirection(pCharacter->GetDirection());
	pCharacter->ChangeDirection(oldDirection);
	delete m_pBullet;
	m_pBullet = nullptr;
}

Point2f PlayerManager::GetPosition()
{
	return m_pCharacter->GetPosition();
}

void PlayerManager::AssignNewTarget(Orb* target)
{
	m_pOrbIndicator->AssignNewTarget(target);
}

void PlayerManager::ProcessMouseDownEvent(const Uint8 mouseIndex)
{
	m_pInputManager->ProcessMouseDownEvent(mouseIndex);
}

void PlayerManager::ProcessMouseUpEvent(const Uint8 mouseIndex)
{
	m_pInputManager->ProcessMouseUpEvent(mouseIndex);
}

void PlayerManager::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_pInputManager->ProcessMouseMotionEvent(e);
}

void PlayerManager::ProcessKeyDownEvent(const SDL_Scancode scancode)
{
	m_pInputManager->ProcessKeyDownEvent(scancode);
}

void PlayerManager::ProcessKeyUpEvent(const SDL_Scancode scancode)
{
	m_pInputManager->ProcessKeyUpEvent(scancode);
}

Character* PlayerManager::GetCharacterPtr()
{
	return m_pCharacter;
}
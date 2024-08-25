#include "pch.h"
#include "PlayerManager.h"
#include "InputManager.h"
#include "Bullet.h"
#include "OrbIndicator.h"
#include "Guard.h"
#include "UI_element.h"
#include "Bomb.h"
#include "UI_element_2.h"

PlayerManager::PlayerManager(InputManager* pInputManager, Character* pCharacter, const Rectf& viewport) :
	m_pCharacter{ pCharacter },
	m_pInputManager{ pInputManager },
	m_pBullet{ nullptr },
	m_pBomb{nullptr},
	m_pOrbIndicator{ new OrbIndicator{Point2f{viewport.width / 2.f - m_pCharacter->GetModelRect().width/2, viewport.height / 2.f - m_pCharacter->GetModelRect().height / 2}}},
	m_pBulletUi{new UI_element{1.5f, "UI_swap_0.jpg"}},
	m_pBombUi{new UI_element_2{10.f, "UI_Bomb_0.jpg"}}
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

std::vector<int> PlayerManager::Update(const float elapsedSec, std::vector<Character*> enemies, const std::vector<std::vector<Point2f>>& mapVertices, Point2f cameraPosition, const Rectf& viewPort)
{
	if (m_BombTimer > 0.f)
	{
		m_BombTimer -= elapsedSec;
	}
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
		Character* pHitCharacter= m_pBullet->Update(elapsedSec, enemies, mapVertices);
		if (pHitCharacter != nullptr)
		{
			ChangeCharacter(pHitCharacter);
			for (size_t i = 0; i < enemies.size(); i++)
			{
				if (enemies[i]->m_Color ==m_pCharacter->m_Color)
				{
					static_cast<Guard*>(enemies[i])->m_VisionConeVisibility = false;
				}
				else
				{
					static_cast<Guard*>(enemies[i])->m_VisionConeVisibility = true;
				}
			}
		}
		else if (m_pBullet->GetDeathTimer() > 1.5f)
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
		m_pBulletUi->RestartTimer();
	}
	std::vector<int> hitCharacters{};
	if (m_pBomb != nullptr)
	{
		hitCharacters = m_pBomb->Update(elapsedSec, enemies, mapVertices);
		if (m_pBomb->IsExploded())
		{
			delete m_pBomb;
			m_pBomb = nullptr;
			m_BombTimer = m_BombCooldown;
		}
	}
	else if (m_pInputManager->IsMouseButtonPressed(InputManager::MouseButtonName::RIGHT_CLICK) && m_BombTimer <= 0.f)
	{
		Vector2f direction{
				m_pInputManager->GetMousePosition().x - viewPort.width / 2,
				m_pInputManager->GetMousePosition().y - viewPort.height / 2
		};

		m_pBomb = new Bomb(m_pCharacter->GetPosition(), direction.Normalized());
		m_pBombUi->RestartTimer();
	}
	m_pCharacter->Update(elapsedSec, mapVertices);
	m_pInputManager->Update(elapsedSec);
	m_pOrbIndicator->UpdateAngle(GetPosition());
	m_pBulletUi->Update(elapsedSec);
	m_pBombUi->Update(elapsedSec);
	return hitCharacters;
}

void PlayerManager::Draw()
{
	m_pCharacter->Draw();
	if (m_pBullet != nullptr)
	{
		m_pBullet->Draw();
	}
	if (m_pBomb != nullptr)
	{
		m_pBomb->Draw();
	}
}

void PlayerManager::DrawUI()
{
	m_pBulletUi->Draw();
	m_pBombUi->Draw();
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
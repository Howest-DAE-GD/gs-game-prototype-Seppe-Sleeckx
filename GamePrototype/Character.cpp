#include "pch.h"
#include "Character.h"
#include "utils.h"
#include "KeyboardManager.h"

using namespace utils;

Character::Character(Point2f startpos, Color4f color, float speed) :
	m_Position{ startpos },
	m_Color{ color },
	m_Model{ Rectf{-5.f, -5.f, 10.f, 10.f } },
	m_MovingVector{},
	m_Speed{speed}
{

}

void Character::Move()
{
	m_Position += m_MovingVector;
}

void Character::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		SetColor(m_Color);
		DrawRect(m_Model);
	}
	glPopMatrix();
}

void Character::Update(float elapsedSec)
{
	m_MovingVector = Vector2f{ 0,0 };
	if (KeyboardManager::IsKeyActive(SDL_SCANCODE_A))
	{
		m_MovingVector.x -= m_Speed;
	}
	if (KeyboardManager::IsKeyActive(SDL_SCANCODE_D))
	{
		m_MovingVector.x += m_Speed;
	}
	if (KeyboardManager::IsKeyActive(SDL_SCANCODE_W))
	{
		m_MovingVector.y += m_Speed;
	}
	if (KeyboardManager::IsKeyActive(SDL_SCANCODE_S))
	{
		m_MovingVector.y -= m_Speed;
	}
	m_MovingVector *= elapsedSec;
	Move();
}
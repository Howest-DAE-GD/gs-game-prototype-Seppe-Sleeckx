#include "pch.h"
#include "MouseManager.h"

void MouseManager::Update(const float elapsedSec)
{
	for (size_t p = 0; p < m_MouseButtonQueue.size(); p++)
	{
		m_MouseButtonQueue[p].SecondsPressed += elapsedSec;
		if (m_MouseButtonQueue[p].SecondsPressed >= m_PressedMouseButtonThreshold)
		{
			m_HeldMouseButtons.push_back(m_MouseButtonQueue[p].MouseIndex);
			m_MouseButtonQueue.erase(m_MouseButtonQueue.begin() + p);
		}
	}
	m_PressedMouseButtons.clear();
}

void MouseManager::ProcessMouseDownEvent(const Uint8 mouseIndex)
{
	bool isActive{ IsMouseButtonActive(mouseIndex) };
	if (!isActive)
	{
		MouseButton k{ mouseIndex };
		m_MouseButtonQueue.push_back(k);
		m_PressedMouseButtons.push_back(mouseIndex);
	}
}

void MouseManager::ProcessMouseUpEvent(const Uint8 mouseIndex)
{
	for (size_t i = 0; i < m_HeldMouseButtons.size(); i++)
	{
		if (m_HeldMouseButtons[i] == mouseIndex)
		{
			m_HeldMouseButtons.erase(m_HeldMouseButtons.begin() + i);
		}
	}
	for (size_t p = 0; p < m_MouseButtonQueue.size(); p++)
	{
		if (m_MouseButtonQueue[p].MouseIndex == mouseIndex)
		{
			m_MouseButtonQueue.erase(m_MouseButtonQueue.begin() + p);
		}
	}
}

void MouseManager::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_MousePosition = Point2f{ (float)e.x, (float)e.y };
}

bool MouseManager::IsMouseButtonHeld(const Uint8 mouseIndex)
{
	for (size_t i = 0; i < m_HeldMouseButtons.size(); i++)
	{
		if (m_HeldMouseButtons[i] == mouseIndex)
		{
			return true;
		}
	}
	return false;
}

bool MouseManager::IsMouseButtonActive(const Uint8 mouseIndex)
{
	for (size_t i = 0; i < m_MouseButtonQueue.size(); i++)
	{
		if (m_MouseButtonQueue[i].MouseIndex == mouseIndex)
		{
			return true;
		}
	}
	return false;
}

bool MouseManager::IsMouseButtonPressed(const Uint8 mouseIndex)
{
	for (size_t i = 0; i < m_PressedMouseButtons.size(); i++)
	{
		if (m_PressedMouseButtons[i] == mouseIndex)
		{
			return true;
		}
	}
	return false;
}

bool MouseManager::IsMouseButtonInQueue(const Uint8 mouseIndex)
{
	if (IsMouseButtonHeld(mouseIndex) || IsMouseButtonInQueue(mouseIndex))
	{
		return true;
	}
	return false;
}

Point2f MouseManager::GetMousePosition()
{
	return m_MousePosition;
}
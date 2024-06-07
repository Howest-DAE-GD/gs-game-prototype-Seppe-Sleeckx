#include "pch.h"
#include "KeyboardManager.h"

void KeyboardManager::Update(const float elapsedSec)
{
	for (size_t p = 0; p < m_KeyQueue.size(); p++)
	{
		m_KeyQueue[p].SecondsPressed += elapsedSec;
		if (m_KeyQueue[p].SecondsPressed >= m_PressedKeyThreshold)
		{
			m_HeldKeys.push_back(m_KeyQueue[p].ScanCode);
			m_KeyQueue.erase(m_KeyQueue.begin() + p);
		}
	}
	m_PressedKeys.clear();
}

void KeyboardManager::ProcessKeyDownEvent(const SDL_Scancode scancode)
{
	bool isActive{ IsKeyActive(scancode)};
	if (!isActive)
	{
		KeyboardKey k{ scancode };
		m_KeyQueue.push_back(k); 
		m_PressedKeys.push_back(scancode);
	}
}

void KeyboardManager::ProcesskeyUpEvent(const SDL_Scancode scancode)
{
	for (size_t i = 0; i < m_HeldKeys.size(); i++)
	{
		if (m_HeldKeys[i] == scancode)
		{
			m_HeldKeys.erase(m_HeldKeys.begin() + i);
		}
	}
	for (size_t p = 0; p < m_KeyQueue.size(); p++)
	{
		if (m_KeyQueue[p].ScanCode == scancode)
		{
			m_KeyQueue.erase(m_KeyQueue.begin() + p);
		}
	}
}

bool KeyboardManager::IsKeyHeld(const SDL_Scancode scancode)
{
	for (size_t i = 0; i < m_HeldKeys.size(); i++)
	{
		if (m_HeldKeys[i] == scancode)
		{
			return true;
		}
	}
	return false;
}

bool KeyboardManager::IsKeyInQueue(const SDL_Scancode scancode)
{
	for (size_t i = 0; i < m_KeyQueue.size(); i++)
	{
		if (m_KeyQueue[i].ScanCode == scancode)
		{
			return true;
		}
	}
	return false;
}

bool KeyboardManager::IsKeyPressed(const SDL_Scancode scancode)
{
	for (size_t i = 0; i < m_PressedKeys.size(); i++)
	{
		if (m_PressedKeys[i] == scancode)
		{
			return true;
		}
	}
	return false;
}

bool KeyboardManager::IsKeyActive(const SDL_Scancode scancode)
{
	if (IsKeyHeld(scancode) || IsKeyInQueue(scancode))
	{
		return true;
	}
	return false;
}

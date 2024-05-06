#include "pch.h"
#include "KeyboardManager.h"

const float KeyboardManager::PressedThreshold{0.2f};
std::vector<SDL_Scancode> KeyboardManager::m_HeldKeys{};
std::vector<KeyboardKey> KeyboardManager::m_PressedKeys{};

void KeyboardManager::Update(float elapsedSec)
{
	for (size_t p = 0; p < m_PressedKeys.size(); p++)
	{
		m_PressedKeys[p].SecondsPressed += elapsedSec;
		if (m_PressedKeys[p].SecondsPressed >= PressedThreshold)
		{
			m_HeldKeys.push_back(m_PressedKeys[p].ScanCode);
			m_PressedKeys.erase(m_PressedKeys.begin() + p);
		}
	}
}

void KeyboardManager::ProcessKeyDownEvent(SDL_Scancode scanCode)
{
	bool isActive{ false };
	for (size_t i = 0; i < m_PressedKeys.size(); i++)
	{
		if (m_PressedKeys[i].ScanCode == scanCode)
		{
			isActive = true;
		}
	}
	for (size_t i = 0; i < m_HeldKeys.size(); i++)
	{
		if (m_HeldKeys[i] == scanCode)
		{
			isActive = true;
		}
	}
	if (!isActive)
	{
		KeyboardKey k{ scanCode };
		m_PressedKeys.push_back(k);
	}

}

void KeyboardManager::ProcessKeyUpEvent(SDL_Scancode scanCode)
{
	for (size_t i = 0; i < m_PressedKeys.size(); i++)
	{
		if (m_PressedKeys[i].ScanCode == scanCode)
		{
			m_PressedKeys.erase(m_PressedKeys.begin() + i);
			return;
		}
	}
	for (size_t h = 0; h < m_HeldKeys.size(); h++)
	{
		if (m_HeldKeys[h] == scanCode)
		{
			m_HeldKeys.erase(m_HeldKeys.begin() + h);
			return;
		}
	}
}

bool KeyboardManager::IsKeyPressed(SDL_Scancode scanCode)
{
	for (size_t i = 0; i < m_PressedKeys.size(); i++)
	{
		if (m_PressedKeys[i].ScanCode == scanCode)
		{
			return true;
		}
	}
	return false;
}

bool KeyboardManager::IsKeyHeld(SDL_Scancode scanCode)
{
	for (size_t i = 0; i < m_HeldKeys.size(); i++)
	{
		if (m_HeldKeys[i] == scanCode)
		{
			return true;
		}
	}
	return false;
}

bool KeyboardManager::IsKeyActive(SDL_Scancode scanCode)
{
	if (IsKeyHeld(scanCode) || IsKeyPressed(scanCode))
	{
		return true;
	}
	return false;
}

std::vector<SDL_Scancode>& KeyboardManager::GetHeldKeys()
{
	return m_HeldKeys;
}

std::vector<SDL_Scancode>& KeyboardManager::GetPressedKeys()
{
	std::vector<SDL_Scancode> returnList{};
	for (size_t i = 0; i < m_PressedKeys.size(); i++)
	{
		returnList.push_back(m_PressedKeys[i].ScanCode);
	}
	return returnList;
}

std::vector<SDL_Scancode>& KeyboardManager::GetActiveKeys()
{
	std::vector<SDL_Scancode>& returnList{ m_HeldKeys };
	for (size_t i = 0; i < m_PressedKeys.size(); i++)
	{
		returnList.push_back(m_PressedKeys[i].ScanCode);
	}
	return returnList;
}
#pragma once
#include "KeyboardKey.h"
#include <vector>

class KeyboardManager final
{
public:
	void Update(const float elapsedSec);
	void ProcessKeyDownEvent(const SDL_Scancode scancode);
	void ProcesskeyUpEvent(const SDL_Scancode scancode);

	bool IsKeyHeld(const SDL_Scancode scancode);
	bool IsKeyActive(const SDL_Scancode scancode);
	bool IsKeyPressed(const SDL_Scancode scancode);

private:
	bool IsKeyInQueue(const SDL_Scancode scancode);

	//Keyboard
	const float m_PressedKeyThreshold{ 0.2f };
	std::vector<KeyboardKey> m_KeyQueue{};
	std::vector<SDL_Scancode> m_HeldKeys{};
	std::vector<SDL_Scancode> m_PressedKeys{};
};


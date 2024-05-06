#pragma once
#include <vector>
#include "KeyboardKey.h"
static class KeyboardManager
{
	//verander in een namespace met static variables wnr tijd over
public:
	static void Update(float elapsedSec);
	static void ProcessKeyDownEvent(SDL_Scancode scanCode);
	static void ProcessKeyUpEvent(SDL_Scancode scanCode);
	static bool IsKeyPressed(SDL_Scancode scanCode);
	static bool IsKeyHeld(SDL_Scancode scanCode);
	static bool IsKeyActive(SDL_Scancode scanCode);
	static std::vector<SDL_Scancode>& GetHeldKeys();
	static std::vector<SDL_Scancode>& GetPressedKeys();
	static std::vector<SDL_Scancode>& GetActiveKeys();
private:
	static const float PressedThreshold;
	static std::vector<KeyboardKey> m_PressedKeys;
	static std::vector<SDL_Scancode> m_HeldKeys;
};


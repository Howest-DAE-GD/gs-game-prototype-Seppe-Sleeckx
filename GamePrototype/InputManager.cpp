#include "pch.h"
#include "InputManager.h"
#include "KeyboardManager.h"
#include "MouseManager.h"

InputManager::InputManager() :
	m_pKeyboardManager{ new KeyboardManager{} },
	m_pMouseManager{ new MouseManager{} }
{

}

InputManager::~InputManager()
{
	delete m_pKeyboardManager;
	delete m_pMouseManager;
}

void InputManager::Update(const float elapsedSec)
{
	m_pKeyboardManager->Update(elapsedSec);
	m_pMouseManager->Update(elapsedSec);
}

#pragma region keyboardFunctionality
void InputManager::ProcessKeyDownEvent(const SDL_Scancode scancode)
{
	m_pKeyboardManager->ProcessKeyDownEvent(scancode);
}

void InputManager::ProcessKeyUpEvent(const SDL_Scancode scancode)
{
	m_pKeyboardManager->ProcesskeyUpEvent(scancode);
}

bool InputManager::IsKeyHeld(const SDL_Scancode scancode)
{
	return m_pKeyboardManager->IsKeyHeld(scancode);
}

bool InputManager::IsKeyActive(const SDL_Scancode scancode)
{
	return m_pKeyboardManager->IsKeyActive(scancode);
}

bool InputManager::IsKeyPressed(const SDL_Scancode scancode)
{
	return m_pKeyboardManager->IsKeyPressed(scancode);
}
#pragma endregion

#pragma region MouseFunctionality
void InputManager::ProcessMouseDownEvent(const Uint8 mouseIndex)
{
	m_pMouseManager->ProcessMouseDownEvent(mouseIndex);
}

void InputManager::ProcessMouseDownEvent(const MouseButtonName mouseButton)
{
	ProcessMouseDownEvent(static_cast<int>(mouseButton));
}

void InputManager::ProcessMouseUpEvent(const Uint8 mouseIndex)
{
	m_pMouseManager->ProcessMouseUpEvent(mouseIndex);
}

void InputManager::ProcessMouseUpEvent(const MouseButtonName mouseButton)
{
	ProcessMouseUpEvent(static_cast<int>(mouseButton));
}

void InputManager::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_pMouseManager->ProcessMouseMotionEvent(e);
}

bool InputManager::IsMouseButtonHeld(const Uint8 mouseIndex)
{
	return m_pMouseManager->IsMouseButtonHeld(mouseIndex);
}

bool InputManager::IsMouseButtonHeld(const MouseButtonName mouseButton)
{
	return IsMouseButtonHeld(static_cast<Uint8>(mouseButton));
}

bool InputManager::IsMouseButtonActive(const Uint8 mouseIndex)
{
	return m_pMouseManager->IsMouseButtonActive(mouseIndex);
}

bool InputManager::IsMouseButtonActive(const MouseButtonName mouseButton)
{
	return IsMouseButtonActive(static_cast<Uint8>(mouseButton));
}

bool InputManager::IsMouseButtonPressed(const Uint8 mouseIndex)
{
	return m_pMouseManager->IsMouseButtonPressed(mouseIndex);
}

bool InputManager::IsMouseButtonPressed(const MouseButtonName mouseButton)
{
	return IsMouseButtonPressed(static_cast<Uint8>(mouseButton));
}

Point2f InputManager::GetMousePosition()
{
	return m_pMouseManager->GetMousePosition();
}
#pragma endregion
#pragma once
class KeyboardManager;
class MouseManager;

class InputManager
{
public:
	enum class MouseButtonName
	{
		//check game.cpp
		LEFT_CLICK = SDL_BUTTON_LEFT,
		RIGHT_CLICK = SDL_BUTTON_RIGHT,
		MIDDLE_CLICK = SDL_BUTTON_RIGHT
	};

	InputManager();
	~InputManager();

	void Update(const float elapsedSec);
	

	//Keyboard functionality
	void ProcessKeyDownEvent(const SDL_Scancode scancode);
	void ProcessKeyUpEvent(const SDL_Scancode scancode);
	bool IsKeyHeld(const SDL_Scancode scancode);
	bool IsKeyActive(const SDL_Scancode scancode);
	bool IsKeyPressed(const SDL_Scancode scancode);

	//Mouse functionality
	void ProcessMouseDownEvent(const Uint8 mouseIndex);
	void ProcessMouseDownEvent(const MouseButtonName mouseButton);
	void ProcessMouseUpEvent(const Uint8 mouseIndex);
	void ProcessMouseUpEvent(const MouseButtonName mouseButton);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	bool IsMouseButtonHeld(const Uint8 mouseIndex);
	bool IsMouseButtonHeld(const MouseButtonName mouseButton);
	bool IsMouseButtonActive(const Uint8 mouseIndex);
	bool IsMouseButtonActive(const MouseButtonName mouseButton);
	bool IsMouseButtonPressed(const Uint8 mouseIndex);
	bool IsMouseButtonPressed(const MouseButtonName mouseButton);
	Point2f GetMousePosition();


private:
	KeyboardManager* const m_pKeyboardManager;
	MouseManager* const m_pMouseManager;
};


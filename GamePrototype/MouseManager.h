#pragma once
#include <vector>
#include "MouseButton.h"

class MouseManager final
{
public:
	void Update(const float elapsedSec);

	void ProcessMouseDownEvent(const Uint8 mouseIndex);
	void ProcessMouseUpEvent(const Uint8 mouseIndex);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);

	bool IsMouseButtonHeld(const Uint8 mouseIndex);
	bool IsMouseButtonActive(const Uint8 mouseIndex);
	bool IsMouseButtonPressed(const Uint8 mouseIndex);
	Point2f GetMousePosition();

private:
	bool IsMouseButtonInQueue(const Uint8 mouseIndex);

	const float m_PressedMouseButtonThreshold{ 0.2f };
	std::vector<MouseButton> m_MouseButtonQueue{};
	std::vector<Uint8> m_HeldMouseButtons{};
	std::vector<Uint8> m_PressedMouseButtons{};
	Point2f m_MousePosition{};
};


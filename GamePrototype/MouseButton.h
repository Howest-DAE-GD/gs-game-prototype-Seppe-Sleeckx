#pragma once
#include "pch.h"
struct MouseButton
{
	explicit MouseButton(Uint8 mouseIndex) :
		MouseIndex{ mouseIndex },
		SecondsPressed{ 0 }
	{
	}
	Uint8 MouseIndex;
	float SecondsPressed;
};
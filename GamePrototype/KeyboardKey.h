#pragma once
#include <SDL_scancode.h>
struct KeyboardKey
{
	explicit KeyboardKey(SDL_Scancode keyCode):
		ScanCode{ keyCode },
		SecondsPressed{ 0 }
	{
	}

	SDL_Scancode ScanCode;
	float SecondsPressed;
};


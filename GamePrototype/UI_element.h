#pragma once
#include "pch.h"
#include "Texture.h"
class UI_element
{
public:
	UI_element(float cooldown, const std::string& texturePath);
	~UI_element();

	void Draw();
	void Update(float elapsedSec);
	void RestartTimer();
	void EndTimerPrematurely();

private:
	void CheckTexture();

	Texture* m_Texture;
	int m_TextureNumber;
	float m_Timer;
	const float m_Cooldown;
};


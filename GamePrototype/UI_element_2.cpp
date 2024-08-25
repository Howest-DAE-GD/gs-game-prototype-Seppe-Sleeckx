#include "pch.h"
#include "UI_element_2.h"

UI_element_2::UI_element_2(float cooldown, const std::string& texturePath) :
	m_Cooldown{ cooldown },
	m_Texture{ new Texture{texturePath} },
	m_TextureNumber{ 0 },
	m_Timer{ 0.f }
{

}

UI_element_2::~UI_element_2()
{
	delete m_Texture;
}

void UI_element_2::Draw()
{
	float scale{ 0.5f };
	glPushMatrix();
	{
		glScalef(scale, scale, 1.f);
		m_Texture->Draw(Point2f{ 1400.f, 10.f });
	}
	glPopMatrix();
}

void UI_element_2::Update(float elapsedSec)
{
	if (m_Timer > 0.f)
	{
		m_Timer -= elapsedSec;
		CheckTexture();
	}
}

void UI_element_2::RestartTimer()
{
	m_Timer = m_Cooldown;
}

void UI_element_2::EndTimerPrematurely()
{
	m_Timer = 0.f;
}

void UI_element_2::CheckTexture()
{
	int timerRounded{ (int)ceilf(m_Timer) };
	if (m_TextureNumber != timerRounded)
	{
		delete m_Texture;
		switch (timerRounded)
		{
		case 0:
			m_Texture = new Texture{ "UI_Bomb_0.jpg" };
			m_TextureNumber = 0;
			break;
		case 1:
			m_Texture = new Texture{ "UI_Bomb_1.jpg" };
			m_TextureNumber = 1;
			break;
		case 2:
			m_Texture = new Texture{ "UI_Bomb_2.jpg" };
			m_TextureNumber = 2;
			break;
		case 3:
			m_Texture = new Texture{ "UI_Bomb_3.jpg" };
			m_TextureNumber = 3;
			break;
		case 4:
			m_Texture = new Texture{ "UI_Bomb_4.jpg" };
			m_TextureNumber = 4;
			break;
		case 5:
			m_Texture = new Texture{ "UI_Bomb_5.jpg" };
			m_TextureNumber = 5;
			break;
		case 6:
			m_Texture = new Texture{ "UI_Bomb_6.jpg" };
			m_TextureNumber = 6;
			break;
		case 7:
			m_Texture = new Texture{ "UI_Bomb_7.jpg" };
			m_TextureNumber = 7;
			break;
		case 8:
			m_Texture = new Texture{ "UI_Bomb_8.jpg" };
			m_TextureNumber = 8;
			break;
		case 9:
			m_Texture = new Texture{ "UI_Bomb_9.jpg" };
			m_TextureNumber = 9;
			break;
		case 10:
			m_Texture = new Texture{ "UI_Bomb_10.jpg" };
			m_TextureNumber = 10;
			break;
		default:
			m_Texture = nullptr;
			break;
		}
	}
}

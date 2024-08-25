#include "pch.h"
#include "UI_element.h"

UI_element::UI_element(float cooldown, const std::string& texturePath) :
	m_Cooldown{cooldown},
	m_Texture{ new Texture{texturePath}},
	m_TextureNumber{0},
	m_Timer{ 0.f }
{
	
}

UI_element::~UI_element()
{
	delete m_Texture;
}

void UI_element::Draw()
{
	float scale{ 0.5f };
	glPushMatrix();
	{
		glScalef(scale, scale, 1.f);
		m_Texture->Draw(Point2f{ 1550.f, 10.f });
	}
	glPopMatrix();
}

void UI_element::Update(float elapsedSec)
{
	if (m_Timer > 0.f)
	{
		m_Timer -= elapsedSec;
		CheckTexture();
	}
}

void UI_element::RestartTimer()
{
	m_Timer = m_Cooldown;
}

void UI_element::EndTimerPrematurely()
{
	m_Timer = 0.f;
}

void UI_element::CheckTexture()
{
	int timerRounded{ (int)ceilf(m_Timer) };
	if (m_TextureNumber != timerRounded)
	{
		delete m_Texture;
		switch (timerRounded)
		{
		case 0:
			m_Texture = new Texture{ "UI_Swap_0.jpg" };
			m_TextureNumber = 0;
			break;
		case 1:
			m_Texture = new Texture{ "UI_Swap_1.jpg" };
			m_TextureNumber = 1;
			break;
		case 2:
			m_Texture = new Texture{ "UI_Swap_2.jpg" };
			m_TextureNumber = 2;
			break;
		case 3:
			m_Texture = new Texture{ "UI_Swap_3.jpg" };
			m_TextureNumber = 3;
			break;
		default:
			m_Texture = nullptr;
			break;
		}
	}
}

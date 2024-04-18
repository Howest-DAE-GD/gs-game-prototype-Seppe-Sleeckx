#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(const std::string& imagePath, const int frameWidth, const int frameHeight) :
	m_FrameWidth{ frameWidth },
	m_FrameHeight{ frameHeight }
{
	m_pTexture = new Texture(imagePath);
	m_pSrcRect = new Rectf(0, 0, (float)m_FrameWidth, (float)m_FrameHeight);
};

Sprite::~Sprite()
{
	delete m_pTexture;
}

void Sprite::Draw() const
{
	m_pTexture->Draw(Rectf{}, *m_pSrcRect);
}

bool Sprite::SetSrcRect(Rectf *srcRect)
{
	if (srcRect->width+srcRect->left <= m_pTexture->GetWidth())
	{
		delete m_pSrcRect;
		m_pSrcRect = srcRect;
		return true;
	}
	else
	{
		return false;
	}
}

bool Sprite::SetSrcRect(const Point2f pos)
{
	Rectf* rect = new Rectf(pos.x, pos.y, (float)m_FrameWidth, (float)m_FrameHeight);
	if (SetSrcRect(rect))
	{
		return true;
	}
	else
	{
		delete rect;
		return false;
	}

}
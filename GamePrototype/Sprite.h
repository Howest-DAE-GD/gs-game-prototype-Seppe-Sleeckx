#pragma once
#include <string>
class Texture;

class Sprite final
{
public:
	Sprite(const std::string& imagePath, const int frameWidth = 0, const int frameHeight = 0);
	~Sprite();

	void Draw() const;

	bool SetSrcRect(Rectf *srcRect);
	bool SetSrcRect(const Point2f pos);
private:
	Texture* m_pTexture;
	Rectf* m_pSrcRect;
	int	m_FrameWidth, m_FrameHeight;
};


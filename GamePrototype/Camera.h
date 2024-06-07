#pragma once
class Camera
{
public:
	Camera(const float screenWidth, const float screenHeight, const float zoom);
	~Camera();

	void Aim(const float levelWidth, const Point2f TrackedPos);
	void Reset();

	Point2f GetPosition();
	bool IsPointInCamera(Point2f pos);


private:
	const float m_ScreenHeight, m_ScreenWidth;
	const float m_Zoom;
	Point2f m_Position{};
};


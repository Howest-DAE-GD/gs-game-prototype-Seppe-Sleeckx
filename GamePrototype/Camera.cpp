#include "pch.h"
#include "Camera.h"
#include "utils.h"

#pragma region Constructor/Destructor
Camera::Camera(const float screenWidth, const float screenHeight, const float zoom) :
	m_ScreenHeight{ screenHeight },
	m_ScreenWidth{ screenWidth },
	m_Zoom{ zoom},
	m_Position{ 0,0 }
{

}

Camera::~Camera()
{

}
#pragma endregion

void Camera::Aim(const float levelWidth, const Point2f TrackedPos)
{
	m_Position.x = TrackedPos.x - (m_ScreenWidth/2) * m_Zoom;
	m_Position.y = TrackedPos.y - (m_ScreenHeight/2) * m_Zoom;
	glPushMatrix();
	glScalef(m_Zoom, m_Zoom, 1.f);
	glTranslatef(-m_Position.x, -m_Position.y, 0.f);
}

void Camera::Reset()
{
	glPopMatrix();
}

Point2f Camera::GetPosition()
{
	Point2f trackCenter{
		m_Position.x + (m_ScreenWidth / 2) * m_Zoom,
		m_Position.y + (m_ScreenHeight / 2) * m_Zoom
	};
	return trackCenter;
}

bool Camera::IsPointInCamera(Point2f pos)
{
	return utils::IsPointInRect(pos, Rectf{ m_Position.x, m_Position.y, m_ScreenWidth * m_Zoom, m_ScreenHeight * m_Zoom });
}
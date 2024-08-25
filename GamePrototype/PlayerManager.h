#pragma once
#include "Character.h"
class InputManager;
class Bullet;
class OrbIndicator;
class Orb;
class UI_element;
class Bomb;
class UI_element_2;

class PlayerManager
{
public:
	PlayerManager(InputManager* pInputManager, Character* pCharacter, const Rectf& viewport);
	~PlayerManager();

	std::vector<int> Update(const float elapsedSec, std::vector<Character*> enemies, const std::vector<std::vector<Point2f>>& mapVertices, Point2f cameraPosition, const Rectf& viewport);
	void Draw();
	void DrawUI();
	void DrawOrbIndicator();

	Point2f GetPosition();
	Character* GetCharacterPtr();
	void AssignNewTarget(Orb* target);

	void ProcessMouseDownEvent(const Uint8 mouseIndex);
	void ProcessMouseUpEvent(const Uint8 mouseIndex);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessKeyDownEvent(const SDL_Scancode scancode);
	void ProcessKeyUpEvent(const SDL_Scancode scancode);

private:
	void ChangeCharacter(Character* pCharacter);

	InputManager* m_pInputManager;
	Character* m_pCharacter;
	Bullet* m_pBullet;
	Bomb* m_pBomb;
	OrbIndicator* m_pOrbIndicator;
	UI_element* m_pBulletUi;
	UI_element_2* m_pBombUi;
	const float m_BombCooldown{ 20.f };
	float m_BombTimer;
};


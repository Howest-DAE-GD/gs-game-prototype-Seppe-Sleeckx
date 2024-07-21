#pragma once
#include "Character.h"
class InputManager;
class Bullet;
class OrbIndicator;
class Orb;

class PlayerManager
{
public:
	PlayerManager(InputManager* pInputManager, Character* pCharacter, const Rectf& viewport);
	~PlayerManager();

	void Update(const float elapsedSec, std::vector<Character*> enemies, const std::vector<std::vector<Point2f>>& mapVertices, Point2f cameraPosition, const Rectf& viewport);
	void Draw();
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
	OrbIndicator* m_pOrbIndicator;
};


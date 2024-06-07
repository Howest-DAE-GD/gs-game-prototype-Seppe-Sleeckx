#pragma once
#include "Character.h"
class InputManager;
class Bullet;

class PlayerManager
{
public:
	PlayerManager(InputManager* pInputManager, Character* pCharacter);
	~PlayerManager();

	void Update(const float elapsedSec, std::vector<Character*> enemies, const std::vector<std::vector<Point2f>>& mapVertices, Point2f cameraPosition, Rectf& viewport);
	void Draw();

	Point2f GetPosition();
	Character* GetCharacterPtr();

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
};


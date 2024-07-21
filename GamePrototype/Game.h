#pragma once
#include "BaseGame.h"
#include "Level.h"
#include "PlayerManager.h"
#include "GuardManager.h"
#include "Camera.h"
#include "Texture.h"
#include "Orb.h"
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;


private:
	PlayerManager* g_PlayerOne;
	GuardManager* g_GuardManager;
	Level* g_Level;
	Camera* g_Camera;
	Texture* g_GameOverImage{ nullptr };
	Texture* g_ScoreText{};
	float g_GameOverImageScale;
	bool g_GameOver{ false };
	Orb* g_Orb;
	double g_AccumulatedTimeInSeconds{0.f};
	int g_Score{ 0 };
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};
#include "pch.h"
#include "Game.h"
#include "Guard.h"
#include "KeyboardManager.h"
Game::Game(const Window& window)
	:BaseGame{ window },
	g_Guard{ new Guard{Point2f{300,300}}},
	g_Level{ new Level{} }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	++angle;
	KeyboardManager::Update(elapsedSec);
	g_Guard->ChangeDirection(angle);
	g_Guard->Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	g_Level->Draw();
	g_Guard->Draw();
	//glPushMatrix();
	//{
	//	glTranslatef(300, 300, 0.f);
	//	glRotatef(angle, 0.f, 0.f, 1.f);
	//	DrawPolygon(g_Cone);
	//}
	//glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	KeyboardManager::ProcessKeyDownEvent(e.keysym.scancode);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	KeyboardManager::ProcessKeyUpEvent(e.keysym.scancode);
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

#include "pch.h"
#include "Game.h"
#include "Guard.h"
#include "InputManager.h"
#include "VisionCone.h"

Game::Game(const Window& window)
	:BaseGame{ window },
	g_Level{ new Level{} },
	g_Camera{ new Camera{GetViewPort().width, GetViewPort().height, 1.f} },
	g_Orb{ new Orb{} },
	g_PlayerOne{ new PlayerManager{new InputManager{}, new Character{ Point2f{1000,500}, Color4f{1.f,1.f,0.f,1.f} },GetViewPort()}},
	g_GuardManager{ new GuardManager{ 10, g_PlayerOne->GetCharacterPtr()} },
	g_ScoreText{ new Texture("0", "Font.ttf", 40, Color4f{1.f,0.5f,0.f,1.f}) }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	g_PlayerOne->AssignNewTarget(g_Orb);
}

void Game::Cleanup()
{
	delete g_PlayerOne;
	delete g_Level;
	delete g_GuardManager;
	delete g_Camera;
	delete g_GameOverImage;
	delete g_ScoreText;
	delete g_Orb;
}

void Game::Update(float elapsedSec)
{
	g_GameOver = g_GuardManager->Update(elapsedSec, g_Level->m_Vertices);
	std::vector<Character*> enemies{ g_GuardManager->GetGuardPtrs() };
	g_PlayerOne->Update(elapsedSec, enemies, g_Level->m_Vertices, g_Camera->GetPosition(), const_cast<Rectf&>(GetViewPort()));
	if (g_GameOver && g_GameOverImage == nullptr)
	{
		g_GameOverImage = new Texture{ "funny_cat_meme.jpg" };
		g_GameOverImageScale = GetViewPort().width / g_GameOverImage->GetWidth();
	}
	g_AccumulatedTimeInSeconds += elapsedSec;
	if (g_AccumulatedTimeInSeconds > 10.f)
	{
		g_GuardManager->AddGuards(2);
		g_AccumulatedTimeInSeconds = 0.f;
	}
	if (g_Orb->CheckHit(g_PlayerOne->GetCharacterPtr()))
	{
		++g_Score;
		delete g_ScoreText;
		g_ScoreText = new Texture(std::to_string(g_Score), "Font.ttf", 40, Color4f{ 1.f,0.5f,0.f,1.f });
		g_Orb->SetNewPosition();
	}
}

void Game::Draw() const
{
	ClearBackground();
	g_Camera->Aim(GetViewPort().width, g_PlayerOne->GetPosition());
	{
		g_Level->Draw();
		g_PlayerOne->Draw();
		for (size_t i = 0; i < g_GuardManager->AmountOfGuards(); i++)
		{
			if (g_Camera->IsPointInCamera(g_GuardManager->GetGuardPosition(i)))
			{
				g_GuardManager->Draw(i);
			}
		}
		g_Orb->Draw();
	}
	g_Camera->Reset();
	g_PlayerOne->DrawOrbIndicator();
	if (g_GameOverImage != nullptr)
	{
		glPushMatrix();
		{
			glScalef(g_GameOverImageScale, g_GameOverImageScale, 1.f);
			g_GameOverImage->Draw();
		}
		glPopMatrix();
	}

	Point2f textPos{
		0.f,
		GetViewPort().height - g_ScoreText->GetHeight()
	};
	g_ScoreText->Draw(textPos);

}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	g_PlayerOne->ProcessKeyDownEvent(e.keysym.scancode);
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	g_PlayerOne->ProcessKeyUpEvent(e.keysym.scancode);
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	g_PlayerOne->ProcessMouseMotionEvent(e);
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	g_PlayerOne->ProcessMouseDownEvent(e.button);
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	g_PlayerOne->ProcessMouseUpEvent(e.button);
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

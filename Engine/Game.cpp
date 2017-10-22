/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	xDist(0, 35),
	yDist(0, 25),
	brd(gfx),
	DELTA_RIGHT(1, 0),
	DELTA_LEFT(-1, 0),
	DELTA_DOWN(0, 1),
	DELTA_UP(0, -1),
	deltaAdj(0, -1),
	goalLoc(xDist(rng), yDist(rng)),
	goal(goalLoc),
	scoreHome(105,0),
	highScoreHome(550,0)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (gameState == GameState::TitleScreen) // Title section.
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) // Press <ENTER> to start.
		{
			gameState = GameState::CountDown;
		}
	}
	else if (gameState == GameState::CountDown) // Countdown to start.
	{
		if (countdown) // Still time left on countdown.
		{
			--countdown;
		}
		else
		{
			gameState = GameState::PlayingGame;
		}
	}
	else if (gameState == GameState::PlayingGame) // Play Game section.
	{
		if (allowInput)
		{
			if (wnd.kbd.KeyIsPressed(VK_RIGHT)) // Right Arrow.
			{
				if (deltaAdj != DELTA_LEFT)
				{
					deltaAdj = DELTA_RIGHT;
					allowInput = false;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT)) // Left Arrow.
			{
				if (deltaAdj != DELTA_RIGHT)
				{
					deltaAdj = DELTA_LEFT;
					allowInput = false;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN)) // Down Arrow.
			{
				if (deltaAdj != DELTA_UP)
				{
					deltaAdj = DELTA_DOWN;
					allowInput = false;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_UP)) // Up Arrow.
			{
				if (deltaAdj != DELTA_DOWN)
				{
					deltaAdj = DELTA_UP;
					allowInput = false;
				}
			}
		}

		// Make move and test for collision.
		if (snake.MoveBy(deltaAdj, brd, allowInput)) // Found collision, end game.
		{
			gameState = GameState::GameOver;
		}

		// Check to see if snake ate goal.
		if (snake.AteGoal(goal))
		{
			// Score of Goal!
			score += goalPoints;
			if (score > highScore) { highScore = score; }
			++speedUp;
			if (speedUp >= goalsPerSpeedUp) // Increase speed on Goal every goalsPerSpeed goals.
			{
				speedUp = 0;
				snake.SpeedUp(1);
			}
			snake.Grow();
			goal.SetLoc(Location(xDist(rng), yDist(rng)));
		}
	}
	else if (gameState == GameState::GameOver) // Game Over.
	{
		if (wnd.kbd.KeyIsPressed('Y')) // Play again Y.
		{
			// Reset and make ready for next play.
			score = 0;
			speedUp = 0;
			countdown = maxCountdown;
			deltaAdj = DELTA_UP;
			snake.Reset();
			gameState = GameState::TitleScreen;
			goal.SetLoc(Location(xDist(rng), yDist(rng)));
		}
		else if (wnd.kbd.KeyIsPressed('N')) // End Game.
		{
			exit(0);
		}
	}
}

void Game::ComposeFrame()
{
	if (gameState == GameState::TitleScreen) // Display Title.
	{
		brd.DrawBoarder();
		SpriteCodex::DrawTitle(290, 225, gfx);
	}
	else if (gameState == GameState::CountDown) // Countdown to start.
	{
		brd.DrawBoarder();
		SpriteCodex::DrawTitle(290, 225, gfx);
		int clock = countdown / period;
		switch (clock)
		{
		case 0:
			gfx.Draw1(385, 155, scoreColor);
			break;
		case 1:
			gfx.Draw2(385, 155, scoreColor);
			break;
		case 2:
			gfx.Draw3(385, 155, scoreColor);
			break;
		default:
			break;
		}
	}
	else if (gameState == GameState::PlayingGame) // Play Game.
	{
		brd.DrawBoarder();
		goal.Draw(brd);
		snake.Draw(brd);
		gfx.DrawNumber(score, scoreHome, scoreColor);
		gfx.DrawNumber(highScore, highScoreHome, scoreColor);
		SpriteCodex::Score(20, 10, gfx);
		SpriteCodex::HighScore(400, 10, gfx);
	}
	else if (gameState == GameState::GameOver) // Game Over.
	{
		brd.DrawBoarder();
		snake.Draw(brd);
		gfx.DrawNumber(score, scoreHome, scoreColor);
		gfx.DrawNumber(highScore, highScoreHome, scoreColor);
		SpriteCodex::Score(20, 10, gfx);
		SpriteCodex::HighScore(400, 10, gfx);
		SpriteCodex::DrawGameOver(316, 251, gfx);
		SpriteCodex::PlayAgain(305, 439, gfx);
	}
}

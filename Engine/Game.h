/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include <random>
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"

enum class GameState
{
	TitleScreen,
	CountDown,
	PlayingGame,
	GameOver
};

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	Board brd;
	const Location DELTA_RIGHT;
	const Location DELTA_LEFT;
	const Location DELTA_DOWN;
	const Location DELTA_UP;
	Location deltaAdj;					// Current Delta to be applied.
	bool allowInput = true;
	Snake snake;
	GameState gameState = GameState::TitleScreen;
	static constexpr int maxCountdown = 150;
	int countdown = maxCountdown;		// Total # of frames to count.
	static constexpr int period = 50;
	bool hasWonGame = false;
	int score = 0;
	Color scoreColor = Colors::Cyan;
	Location goalLoc;
	Goal goal;
	static constexpr int goalPoints = 25;
	Location scoreHome;
	Location highScoreHome;
	int speedUp = 0;					// Control for moderation of Speed increase every goal.
	static constexpr int goalsPerSpeedUp = 4;
										// # of goals between speed up.
	int highScore = 0;					// Highest score of all games.
	/********************************/
};
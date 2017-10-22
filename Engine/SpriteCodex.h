#pragma once

#include "Graphics.h"

class SpriteCodex
{
public:
	static void DrawGameOver( int x,int y,Graphics& gfx );
	static void DrawTitle( int x,int y,Graphics& gfx );
	static void PlayAgain(int x, int y, Graphics& gfx);
	static void HighScore(int x, int y, Graphics& gfx);
	static void Score(int x, int y, Graphics& gfx);
};
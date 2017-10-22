#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics&);
	void DrawCell(const Location& loc, Color c);
	void DrawBoarder();
	int GetGridWidth() const;
	int GetGridHeight() const;
private:
	static constexpr int dimention = 20;
	static constexpr int width = 36;
	static constexpr int height = 26;
	static constexpr int padding = 40;
	static constexpr int brdWidth = 5;
	Graphics& gfx;
	Color bdrColor = Colors::Gray;
};
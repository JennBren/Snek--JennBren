#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfxRef)
	:
	gfx(gfxRef)
{
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(1 + padding + (loc.x * dimention), 1 + padding + (loc.y * dimention), dimention - 2, dimention - 2, c);
}


void Board::DrawBoarder()
{
	int loc = padding - brdWidth;
	int hLineWidth = (2 * brdWidth) + (width * dimention);
	int vLineHeight = (2 * brdWidth) + (height * dimention);

	gfx.DrawRectDim(loc, loc, hLineWidth, brdWidth, bdrColor);
	gfx.DrawRectDim(loc, padding + (height * dimention), hLineWidth, brdWidth, bdrColor);

	gfx.DrawRectDim(loc, loc, brdWidth, vLineHeight, bdrColor);
	gfx.DrawRectDim(padding + (width * dimention), loc, brdWidth, vLineHeight, bdrColor);
}


int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

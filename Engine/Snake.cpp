#include "Snake.h"

Snake::Snake()
	:
	snakeHome(19, 14)
{
	segments[0].InitHead(snakeHome);
	if (nSegments > 1)
	{
		for (int i = 1; i < nSegments; ++i)
		{
			Location south(0,1); // For Init, assume head north of tail.
			south.Add(segments[i - 1].GetLoc());
			segments[i].InitBody(south, i);
		}
	}
}

bool Snake::MoveBy(const Location& delta_loc, Board& brd, bool& allowInput)
{
	if (curFrame % nFramesPerMove) // Not a move frame, increment and return.
	{
		++curFrame;
		return false;
	}
	else
	{
		Location newLoc = segments[0].GetLoc();
		newLoc.Add(delta_loc);

			// Check for out of bounds.
		if (newLoc.x < 0 || newLoc.x >= brd.GetGridWidth()
			|| newLoc.y < 0 || newLoc.y >= brd.GetGridHeight())
		{
			return true;
		}
			// Check for collision of head on body.
		else
		{		// Don't check very last segment as it will be moving.
			for (int i = 1; i < nSegments - 1; ++i)
			{
				if (newLoc == segments[i].GetLoc()) return true;
			}
		}

		// All is well update position and move on. ^_^
		curFrame = 1;
		int adjust = -1;
		for (int i = nSegments - 1; i > 0; --i)
		{
			segments[i].Follow(segments[i - 1]);
		}
		segments[0].MoveBy(delta_loc);
		allowInput = true;
	}
	return false;
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody(segments[nSegments - 1].GetLoc(), nSegments);
		++nSegments;
	}
}

void Snake::Draw(Board & brd)
{
	if (nSegments > 1) // Mod to draw head last.
	{
		for (int i = 1; i < nSegments; ++i)
		{
			segments[i].Draw(brd);
		}
	}
	segments[0].Draw(brd);
}

void Snake::Reset()
{
	nFramesPerMove = startnFPM;
	nSegments = startSegments;
	segments[0].InitHead(snakeHome);
	if (nSegments > 1)
	{
		for (int i = 1; i < nSegments; ++i)
		{
			Location south(0, 1); // For Init, assume head north of tail.
			south.Add(segments[i - 1].GetLoc());
			segments[i].InitBody(south, i);
		}
	}
}

bool Snake::AteGoal(Goal& goal)
{
	if (goal.GetLoc() == segments[0].GetLoc()) return true;
	else return false;
}

int Snake::GetnFPM() const
{
	return nFramesPerMove;
}

void Snake::SpeedUp(int delta_inc)
{
	if (nFramesPerMove - delta_inc < maxSpeed) return;
	else { nFramesPerMove -= delta_inc; }
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(const Location& in_loc, int cIndex)
{
	loc = in_loc;
	Color segC = bodyColor;
	unsigned int green = segC.GetG();
	green = green - (((cIndex - 1) % segShades) * segShadeDif);
	segC.SetG(green);
	c = segC;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

Location Snake::Segment::GetLoc() const
{
	return loc;
}

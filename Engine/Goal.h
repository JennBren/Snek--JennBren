#pragma once

#include "Board.h"

class Goal
{
public:
	Goal(Location in_loc);
	Location GetLoc() const;
	void Draw(Board& brd);
	void SetLoc(Location in_loc);
private:
	Location loc;
	Color c;
	static constexpr int colorStep = 12;		// Amount to advance color each cycle.
	int colorIndex = 0;							// Index for color change over time.
};
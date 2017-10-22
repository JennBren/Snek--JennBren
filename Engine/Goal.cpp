#include "Goal.h"

Goal::Goal(Location in_loc)
{
	loc = in_loc;
}

Location Goal::GetLoc() const
{
	return loc;
}

void Goal::Draw(Board& brd)
{
	// Set Color
	colorIndex += colorStep;
	if (colorIndex >= 1536) { colorIndex = 0; }
	int index = colorIndex / 256;
	int cAdj = colorIndex % 256;
	switch (index)
	{
	case 0:
		c.SetG(cAdj);
		break;
	case 1:
		c.SetR(255 - cAdj);
		break;
	case 2:
		c.SetB(cAdj);
		break;
	case 3:
		c.SetG(255 - cAdj);
		break;
	case 4:
		c.SetR(cAdj);
		break;
	case 5:
		c.SetB(255 - cAdj);
		break;
	default:
		break;
	}

	// Draw box.
	brd.DrawCell(loc, c);
}

void Goal::SetLoc(Location in_loc)
{
	loc = in_loc;
}

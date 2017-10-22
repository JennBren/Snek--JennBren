#pragma once

class Location
{
public:
	Location()
	{
		x = 0;
		y = 0;
	}
	Location(int in_x, int in_y)
	{
		x = in_x;
		y = in_y;
	}
	bool Location::operator==(const Location& other)
	{
		if ((x == other.x) && (y == other.y)) return true;
		else return false;
	}
	bool Location::operator!=(const Location& other)
	{
		return !(*this == other);
	}
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}
	bool isOpposite(const Location& other)
	{
		if (x) // x is vector.
		{
			if (y == 0 && (-x == other.x)) return true;
			else return false;
		}
		else // x is 0 component.
		{
			if (-y == other.y) return true;
			else return false;
		}
	}

	int x;
	int y;
};
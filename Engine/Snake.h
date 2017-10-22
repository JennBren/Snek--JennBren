#pragma once

#include "Board.h"
#include "Goal.h"
#include <assert.h>

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(const Location& in_loc, int cIndex);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		Location GetLoc() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake();
	bool MoveBy(const Location& delta_loc, Board& brd, bool& allowInput);
	void Grow();
	void Draw(Board& brd);
	void Reset();
	bool AteGoal(Goal& goal);
	int GetnFPM() const;
	void SpeedUp(int delta_inc);
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	static constexpr int startSegments = 3;
	static constexpr int segShades = 4;
	static constexpr int segShadeDif = 35;
	static constexpr int maxSpeed = 2;
	const Location snakeHome;
	Segment segments[nSegmentsMax];
	int nSegments = startSegments;
	static constexpr int startnFPM = 12;
	int nFramesPerMove = startnFPM;
	int curFrame = 0;
};

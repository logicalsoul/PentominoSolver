#pragma once
#include "PentHand.h"

// •~‚«‹l‚ß–â‘è‚Ì”Õ–Ê
class PentField
{
public:
	PentField(int, int);
	~PentField();

	bool CanPut(PentHand, int) const;
	void Put(PentHand, int);
	void Remove(PentHand, int);

	bool IsOccupied(int pos) const { return square[pos].is_occupied; }
	int GetSize() const { return square_size; }

	std::string to_string() const;

private:
	const int Xrange, Yrange;
	const int square_size;
	struct Square
	{
		bool is_occupied;
		PentHand::Shape shape;
	};

	Square *square;

	inline bool IsOutOfRange(int pos) const { return pos < 0 || square_size <= pos; }
};


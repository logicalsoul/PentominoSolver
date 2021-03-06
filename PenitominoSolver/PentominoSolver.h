#pragma once
#include "PentHandList.h"
#include "PentField.h"

// Pentominoの敷き詰め問題を解く
class PentominoSolver
{
public:
	PentominoSolver(int, int);
	~PentominoSolver();

	int Solve();
private:
	static const int NumOfPentomino = 12;

	PentField *field;
	PentHandList *handlist;
	
	struct HandHistory
	{
		PentHand hand;
		int pos;
	};
	
	HandHistory history[NumOfPentomino];
};


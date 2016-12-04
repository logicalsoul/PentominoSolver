#pragma once
#include "PentHand.h"

// PentHandを管理するクラス
class PentHandList
{
public:
	PentHandList(int, int);
	~PentHandList();

	 bool Next(PentHand*);
	 void RemoveHand(PentHand p) { exists[p.GetShape()] = false; }
	 void AddHand(PentHand p) { exists[p.GetShape()] = true; }
	 void ResetCounter() { counter = 0; }

private:

	PentHand hands[480];	// とりあえず最大値で用意
	int NumOfHands;
	int counter;
	bool exists[PentHand::NumOfShapes];

	bool InHands(int, int, PentHand);
};


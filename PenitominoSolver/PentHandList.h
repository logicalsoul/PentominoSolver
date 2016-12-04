#pragma once
#include "PentHand.h"

// PentHandを管理するクラス
class PentHandList
{
public:
	PentHandList(int, int);
	~PentHandList();

	bool GetHand(int, PentHand*) const;
	void RemoveHand(PentHand p) { exists[p.GetShape()] = false; }
	void AddHand(PentHand p) { exists[p.GetShape()] = true; }

	int GetNumOfHands() const { return NumOfHands; }

private:

	PentHand hands[480];	// とりあえず最大値で用意
	int NumOfHands;
	bool exists[PentHand::NumOfShapes];

	bool InHands(int, int, PentHand);
};


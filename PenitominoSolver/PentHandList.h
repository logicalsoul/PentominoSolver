#pragma once
#include "PentHand.h"

// PentHand���Ǘ�����N���X
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

	PentHand hands[480];	// �Ƃ肠�����ő�l�ŗp��
	int NumOfHands;
	int counter;
	bool exists[PentHand::NumOfShapes];

	bool InHands(int, int, PentHand);
};

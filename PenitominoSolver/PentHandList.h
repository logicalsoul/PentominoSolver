#pragma once
#include "PentHand.h"

// PentHand���Ǘ�����N���X
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

	PentHand hands[480];	// �Ƃ肠�����ő�l�ŗp��
	int NumOfHands;
	bool exists[PentHand::NumOfShapes];

	bool InHands(int, int, PentHand);
};


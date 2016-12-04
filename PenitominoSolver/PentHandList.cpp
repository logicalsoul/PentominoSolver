#include "PentHandList.h"

// �ŏ��ɍl�����邷�ׂĂ̎�𐶐����āA����̂��̂�r���������X�g�����
PentHandList::PentHandList(int r, int d)
{
	int s, cnt, i, j, tmp;
	PentHand p;

	cnt = 0;
	for (s = 0; s < PentHand::NumOfShapes; s++)
	{
		exists[s] = true;

		int start = cnt;
		p.Set(r, d, (PentHand::Shape)s);

		// ��{�`�Ƃ���shift���Z�b�g
		hands[cnt++] = p;
		for (i = 0; i < PentHand::PentominoSize - 1; i++)
		{
			hands[cnt++] = p.Shift(i);
		}

		// ��]�`
		tmp = cnt;
		for (i = start; i < tmp; i++)
		{
			for (j = 1; j < 3; j++)		// ��]�p��90, 180. 270��3��
			{
				p = hands[i].Rotate(1);
				if (!InHands(start, cnt, p))
				{
					hands[cnt++] = p;
				}
			}
		}

		// ����
		tmp = cnt;
		for (i = start; i < tmp; i++)
		{
			p = hands[i].Mirror();
			if (!InHands(start, cnt, p))
			{
				hands[cnt++] = p;
			}
		}
	}
	NumOfHands = cnt;
	counter = 0;
}


PentHandList::~PentHandList()
{
}

// hands�z���start�Ԗڂ���end-1�Ԗڂ�p�Ɠ������̂����邩�ǂ�����Ԃ�
bool PentHandList::InHands(int start, int end, PentHand p)
{
	for (int i = start; i < end; i++)
	{
		if (hands[i] == p)
		{
			return true;
		}
	}
	return false;
}

// ���̎��Ԃ��B�߂�l�͕Ԃ��肪���邩�ǂ���
bool PentHandList::Next(PentHand *out_p)
{
	while (counter < NumOfHands && !exists[hands[counter].GetShape()])
	{
		counter++;
	}

	if (counter >= NumOfHands)
	{
		return false;
	}
	else
	{
		*out_p = hands[counter++];
		return true;
	}
}
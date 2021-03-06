#include "PentHandList.h"

// 最初に考えられるすべての手を生成して、同一のものを排除したリストを作る
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

		// 基本形とそのshiftをセット
		hands[cnt++] = p;
		for (i = 0; i < PentHand::PentominoSize - 1; i++)
		{
			hands[cnt++] = p.Shift(i);
		}

		// 回転形
		tmp = cnt;
		for (i = start; i < tmp; i++)
		{
			for (j = 1; j < 4; j++)		// 回転角は90, 180, 270の3つ
			{
				p = hands[i].Rotate(j);
				if (!InHands(start, cnt, p))
				{
					hands[cnt++] = p;
				}
			}
		}

		// 鏡像
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
}


PentHandList::~PentHandList()
{
}

// hands配列のstart番目からend-1番目にpと同じものがあるかどうかを返す
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

// 指定番目の次の手を返す。戻り値は返す手があるかどうか
bool PentHandList::GetHand(int num, PentHand *out_p) const
{
	if (num < NumOfHands && exists[hands[num].GetShape()])
	{
		*out_p = hands[num];
		return true;
	}
	else
	{
		return false;
	}
}
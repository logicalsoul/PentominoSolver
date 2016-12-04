#include "PentominoSolver.h"
#include <iostream>

PentominoSolver::PentominoSolver(int xrange, int yrange)
{
	field = new PentField(xrange, yrange);
	handlist = new PentHandList(1, xrange);
}


PentominoSolver::~PentominoSolver()
{
	delete field;
	delete handlist;
}

// 解をすべて標準出力に表示し、戻り値として解の個数を返す
int PentominoSolver::Solve()
{
	int ret = 0;
	int pos, depth;
	int hand_cnt[NumOfPentomino];
	PentHand p;
	bool is_hand, is_end;

	for (int i = 0; i < NumOfPentomino; i++)
	{
		hand_cnt[i] = 0;
	}

	depth = 0;
	while (true)
	{
		// 深度が最大に達していたら解に至ったということ
		if (depth == NumOfPentomino)
		{
			std::cout << field->to_string() << std::endl;	// 解を表示
			ret++;

			// 直前の手を元に戻す
			hand_cnt[depth] = 0;
			depth--;
			field->Remove(history[depth].hand, history[depth].pos);
			handlist->AddHand(history[depth].hand);
		}

		pos = 0;
		while (field->IsOccupied(pos))
		{
			pos++;
		}

		// 置ける手を探す
		is_hand = false;
		while (hand_cnt[depth] < handlist->GetNumOfHands())
		{
			if (handlist->GetHand(hand_cnt[depth]++, &p) && field->CanPut(p, pos))
			{
				is_hand = true;
				break;
			}
		}

		if (is_hand)
		{
			// 置ける手があった場合、それを置いて次の深度へ
			field->Put(p, pos);
			history[depth].hand = p;
			history[depth].pos = pos;
			handlist->RemoveHand(p);
			depth++;
		}
		else
		{
			
			// 最初の深度の最後の手を調べ終わったところで終了
			if (depth == 0 && hand_cnt[0] == handlist->GetNumOfHands())
			{
				return ret;
			}

			// 直前の手を取り消す
			hand_cnt[depth] = 0;
			depth--;
			field->Remove(history[depth].hand, history[depth].pos);
			handlist->AddHand(history[depth].hand);
		}
	}
}
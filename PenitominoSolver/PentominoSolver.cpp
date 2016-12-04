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

// �������ׂĕW���o�͂ɕ\�����A�߂�l�Ƃ��ĉ��̌���Ԃ�
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
		// �[�x���ő�ɒB���Ă�������Ɏ������Ƃ�������
		if (depth == NumOfPentomino)
		{
			std::cout << field->to_string() << std::endl;	// ����\��
			ret++;

			// ���O�̎�����ɖ߂�
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

		// �u������T��
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
			// �u����肪�������ꍇ�A�����u���Ď��̐[�x��
			field->Put(p, pos);
			history[depth].hand = p;
			history[depth].pos = pos;
			handlist->RemoveHand(p);
			depth++;
		}
		else
		{
			
			// �ŏ��̐[�x�̍Ō�̎�𒲂׏I������Ƃ���ŏI��
			if (depth == 0 && hand_cnt[0] == handlist->GetNumOfHands())
			{
				return ret;
			}

			// ���O�̎��������
			hand_cnt[depth] = 0;
			depth--;
			field->Remove(history[depth].hand, history[depth].pos);
			handlist->AddHand(history[depth].hand);
		}
	}
}
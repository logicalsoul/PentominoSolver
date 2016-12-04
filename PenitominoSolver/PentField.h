#pragma once
#include "PentHand.h"

/*
 * �~���l�ߖ��̔Ֆ�
 * �Ֆʂ�1�����z��ŕ\���B
 * n x m �̔Ֆʂł���΁A�T�C�Y(n + 2) x (m + 2)�̔z��ŕ\�����͕͂ǂƂ���B
 * (�O�̍s�̃}�X��ׂƔF�����Ȃ��悤�ɂ��邽��) <- �ǂ͉E������1�������ł����������ڂ��l�����Ď��͂ɂ��Ƃ�
 */
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


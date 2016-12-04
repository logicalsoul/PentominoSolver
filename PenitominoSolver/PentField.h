#pragma once
#include "PentHand.h"

/*
 * 敷き詰め問題の盤面
 * 盤面を1次元配列で表現。
 * n x m の盤面であれば、サイズ(n + 2) x (m + 2)の配列で表し周囲は壁とする。
 * (前の行のマスを隣と認識しないようにするため) <- 壁は右か左に1枚だけでいいが見た目も考慮して周囲につけとく
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


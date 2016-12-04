#pragma once
#include <string>

/*
 * ペントミノを配置する置き方のクラス
 * 置く場所の起点の座標を0として、ペントミノが占有する0以外の場所と種類を変数として持つ
 * 置く場所は1次元配列で管理されているとし、コンストラクタが座標上の右と下に移動した場合に
 * 配列インデックスに加算すべき値を引数として取る
 */
class PentHand
{
public:
	static const int PentominoSize = 5;

	// ペントミノの種類
	enum Shape
	{
		F, L, N, P, Y, Z,
		T, U, V, W, I, X,
		NumOfShapes
	};

	PentHand();
	~PentHand();

	void Set(int, int, Shape);

	PentHand Mirror() const;
	PentHand Rotate(int) const;
	PentHand Shift(int) const;

	bool operator==(PentHand) const;

	std::string ShapeStr(Shape);
	std::string to_string();
	bool IsSorted();

private:
	static const std::string ShapeStrArray[];
	int RightPos;		// 座標右に1つ移動したときにインデックスに加算すべき値(1であるはず)
	int DownPos;		// 座標下に1つ移動したときにインデックスに加算すべき値(9以上)
	int pos[PentominoSize - 1];		// 起点(座標0)以外の座標。比較するため常に昇順でソートする
	Shape shape;

	void SetRDPos(int, int);
	void SetShape(Shape);
	void Sort();

	inline int GetPos(int l, int d) const
	{
		return l * RightPos + d * DownPos;
	}
	
	inline int GetX(int p) const
	{
		int ret = (p + PentominoSize * DownPos) % DownPos;
		if (ret > DownPos / 2)
		{
			return ret - DownPos;
		}
		else
		{
			return ret;
		}
	}
	inline int GetY(int p) const { return (p - GetX(p)) / DownPos; }
};


#include "PentHand.h"

const std::string PentHand::ShapeStrArray[] =
{
	"F", "L", "N", "P", "Y", "Z",
	"T", "U", "V", "W", "I", "X"
};


PentHand::PentHand()
{
}

PentHand::~PentHand()
{
}

// 形とインデックスをセットする
void PentHand::Set(int r, int d, Shape s)
{
	SetRDPos(r, d);
	SetShape(s);
}

// 右と下の座標のインデックスをセットする
void PentHand::SetRDPos(int r, int d)
{
	RightPos = r;
	DownPos = d;
}

// 引数の形をセットする
void PentHand::SetShape(Shape s)
{
	shape = s;
	switch (s)
	{
	case F:
		pos[0] = GetPos(1, 0);
		pos[1] = GetPos(1, 1);
		pos[2] = GetPos(2, 1);
		pos[3] = GetPos(1, 2);
		break;
	case L:
		pos[0] = GetPos(0, 1);
		pos[1] = GetPos(0, 2);
		pos[2] = GetPos(0, 3);
		pos[3] = GetPos(1, 3);
		break;
	case N:
		pos[0] = GetPos(1, -3);
		pos[1] = GetPos(1, -2);
		pos[2] = GetPos(0, -1);
		pos[3] = GetPos(1, -1);
		break;
	case P:
		pos[0] = GetPos(1, 0);
		pos[1] = GetPos(0, 1);
		pos[2] = GetPos(1, 1);
		pos[3] = GetPos(0, 2);
		break;
	case Y:
		pos[0] = GetPos(1, -1);
		pos[1] = GetPos(1, 0);
		pos[2] = GetPos(1, 1);
		pos[3] = GetPos(1, 2);
		break;
	case Z:
		pos[0] = GetPos(1, 0);
		pos[1] = GetPos(1, 1);
		pos[2] = GetPos(1, 2);
		pos[3] = GetPos(2, 2);
		break;
	case T:
		pos[0] = GetPos(1, 0);
		pos[1] = GetPos(2, 0);
		pos[2] = GetPos(1, 1);
		pos[3] = GetPos(1, 2);
		break;
	case U:
		pos[0] = GetPos(2, 0);
		pos[1] = GetPos(0, 1);
		pos[2] = GetPos(1, 1);
		pos[3] = GetPos(2, 1);
		break;
	case V:
		pos[0] = GetPos(0, 1);
		pos[1] = GetPos(0, 2);
		pos[2] = GetPos(1, 2);
		pos[3] = GetPos(2, 2);
		break;
	case W:
		pos[0] = GetPos(0, 1);
		pos[1] = GetPos(1, 1);
		pos[2] = GetPos(1, 2);
		pos[3] = GetPos(2, 2);
		break;
	case I:
		pos[0] = GetPos(0, 1);
		pos[1] = GetPos(0, 2);
		pos[2] = GetPos(0, 3);
		pos[3] = GetPos(0, 4);
		break;
	case X:
		pos[0] = GetPos(1, -1);
		pos[1] = GetPos(1, 0);
		pos[2] = GetPos(2, 0);
		pos[3] = GetPos(1, 1);
		break;
	default:
		break;
	}
}

// x軸に対する鏡像を返す
PentHand PentHand::Mirror() const
{
	PentHand ret;

	ret.SetRDPos(RightPos, DownPos);
	ret.shape = shape;
	for (int i = 0; i < PentominoSize - 1; i++)
	{
		ret.pos[i] = GetPos(-GetX(pos[i]), GetY(pos[i]));
	}
	ret.Sort();

	return ret;
}

// 反時計回りに90度回転をcnt回行ったものを返す
// Y軸の向きが通常の座標系と逆なので変換行列が普通の回転行列でないことに注意
PentHand PentHand::Rotate(int cnt) const
{
	PentHand ret = *this;
	int i, j;

	for (j = 0; j < cnt; j++)
	{
		for (i = 0; i < PentominoSize - 1; i++)
		{
			ret.pos[i] = GetPos(GetY(ret.pos[i]), -GetX(ret.pos[i]));
		}
	}
	ret.Sort();

	return ret;
}

// pos[cnt]が起点となるようにシフトする
PentHand PentHand::Shift(int cnt) const
{
	PentHand ret = *this;
	int i;

	ret.SetRDPos(RightPos, DownPos);
	ret.shape = shape;
	for (i = 0; i < PentominoSize - 1; i++)
	{
		if (i == cnt)
		{
			ret.pos[i] = -pos[cnt];
		}
		else
		{
			ret.pos[i] = pos[i] - pos[cnt];
		}
	}
	ret.Sort();

	return ret;
}

// posをソートする
void PentHand::Sort()
{
	int i, j, t;

	for (i = PentominoSize - 2; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (pos[j] > pos[j + 1])
			{
				t = pos[j];
				pos[j] = pos[j + 1];
				pos[j + 1] = t;
			}
		}
	}
}

// 比較演算子
bool PentHand::operator==(PentHand p) const
{
	if (shape != p.shape)
	{
		return false;
	}

	for (int i = 0; i < PentominoSize - 1; i++)
	{
		if (pos[i] != p.pos[i])
		{
			return false;
		}
	}

	return true;
}

// ペントミノの形を表す文字列を返す
std::string PentHand::ShapeStr(Shape s)
{
	if (0 <= s && s < Shape::NumOfShapes)
	{
		return ShapeStrArray[s];
	}
	else
	{
		// 不正な引数のとき
		return "illegal index";
	}
}

// デバッグ用文字列出力
std::string PentHand::to_string()
{
	std::string ret;
	const int FieldSize = 9 * DownPos;
	const int center = 4 + 4 * DownPos;
	char *field = new char[FieldSize];	// 縦9, 横DownPosの盤の中央に起点を置いたとしてペントミノを表示する
	int i, j;

	for (i = 0; i < FieldSize; i++)
	{
		field[i] = '-';
	}
	for (i = 0; i < PentominoSize - 1; i++)
	{
		field[center + pos[i]] = '*';
	}
	field[center] = '*';	// 起点

	ret = "Shape:" + ShapeStr(shape) + "\n";
	for (i = 0; i < FieldSize / DownPos; i++)
	{
		for (j = 0; j < DownPos; j++)
		{
			ret += field[i * DownPos + j];
		}
		ret += "\n";
	}

	return ret;
}

// デバッグ用:ソート済かどうか
bool PentHand::IsSorted()
{
	int i;

	for (i = 0; i < PentominoSize - 2; i++)
	{
		if (pos[i] > pos[i + 1])
		{
			return false;
		}
	}
	return true;
}
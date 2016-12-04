#include "PentField.h"

PentField::PentField(int x, int y) : Xrange(x), Yrange(y), square_size(x * y)
{
	square = new Square[square_size];
	

	for (int i = 0; i < square_size; i++)
	{
		if (i < Xrange || i >= square_size - Xrange || i % Xrange == 0 || i % Xrange == Xrange - 1)
		{
			// ��
			square[i].is_occupied = true;
		}
		else
		{
			square[i].is_occupied = false;
		}
		square[i].shape = PentHand::NumOfShapes;	// �ЂƂ܂��S���ǂƓ����l�ɂ��Ă���
	}
}


PentField::~PentField()
{
	delete[] square;
}

// �w�肳�ꂽ�ꏊ�Ƀy���g�~�m��u���邩�ǂ�����Ԃ�
bool PentField::CanPut(PentHand p, int pos) const
{
	if (IsOutOfRange(pos) || square[pos].is_occupied)
	{
		return false;
	}

	for (int i = 0; i < PentHand::PentominoSize - 1; i++)
	{
		int tpos = pos + p.GetPos(i);

		if (IsOutOfRange(tpos) || square[tpos].is_occupied)
		{
			return false;
		}
	}

	return true;
}

// �w�肳�ꂽ�ꏊ�Ƀy���g�~�m��u���B���ł�CanPut()�Œu���邱�Ƃ��m�F�ς݂Ƃ���
void PentField::Put(PentHand p, int pos)
{
	square[pos].is_occupied = true;
	square[pos].shape = p.GetShape();

	for (int i = 0; i < PentHand::PentominoSize - 1; i++)
	{
		int tpos = pos + p.GetPos(i);

		square[tpos].is_occupied = true;
		square[tpos].shape = p.GetShape();
	}
}

// �w�肳�ꂽ�ꏊ����y���g�~�m����菜��
void PentField::Remove(PentHand p, int pos)
{
	square[pos].is_occupied = false;
	square[pos].shape = PentHand::NumOfShapes;

	for (int i = 0; i < PentHand::PentominoSize - 1; i++)
	{
		int tpos = pos + p.GetPos(i);

		square[tpos].is_occupied = false;
		square[tpos].shape = PentHand::NumOfShapes;
	}
}


// ���݂̔Ֆʏ�Ԃ�\���������Ԃ�
std::string PentField::to_string() const
{
	int x, y, pos;
	std::string ret = "";

	for (y = 0; y < Yrange; y++)
	{
		for (x = 0; x < Xrange; x++)
		{
			pos = x + y * Xrange;
			if (square[pos].is_occupied)
			{
				if (square[pos].shape < PentHand::NumOfShapes)
				{
					ret += PentHand::ShapeStr(square[pos].shape);
				}
				else
				{
					// ��
					ret += "+";
				}
			}
			else
			{
				ret += "-";
			}
		}
		ret += "\n";
	}
	return ret;
}
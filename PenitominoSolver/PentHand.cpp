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

// �`�ƃC���f�b�N�X���Z�b�g����
void PentHand::Set(int r, int d, Shape s)
{
	SetRDPos(r, d);
	SetShape(s);
}

// �E�Ɖ��̍��W�̃C���f�b�N�X���Z�b�g����
void PentHand::SetRDPos(int r, int d)
{
	RightPos = r;
	DownPos = d;
}

// �����̌`���Z�b�g����
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

// x���ɑ΂��鋾����Ԃ�
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

// �����v����90�x��]��cnt��s�������̂�Ԃ�
// Y���̌������ʏ�̍��W�n�Ƌt�Ȃ̂ŕϊ��s�񂪕��ʂ̉�]�s��łȂ����Ƃɒ���
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

// pos[cnt]���N�_�ƂȂ�悤�ɃV�t�g����
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

// pos���\�[�g����
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

// ��r���Z�q
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

// �y���g�~�m�̌`��\���������Ԃ�
std::string PentHand::ShapeStr(Shape s)
{
	if (0 <= s && s < Shape::NumOfShapes)
	{
		return ShapeStrArray[s];
	}
	else
	{
		// �s���Ȉ����̂Ƃ�
		return "illegal index";
	}
}

// �f�o�b�O�p������o��
std::string PentHand::to_string()
{
	std::string ret;
	const int FieldSize = 9 * DownPos;
	const int center = 4 + 4 * DownPos;
	char *field = new char[FieldSize];	// �c9, ��DownPos�̔Ղ̒����ɋN�_��u�����Ƃ��ăy���g�~�m��\������
	int i, j;

	for (i = 0; i < FieldSize; i++)
	{
		field[i] = '-';
	}
	for (i = 0; i < PentominoSize - 1; i++)
	{
		field[center + pos[i]] = '*';
	}
	field[center] = '*';	// �N�_

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

// �f�o�b�O�p:�\�[�g�ς��ǂ���
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
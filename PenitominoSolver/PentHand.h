#pragma once
#include <string>

/*
 * �y���g�~�m��z�u����u�����̃N���X
 * �u���ꏊ�̋N�_�̍��W��0�Ƃ��āA�y���g�~�m����L����0�ȊO�̏ꏊ�Ǝ�ނ�ϐ��Ƃ��Ď���
 * �u���ꏊ��1�����z��ŊǗ�����Ă���Ƃ��A�R���X�g���N�^�����W��̉E�Ɖ��Ɉړ������ꍇ��
 * �z��C���f�b�N�X�ɉ��Z���ׂ��l�������Ƃ��Ď��
 */
class PentHand
{
public:
	static const int PentominoSize = 5;

	// �y���g�~�m�̎��
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
	int RightPos;		// ���W�E��1�ړ������Ƃ��ɃC���f�b�N�X�ɉ��Z���ׂ��l(1�ł���͂�)
	int DownPos;		// ���W����1�ړ������Ƃ��ɃC���f�b�N�X�ɉ��Z���ׂ��l(9�ȏ�)
	int pos[PentominoSize - 1];		// �N�_(���W0)�ȊO�̍��W�B��r���邽�ߏ�ɏ����Ń\�[�g����
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


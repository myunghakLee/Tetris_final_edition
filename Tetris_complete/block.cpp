#include"Fscrine.h"
#include<iostream>

int block::change_block(const int a)		//����� ������� a�� ����� ���ư��� �ʴ� ��Ȳ���� ����� ������� �ٽ� ����� �ݴ�� ������� �ϹǷ� ���� �� ó�� �������� a�� 1�̰� ���� ��� ������ ���Ѵٴ� ������ �ǴܵǸ� a�� -1�� �ְ� �ٽ� �Լ��� ȣ���Ͽ� �ݴ�� �����ش�
{
	
	up += a; 
	if (up < 0){ up += 4; }

	up %= 4;
	return up;
}
int block::get_up() const
{
	return up;
}

tetrimino_0::tetrimino_0()
{
	int save[4][4][4] =
	{ { 
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } } };


	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				block_shape[i][j][k] = save[i][j][k];

}

int tetrimino_0::get_block(const int& y, const int& x) const
{
	return block_shape[get_up()][y][x];
}

tetrimino_L::tetrimino_L() :block()
{
	int save[4][4][4] =
	{ { 
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 0, 1, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 0, 0, 0 } } };
	memcpy(block_shape, save, sizeof(int) * 4 * 4 * 4);
}
int tetrimino_L::get_block(const int& y, const int& x) const
{
	return block_shape[get_up()][y][x];
}


tetrimino_J::tetrimino_J() :block()
{
	int save[4][4][4] =
	
	{ { 
	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 1, 0, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } } };
	memcpy(block_shape, save, sizeof(int) * 4 * 4 * 4);
}
int tetrimino_J::get_block(const int& y, const int& x) const
{
	return block_shape[get_up()][y][x];
}



tetrimino_S::tetrimino_S() :block()
{
	int save[4][4][4] =
	{ { 
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 0, 1, 1 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 0, 1, 1 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } } };
	memcpy(block_shape, save, sizeof(int) * 4 * 4 * 4);
}
int tetrimino_S::get_block(const int& y, const int& x) const
{
	return block_shape[get_up()][y][x];
}



tetrimino_Z::tetrimino_Z() :block()
{
	int save[4][4][4] =
		//Z ȸ��0 
	{ { 
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	//Z ȸ��1 
	{ 
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	//Z ȸ��2 
	{ 
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	//Z ȸ��3 
	{ 
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } } };
	memcpy(block_shape, save, sizeof(int) * 4 * 4 * 4);
}
int tetrimino_Z::get_block(const int& y, const int& x) const
{
	return block_shape[get_up()][y][x];
}



tetrimino_T::tetrimino_T() :block()
{
	int save[4][4][4] =
	{ 
	{
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	// �� ȸ�� 1
	{ 
	{ 0, 1, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	// �� ȸ�� 2
	{
	{ 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	// �� ȸ�� 3
	{ 
	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } } };
	memcpy(block_shape, save, sizeof(int) * 4 * 4 * 4);
}
int tetrimino_T::get_block(const int& y, const int& x) const
{
	return block_shape[get_up()][y][x];
}



tetrimino_I::tetrimino_I() :block()
{
	int save[4][4][4] =
		//���� ȸ��}0
	{ { 
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 } },
	//���� ȸ��1
	{ 
	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	//���� ȸ��}2
	{ 
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 } },
	//���� ȸ��3
	{ 
	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } } };
	memcpy(block_shape, save, sizeof(int) * 4 * 4 * 4);
}
int tetrimino_I::get_block(const int& y, const int& x) const
{
	return block_shape[get_up()][y][x];
}

tetrimino_plus::tetrimino_plus() :block()
{
	int save[4][4][4] =
	{ { 
	{ 0, 1, 0, 0 },
	{ 1, 0, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 1, 0, 0 },
	{ 1, 0, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	{ 
	{ 0, 1, 0, 0 },
	{ 1, 0, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	//���� ȸ��3
	{ 
	{ 0, 1, 0, 0 },
	{ 1, 0, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	};
	memcpy(block_shape, save, sizeof(int) * 4 * 4 * 4);
}
int tetrimino_plus::get_block(const int& y, const int& x) const
{
	return block_shape[get_up()][y][x];
}

#include"Fscrine.h"
#include<iostream>

int block::change_block(const int a)		//블록을 돌릴경우 a는 블록이 돌아가지 않는 상황에서 블록을 돌릴경우 다시 블록을 반대로 돌려줘야 하므로 있음 즉 처음 돌릴때는 a가 1이고 돌린 결과 돌리지 못한다는 것으로 판단되면 a에 -1을 넣고 다시 함수를 호출하여 반대로 돌려준다
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
		//Z 회전0 
	{ { 
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	//Z 회전1 
	{ 
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	//Z 회전2 
	{ 
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	//Z 회전3 
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
	// ㅏ 회전 1
	{ 
	{ 0, 1, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	// ㅜ 회전 2
	{
	{ 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
	// ㅓ 회전 3
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
		//직선 회전}0
	{ { 
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 } },
	//직선 회전1
	{ 
	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 1 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },
	//직선 회전}2
	{ 
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 } },
	//직선 회전3
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
	//직선 회전3
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

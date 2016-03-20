#ifndef __block___
#define __block___

#include"Fscrine.h"


class block		
{
private:
	int up;

public:
	block() : up(0)
	{}
	virtual int get_block(const int&y, const int&x) const = 0;
	int change_block(const int a);
	int get_up() const;
};

class tetrimino_0 :public block
{
private:
	int block_shape[4][4][4];										//맨 앞의 4는 블록이 돌아가는 4가지 모양 그 다음 2개의 4는 블록의 칸, block.cpp참조
public:
	virtual int get_block(const int& y, const int& x) const;
	tetrimino_0();
};

class tetrimino_L :public block
{
private:
	int block_shape[4][4][4];
public:
	virtual int get_block(const int& y, const int& x) const;
	tetrimino_L();
};

class tetrimino_J :public block
{
private:
	int block_shape[4][4][4];
public:
	virtual int get_block(const int& y, const int& x) const;
	tetrimino_J();
};

class tetrimino_S :public block
{
private:
	int block_shape[4][4][4];
public:
	virtual int get_block(const int& y, const int& x) const;
	tetrimino_S();
};

class tetrimino_Z :public block
{
private:
	int block_shape[4][4][4];
public:
	virtual int get_block(const int& y, const int& x) const;
	tetrimino_Z();
};

class tetrimino_T :public block
{
private:
	int block_shape[4][4][4];
public:
	virtual int get_block(const int& y, const int& x) const;
	tetrimino_T();
};

class tetrimino_I :public block
{
private:
	int block_shape[4][4][4];
public:
	virtual int get_block(const int& y, const int& x) const;
	tetrimino_I();
};

class tetrimino_plus : public block
{
private:
	int block_shape[4][4][4];
public:
	virtual int get_block(const int& y, const int& x) const;
	tetrimino_plus();
};

#endif

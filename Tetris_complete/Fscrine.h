#ifndef __F_SCRINE___
#define __F_SCRINE___
#include<conio.h>
#include<curses.h>
#include"block.h"
#include<fstream>
#include<windows.h>

class next_block
{
private:
	WINDOW *next_block_win;
	int block_shape[4][4];
	int next_color;
	int next_blocks;
	bool first;
public:
	next_block()
	{
		first = true;
		block *next_blocks = new tetrimino_0;
		next_block_win = newwin(8, 10, 2, 30);
		wbkgd(next_block_win, COLOR_PAIR(1));
	}
	void switch_first(){ first = false; };
	void draw() const;
	void input_block(block *blocks);			//block값을 fild라는 2차원 배열에 저장
	void redraw();
	void save_blocks_and_color(int blocks);
	int get_block();
	int get_color();
	bool get_first(){ return first; };
};

class score_scrine
{
private:
	WINDOW *score_win;
	int score;
public:
	score_scrine()
	{
		score_win = newwin(4, 10, 11, 30);
		wbkgd(score_win, COLOR_PAIR(1));
		score = 0;

	}
	void score_plus();
	void draw() const;
};

class user_name_scrine
{
private:
	WINDOW *user_win;
public:
	user_name_scrine()
	{
		user_win = newwin(4, 10, 17, 30);
	}
	void const draw(char name[]) const;
};




class main_scrine
{
private:
	int fild[21][13];		//테트리스 칸
	WINDOW * win;
	int score;				//점수
	int x, y;
	score_scrine scrine_score;			//스코어가 나올 화면
	user_name_scrine name_scrine;		//user의 이름이 나올 화면
	next_block next_block_scrine;
	int right;							//오른쪽 벽으로 부터의 거리
	int top;							//위쪽으로부터의 거리
	int color;							//색
public:
	main_scrine() :score(0)
	{
		color = 1;

		win = newwin(20, 22, 2, 2);
		for (int i = 0; i <= 17; i++)		//빈공간
			for (int j = 1; j <= 10; j++)
				fild[i][j] = 0;
		for (int i = 0; i <= 18; i++)		//벽
		{
			fild[i][0] = 10;
			fild[i][11] = 10;
			fild[i][12] = 10;
		}
		for (int i = 0; i <= 11; i++)		//벽
		{
			fild[20][i] = 10;
			fild[19][i] = 10;
		}
	}
	void print_start_scrine(char name[]) const;				//바깥 테두리 score_scrine, name_scrine을 만듬	
	void outside_border() const;							//바깥 테두리를 만듬
	void gamming_scrine(std::ifstream& instream);			//게임화면 만듬
	void start_game(std::ifstream& instream);				//테트리스 게임의 중심함수, 블록을 조작하고 없에는것이 대부분 들어있음
	bool const reprint_scrine(block *blocks) const;			//게임화면을 새로고침함 즉 데이터상으로는 움직였지만 화면에 나오지 않은 것을 나오게함
	bool const move_up(block *blocks);						//위로이동하는 함수, 현재 프로젝트에서는 사용하지 않음
	bool const move_down(block *blocks);					//아래로 한칸 이동하는 함수
	void move_side(block *blocks, int a);					//옆으로 움직이는 함수 a가 1이냐 -1이냐 에따라 왼쪽 오른쪽이 갈림
	void in_it_fild();										//fild 초기화 fild값이 1인부분(현재 내려가고 있는 블록)을 찾아 0으로 바꿈
	bool is_it_ok() const;									//블록이 그쪽으로 움직일수 있나 판단
	void input_block_fild(block *blocks, int a);			//block값을 fild라는 2차원 배열에 저장
	void delete_line(block *blocks);						//한줄을 지워도 되는 상환한지 판단 후 지워도 된다면 지움
	bool is_it_finish() const;								//gameover 가 되었는지			조건2(블록이 맨 첫줄에 쌓여 있는지, 단 이번 프로젝트에서는 사용하지 않음)
	void f(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);	//settimer를 사용하기 위한 함수



};


#endif

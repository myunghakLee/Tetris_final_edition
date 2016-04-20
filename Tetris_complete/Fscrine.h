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
	next_block(int x = 0)
	{
		first = true;
		block *next_blocks = new tetrimino_0;
		next_block_win = newwin(8, 10, 2, 30 + x);
		wbkgd(next_block_win, COLOR_PAIR(1));
	}
	void switch_first() { first = false; };
	void draw(int player = 1);
	void input_block(block *blocks);			//block값을 fild라는 2차원 배열에 저장
	void redraw(int player = 1);
	void save_blocks_and_color(int blocks);
	int get_block();
	int get_color();
	bool get_first() { return first; };
};

class score_scrine
{
private:
	WINDOW *score_win;
	int score;
	int score2;
public:
	score_scrine(const int x = 0)
	{
		score_win = newwin(4, 10, 11, 30 + x);
		wbkgd(score_win, COLOR_PAIR(1));
		score = 0;
	}
	void score_plus();
	void draw(int player = 1);
};

class user_name_scrine
{
private:
	WINDOW *user_win;
public:
	user_name_scrine(int x = 0)
	{
		user_win = newwin(4, 10, 17, 30 + x);
	}
	void const draw(char name[], int player = 1);
};




class main_scrine
{
private:
	int fild[2][21][13];		//테트리스 칸
	WINDOW * win[2];
	int score[2];				//점수
	score_scrine *scrine_score[2];			//스코어가 나올 화면
	user_name_scrine *name_scrine[2];		//user의 이름이 나올 화면
	next_block *next_block_scrine[2];
	int right[2];							//오른쪽 벽으로 부터의 거리
	int top[2];							//위쪽으로부터의 거리
	int color[2];							//색
	int top_shadow[2];						//shadow를 만들기 위한 top값
	bool shadow_on[2];						//shadow를 킬지 말지 정하는 변수
	bool player_complete_down[2];//각 플레이어마다 언제 바닥에 블럭을 완전히 내렸는지
	block *blocks[2];
	int choose;								//1p인지 2p인지 선택하기 위한 변수
	bool AI_on;



public:
	main_scrine(){
		AI_on = false;
		scrine_score[0] = new score_scrine;
		name_scrine[0] = new user_name_scrine;
		next_block_scrine[0] = new next_block;
		scrine_score[1] = new score_scrine(50);
		name_scrine[1] = new user_name_scrine(50);
		next_block_scrine[1] = new next_block(50);


		score[0] = 0;
		score[1] = 0;
		player_complete_down[0] = true;
		player_complete_down[1] = true;
		color[0] = 1;
		color[1] = 1;
		shadow_on[0] = true;
		shadow_on[1] = true;
		win[0] = newwin(20, 22, 2, 2);
		win[1] = newwin(20, 22, 2, 52);

		for (int pp = 0; pp < 2; pp++) {
			for (int i = 0; i <= 18; i++)		//빈공간
				for (int j = 1; j <= 10; j++) {
					fild[pp][i][j] = 0;
				}
			for (int i = 0; i <= 18; i++)		//벽
			{
				fild[pp][i][0] = 10;
				fild[pp][i][11] = 10;
				fild[pp][i][12] = 10;
			}
			for (int i = 0; i <= 12; i++)		//벽
			{
				fild[pp][20][i] = 10;
				fild[pp][19][i] = 10;
			}
		}


	}
	void print_start_scrine(char name[], char name2[]);				//바깥 테두리 score_scrine, name_scrine을 만듬	, player2 가 50일시 2번스크린 개방
	void outside_border();							//바깥 테두리를 만듬
	void start_game(std::ifstream& instream);				//테트리스 게임의 중심함수, 블록을 조작하고 없에는것이 대부분 들어있음
	bool const reprint_scrine() const;			//게임화면을 새로고침함 즉 데이터상으로는 움직였지만 화면에 나오지 않은 것을 나오게함
	bool const move_down(block *blocks, int p);					//아래로 한칸 이동하는 함수
	void move_side(block *blocks, int a, int p);					//옆으로 움직이는 함수 a가 1이냐 -1이냐 에따라 왼쪽 오른쪽이 갈림
	void in_it_fild(int p);										//fild 초기화 fild값이 1인부분(현재 내려가고 있는 블록)을 찾아 0으로 바꿈
	bool is_it_ok() const;									//블록이 그쪽으로 움직일수 있나 판단
	void input_block_fild(block *blocks, int a, int p);			//block값을 fild라는 2차원 배열에 저장
	void delete_line(block *blocks, int p);						//한줄을 지워도 되는 상환한지 판단 후 지워도 된다면 지움
	bool is_it_finish(int p) const;								//gameover 가 되었는지			조건2(블록이 맨 첫줄에 쌓여 있는지, 단 이번 프로젝트에서는 사용하지 않음)
	void make_shadow(block *blocks, int p);
	void input_shadow_fild(block *blocks, int a, int p);			//shadow를 집어넣음
	void draw();												//게임화면 그림
	void set_choose(int a) { choose = a; }										//choose를 변경하기 위한 함수
	int get_choose() { return choose; }							//choose에 접근하기 위한 함수
	void finish_scrine(block *blocks, int p);
	void AI_move(block *blocks, int p = 1 );												//AI의 움직임을 위한 함수
	int calc(int p = 1);												//AI가 어떻게 움직여야 하는지 계산하기 위한것을 정리, 관리하는 함수
	int calc_height(int p = 1);											//높이 계산
	int calc_surface(int p = 1);										//표면 계산
	int can_remove(int p = 1);											//지울 수 있나
	int nearly_remove(int p = 1);										//거의 지우기에 근접해 있나
	int calc_shadow_height(int p = 1);									//지금 쌓을 예정인 블록이 쌓일 높이
	int calc_blank(int p = 1);											//빈칸의 갯수
	void calc_blank_sub(int x, int y, int p = 1);
	void AI_ON() { AI_on = true; }

};




#endif
	
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
	void input_block(block *blocks);			//block���� fild��� 2���� �迭�� ����
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
	int fild[2][21][13];		//��Ʈ���� ĭ
	WINDOW * win[2];
	int score[2];				//����
	score_scrine *scrine_score[2];			//���ھ ���� ȭ��
	user_name_scrine *name_scrine[2];		//user�� �̸��� ���� ȭ��
	next_block *next_block_scrine[2];
	int right[2];							//������ ������ ������ �Ÿ�
	int top[2];							//�������κ����� �Ÿ�
	int color[2];							//��
	int top_shadow[2];						//shadow�� ����� ���� top��
	bool shadow_on[2];						//shadow�� ų�� ���� ���ϴ� ����
	bool player_complete_down[2];//�� �÷��̾�� ���� �ٴڿ� ���� ������ ���ȴ���
	block *blocks[2];
	int choose;								//1p���� 2p���� �����ϱ� ���� ����
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
			for (int i = 0; i <= 18; i++)		//�����
				for (int j = 1; j <= 10; j++) {
					fild[pp][i][j] = 0;
				}
			for (int i = 0; i <= 18; i++)		//��
			{
				fild[pp][i][0] = 10;
				fild[pp][i][11] = 10;
				fild[pp][i][12] = 10;
			}
			for (int i = 0; i <= 12; i++)		//��
			{
				fild[pp][20][i] = 10;
				fild[pp][19][i] = 10;
			}
		}


	}
	void print_start_scrine(char name[], char name2[]);				//�ٱ� �׵θ� score_scrine, name_scrine�� ����	, player2 �� 50�Ͻ� 2����ũ�� ����
	void outside_border();							//�ٱ� �׵θ��� ����
	void start_game(std::ifstream& instream);				//��Ʈ���� ������ �߽��Լ�, ����� �����ϰ� �����°��� ��κ� �������
	bool const reprint_scrine() const;			//����ȭ���� ���ΰ�ħ�� �� �����ͻ����δ� ���������� ȭ�鿡 ������ ���� ���� ��������
	bool const move_down(block *blocks, int p);					//�Ʒ��� ��ĭ �̵��ϴ� �Լ�
	void move_side(block *blocks, int a, int p);					//������ �����̴� �Լ� a�� 1�̳� -1�̳� ������ ���� �������� ����
	void in_it_fild(int p);										//fild �ʱ�ȭ fild���� 1�κκ�(���� �������� �ִ� ���)�� ã�� 0���� �ٲ�
	bool is_it_ok() const;									//����� �������� �����ϼ� �ֳ� �Ǵ�
	void input_block_fild(block *blocks, int a, int p);			//block���� fild��� 2���� �迭�� ����
	void delete_line(block *blocks, int p);						//������ ������ �Ǵ� ��ȯ���� �Ǵ� �� ������ �ȴٸ� ����
	bool is_it_finish(int p) const;								//gameover �� �Ǿ�����			����2(����� �� ù�ٿ� �׿� �ִ���, �� �̹� ������Ʈ������ ������� ����)
	void make_shadow(block *blocks, int p);
	void input_shadow_fild(block *blocks, int a, int p);			//shadow�� �������
	void draw();												//����ȭ�� �׸�
	void set_choose(int a) { choose = a; }										//choose�� �����ϱ� ���� �Լ�
	int get_choose() { return choose; }							//choose�� �����ϱ� ���� �Լ�
	void finish_scrine(block *blocks, int p);
	void AI_move(block *blocks, int p = 1 );												//AI�� �������� ���� �Լ�
	int calc(int p = 1);												//AI�� ��� �������� �ϴ��� ����ϱ� ���Ѱ��� ����, �����ϴ� �Լ�
	int calc_height(int p = 1);											//���� ���
	int calc_surface(int p = 1);										//ǥ�� ���
	int can_remove(int p = 1);											//���� �� �ֳ�
	int nearly_remove(int p = 1);										//���� ����⿡ ������ �ֳ�
	int calc_shadow_height(int p = 1);									//���� ���� ������ ����� ���� ����
	int calc_blank(int p = 1);											//��ĭ�� ����
	void calc_blank_sub(int x, int y, int p = 1);
	void AI_ON() { AI_on = true; }

};




#endif
	
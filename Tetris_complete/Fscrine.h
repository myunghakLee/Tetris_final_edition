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
	void input_block(block *blocks);			//block���� fild��� 2���� �迭�� ����
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
	int fild[21][13];		//��Ʈ���� ĭ
	WINDOW * win;
	int score;				//����
	int x, y;
	score_scrine scrine_score;			//���ھ ���� ȭ��
	user_name_scrine name_scrine;		//user�� �̸��� ���� ȭ��
	next_block next_block_scrine;
	int right;							//������ ������ ������ �Ÿ�
	int top;							//�������κ����� �Ÿ�
	int color;							//��
public:
	main_scrine() :score(0)
	{
		color = 1;

		win = newwin(20, 22, 2, 2);
		for (int i = 0; i <= 17; i++)		//�����
			for (int j = 1; j <= 10; j++)
				fild[i][j] = 0;
		for (int i = 0; i <= 18; i++)		//��
		{
			fild[i][0] = 10;
			fild[i][11] = 10;
			fild[i][12] = 10;
		}
		for (int i = 0; i <= 11; i++)		//��
		{
			fild[20][i] = 10;
			fild[19][i] = 10;
		}
	}
	void print_start_scrine(char name[]) const;				//�ٱ� �׵θ� score_scrine, name_scrine�� ����	
	void outside_border() const;							//�ٱ� �׵θ��� ����
	void gamming_scrine(std::ifstream& instream);			//����ȭ�� ����
	void start_game(std::ifstream& instream);				//��Ʈ���� ������ �߽��Լ�, ����� �����ϰ� �����°��� ��κ� �������
	bool const reprint_scrine(block *blocks) const;			//����ȭ���� ���ΰ�ħ�� �� �����ͻ����δ� ���������� ȭ�鿡 ������ ���� ���� ��������
	bool const move_up(block *blocks);						//�����̵��ϴ� �Լ�, ���� ������Ʈ������ ������� ����
	bool const move_down(block *blocks);					//�Ʒ��� ��ĭ �̵��ϴ� �Լ�
	void move_side(block *blocks, int a);					//������ �����̴� �Լ� a�� 1�̳� -1�̳� ������ ���� �������� ����
	void in_it_fild();										//fild �ʱ�ȭ fild���� 1�κκ�(���� �������� �ִ� ���)�� ã�� 0���� �ٲ�
	bool is_it_ok() const;									//����� �������� �����ϼ� �ֳ� �Ǵ�
	void input_block_fild(block *blocks, int a);			//block���� fild��� 2���� �迭�� ����
	void delete_line(block *blocks);						//������ ������ �Ǵ� ��ȯ���� �Ǵ� �� ������ �ȴٸ� ����
	bool is_it_finish() const;								//gameover �� �Ǿ�����			����2(����� �� ù�ٿ� �׿� �ִ���, �� �̹� ������Ʈ������ ������� ����)
	void f(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);	//settimer�� ����ϱ� ���� �Լ�



};


#endif

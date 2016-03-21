#include"Fscrine.h"
#include<iostream>
#include<windows.h>
#include<fstream>
#include<time.h>


double delay_time = 1.5;

void main_scrine::print_start_scrine(char name[]) const
{
	outside_border();
	scrine_score.draw();
	next_block_scrine.draw();
	name_scrine.draw(name);
}

void main_scrine::outside_border() const		//�� �ٱ��� â ����
{

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);		//score, username scrine�� �� ����	���ڻ�, ����
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);		//���� ���� â? �� ����

	bkgd(COLOR_PAIR(1));			//��attribute�� ������ ��ü ����
	bkgd(COLOR_PAIR(2));


	attron(COLOR_PAIR(2));			//������ attribute����
	border('|', '|', '-', '-', '+', '+', '+', '+');
	attroff(COLOR_PAIR(2));

	refresh();
}

void score_scrine::draw() const
{
	wbkgd(score_win, COLOR_PAIR(1));
	wattron(score_win, COLOR_PAIR(1));
	mvwprintw(score_win, 1, 1, "score");
	mvwprintw(score_win, 2, 1, "%d", score);
	wborder(score_win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(score_win);

}

void next_block::draw() const
{
	wbkgd(next_block_win, COLOR_PAIR(1));
	wattron(next_block_win, COLOR_PAIR(1));
	mvwprintw(next_block_win, 1, 3, "NEXT");
	wborder(next_block_win, '|', '|', '-', '-', '+', '+', '+', '+');

	wrefresh(next_block_win);


}
void next_block::redraw()
{
	block * blocks = new tetrimino_0;

	if (next_blocks == 0) { blocks = new tetrimino_L; }		//������ 0�� ���� ��� tetrimino_L�� ����
	else if (next_blocks == 1) { blocks = new tetrimino_J; }		//������ 1�� ���� ��� tetrimino_J�� ����
	else if (next_blocks == 2) { blocks = new tetrimino_0; }
	else if (next_blocks == 3) { blocks = new tetrimino_S; }
	else if (next_blocks == 4) { blocks = new tetrimino_Z; }
	else if (next_blocks == 5) { blocks = new tetrimino_T; }
	else if (next_blocks == 6) { blocks = new tetrimino_I; }
	else if (next_blocks == 7) { blocks = new tetrimino_plus; }


	input_block(blocks);
	mvwprintw(next_block_win, 2, 1, "        ");
	mvwprintw(next_block_win, 3, 1, "        ");
	mvwprintw(next_block_win, 4, 1, "        ");
	mvwprintw(next_block_win, 5, 1, "        ");
	mvwprintw(next_block_win, 6, 1, "        ");

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			if (block_shape[i][j] == 1)
			{
				wattron(next_block_win, COLOR_PAIR(next_color));
				mvwprintw(next_block_win, i + 3, j * 2 + 1, "��");
				wattroff(next_block_win, COLOR_PAIR(next_color));
			}
	}
	wrefresh(next_block_win);
	switch_first();

}
void next_block::save_blocks_and_color(int blocks)
{
	next_color = blocks + 3;
	next_blocks = blocks;
}
int next_block::get_block()
{
	return next_blocks;
}
int next_block::get_color() { return next_color; }

void next_block::input_block(block *blocks)
{

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			block_shape[i][j] = 0;
		}


	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			block_shape[i][j] += blocks->get_block(i, j);
		}
}


void score_scrine::score_plus()
{
	score++;		//score�� 1 �����ش�.
	draw();			//�ٽ� �׸���
}

void const user_name_scrine::draw(char name[]) const
{

	wbkgd(user_win, COLOR_PAIR(1));
	wattron(user_win, COLOR_PAIR(1));
	mvwprintw(user_win, 1, 1, "NAME");
	mvwprintw(user_win, 2, 1, "%s", name);
	wborder(user_win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(user_win);
}

void main_scrine::gamming_scrine(std::ifstream& instream)
{
	wattron(win, COLOR_PAIR(2));
	for (int i = 1; i <= 18; i++)
		mvwprintw(win, i, 1, "������������");
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	wattroff(win, COLOR_PAIR(2));

	wrefresh(win);
	while (1)	//gameover�� �Ǿ���?
	{
		start_game(instream);	//�׷��� ���� ��� ������ ��� ����
	}
}
void main_scrine::start_game(std::ifstream& instream)
{

	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);




	block *blocks = new tetrimino_0;

	int random_block;		//7�� 8�� ������ ��� �̻��� plus����� ���� �߰���, �� 7���� ���� �ϳ��� �������� �����ϱ� ���Ѱ�
	int random_block2;
	random_block = rand() % 7;
	if (next_block_scrine.get_first())		//���� �����ϰ� ó�� ���� ������ ���
	{
		random_block2 = random_block;		//randomblock2�� randomblock�� �����صд�
		random_block = rand() % 7;			//���� random_block�� ������ �����
	}
	else
	{
		random_block2 = next_block_scrine.get_block();	//randimblock2�� ���� block�� �����´�
	}
	next_block_scrine.save_blocks_and_color(random_block);	//randomblock�� ������ ������ �Ϳ� ǥ��
	random_block = random_block2;	//randomblock�� randomblock2�� �ٽ� ����
	
	color = random_block + 3;			//�� ������ ���� �ٸ��� �ؾ� �ϹǷ�


	if (random_block == 0) { blocks = new tetrimino_L; }		//������ 0�� ���� ��� tetrimino_L�� ����
	else if (random_block == 1) { blocks = new tetrimino_J; }		//������ 1�� ���� ��� tetrimino_J�� ����
	else if (random_block == 2) { blocks = new tetrimino_0; }
	else if (random_block == 3) { blocks = new tetrimino_S; }
	else if (random_block == 4) { blocks = new tetrimino_Z; }
	else if (random_block == 5) { blocks = new tetrimino_T; }
	else if (random_block == 6) { blocks = new tetrimino_I; }
	else if (random_block == 7) { blocks = new tetrimino_plus; }












	next_block_scrine.redraw();

	right = 4;						//ó�� ����� ���������κ��� 4ĭ
	top = 1;						//���κ��� 1ĭ �������� ����
	top_shadow = top;					//�׸��ڵ� ���� ����
	input_block_fild(blocks, 1);

	reprint_scrine(blocks);			//���ο� ����� ����
	if (!is_it_ok())
	{
		reprint_scrine(blocks);

		mvprintw(22, 8, "score : %d", score);
		mvprintw(23, 8, "Press 'Q' Key to exit Tetris");
		while (1)
		{
			char key = getch();
			if (key == 'q' || key == 'Q')
			{
				system("cls");
				exit(1);
			}
		}
	}

	double present_time, present_sec;
	double start_time = clock();
	double start_sec = 0;

	while (1)		//����� �ٴڿ� ������ ���� ����ڰ� �����ϼ� �ְ���
	{
		char key;
		instream >> key;
		if (shadow_on) {make_shadow(blocks);}

		if (key < 0 || instream.fail())		//input.txt�� ��������� ���� ���
		{

			double nt, nsec;		//����ð�, ���� ��  ����ð��� �� ū���ڷ� ǥ����
			double ot = clock();    // ���� �ð� ���� 
			double osec = 0;		//ó���� 0��

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////

			bool is_break = false;
			do {
				nt = clock();    // ���� �ð� ���� 
				nsec = difftime(nt, ot) / 1000;    // ��� �ð� 
				present_time = clock();	//starttime�� ¦�� �̷����
				present_sec = difftime(present_time, start_time) / 1000;	//����ð�

				if (nsec > osec + delay_time || present_sec > start_sec + delay_time) {    // �����ð��� ����ϸ� 
					start_sec = present_sec;    // ���� �޼��� ǥ�� �ð� �缳�� 
					osec = nsec;    // ���� �޼��� ǥ�� �ð� �缳�� 
					if (move_down(blocks))	//����� ��ĭ ������ ������ �Ͱ� ���ÿ� ����� �ٴڿ� ��Ҵ��� �Ǵ�
					{
						is_break = true;
						break;
					}
				}
 			} while (!_kbhit());    // Ű���尡 ������ �ʴ� ���� 
			if (is_break)
			{
				break;
			}//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			key = getch();

		}

		if (key == 3 || key == 't')			//up
		{
			blocks->change_block(1);
			in_it_fild();
			input_block_fild(blocks, 1);
			if (!is_it_ok())
			{
				input_block_fild(blocks, -1);
				blocks->change_block(-1);
				in_it_fild();
				input_block_fild(blocks, 1);
			}
			reprint_scrine(blocks);
		}
		else if (key == 2 || key == 'g')		//down
		{
			if (move_down(blocks))	//����� ��ĭ ������ ������ �Ͱ� ���ÿ� ����� �ٴڿ� ��Ҵ��� �Ǵ�
			{
				break;
			}
		}
		else if (key == 4 || key == 'l')		//left
		{
			right--;
			move_side(blocks, 1);		//����� ������ �ű�
		}
		else if (key == 5 || key == 'r')		//right
		{
			right++;
			move_side(blocks, -1);
		}
		else if (key == 32 || key == 'd')		//space
		{
			while (1)		//spaceŰ�� ���� ��� ����� �ٴڿ� ������ ���� ����Ͽ� ����
			{
				if (move_down(blocks))
				{
					break;
				}
			}
			break;
		}
		else if (key == 113 || key == 'q')	//q			q�� ������ ������ ����������
		{
			mvprintw(22, 8, "score : %d", score);
			mvprintw(23, 8, "Press 'Q' Key to exit Tetris");
			while (1)
			{
				char key = getch();
				if (key == 'q' || key == 'Q')
				{
					system("cls");
					exit(1);
				}
			}
		}
		else if (key == 's' || key == 'S')
		{
			if (is_it_ok()){
				if (shadow_on) { shadow_on = false; }
				else { shadow_on = true; }
			
			in_it_fild();
			input_block_fild(blocks, 1);
			reprint_scrine(blocks);
			}
		}
		else if (key == 'p')
		{
			reprint_scrine(blocks);

		}
		//else if (key == 'a')	//�� ���� �����
		//{

		//	for (int k = 18; k > 1; k--)
		//		for (int j = 1; j < 11; j++)
		//		{
		//			fild[k][j] = fild[k - 1][j];
		//		}
		//	reprint_scrine(blocks);
		//}
		//else if (key == 'z')	//���� ��� ��� �ٲٱ�
		//{
		//	input_block_fild(blocks, -1);
		//	break;
		//}
	}

	delete_line(blocks);
	reprint_scrine(blocks);

}
bool const main_scrine::reprint_scrine(block *blocks)const	//����ȭ���� ���ΰ�ħ(?)��
{
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 11; j++)
			if (fild[i][j] == 1)
			{
				wattron(win, COLOR_PAIR(color));
				mvwprintw(win, i, j * 2 - 1, "��");
				wattroff(win, COLOR_PAIR(color));
			}
			else if (fild[i][j] == 123)//shadow�� �����
			{
				wattron(win, COLOR_PAIR(10));
				mvwprintw(win, i, j * 2 - 1, "��");
				wattroff(win, COLOR_PAIR(10));
			}
			else if (fild[i][j] == 124)
			{
				wattron(win, COLOR_PAIR(color));
				mvwprintw(win, i, j * 2 - 1, "��");
				wattroff(win, COLOR_PAIR(color));
			}
			else if (fild[i][j] >= 100)
			{
				wattron(win, COLOR_PAIR(fild[i][j] / 100));
				mvwprintw(win, i, j * 2 - 1, "��");
				wattroff(win, COLOR_PAIR(fild[i][j] / 100));
			}
			else if (fild[i][j] == 0)
			{
				wattron(win, COLOR_PAIR(2));
				mvwprintw(win, i, j * 2 - 1, "��");
				wattroff(win, COLOR_PAIR(2));
			}
			
	}

	wrefresh(win);

	return true;
}

void main_scrine::in_it_fild()		//fild �ʱ�ȭ
{
	for (int i = 1; i < 19; i++)
		for (int j = 1; j < 11; j++)
			if (fild[i][j] == 1 || fild[i][j] == 123 || fild[i][j] == 124)
				fild[i][j] = 0;
}

bool main_scrine::is_it_ok() const	//����� ������ ������ �����ϼ� �ֳ� ������ �Ǵ�
{
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 13; j++)
			if (!(fild[i][j] == 0 || fild[i][j] == 1 || fild[i][j] == 10 || (fild[i][j] % 100 == 0) || fild[i][j] == 123 || fild[i][j] == 124))//fild �� 0,1,10,100,200,300,400...900�� ��� �� fild�� �̻��� ���� ���
			{
				return false;
			}
	return true;
}

void main_scrine::input_block_fild(block *blocks, int a)	//block�� �ʵ忡 ǥ��,	a�� 1�ϰ�� ����� ǥ�� -1�� ��� ����� ����
{
	for (int i = top; i < top + 4; i++)
		for (int j = right; j < right + 4; j++)
		{
			if (i < 0)
				i = 0;
			if (j < -1)
				j = -1;

			fild[i][j + 1] += blocks->get_block(i - top, j - right)*a;
		}

}

bool const main_scrine::move_down(block *blocks)
{
	in_it_fild();
	if (shadow_on) { input_shadow_fild(blocks, 1); }
	top++;
	if (top < 18)
	{
		input_block_fild(blocks, 1);	//����� ���� ��ġ�� �׸�
		if (!is_it_ok())	//����� �� �������� ���
		{
			input_block_fild(blocks, -1);//���� ����� ����, ����� ����� ������ �����̱� ����
			top--;
			input_block_fild(blocks, 1);//����� ��ĭ ������ �ٽ� �׸�
			for (int i = 1; i < 19; i++){
				for (int j = 1; j < 11; j++)
					if (fild[i][j] == 1 || fild[i][j] == 123 || fild[i][j]==124)
					{
						fild[i][j] = 100 * color;	//fild�� ���� �ٲپ��� �� 100���ڸ��� �� ����� ���� �ǹ���
					}
			}
			return true;
		}
		reprint_scrine(blocks);
		return false;
	}
	else//����� �� �ر��� ������ ���
	{
		top--;
		input_block_fild(blocks, 1);
		top++;
		for (int i = 1; i < 19; i++)
		{
			for (int j = 1; j < 11; j++)
				if (fild[i][j] == 1 || fild[i][j] == 124 || fild[i][j] == 123)
				{
					fild[i][j] = 100 * color;
				}///////////////////////////////////////////////////////////////////////////////////////
		}
		reprint_scrine(blocks);
		return true;
	}
	return false;
}

void main_scrine::move_side(block *blocks, int a)
{
	in_it_fild();

	input_block_fild(blocks, 1);
	if (!is_it_ok())				//�����̴� ���� ��������
	{
		input_block_fild(blocks, -1);		//���� ����� ����
		right += a;							//���������� ��ĭ �̵�
		input_block_fild(blocks, 1);		//����� �ٽ� �׸�
	}
	reprint_scrine(blocks);
}

void main_scrine::delete_line(block *blocks)
{
	int del = 0;
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (100 <= fild[i][j] && fild[i][j] <= 900)
				del++;
		}
		if (del == 10)		//������ �������
		{
			scrine_score.score_plus();	//score�� 1 �ø�
			score++;					//���߿� ������ ������ ������ ����ֱ� ���Ѱ�
			if (delay_time > 0.1)
			{
				delay_time -= 0.01;
			}
			for (int k = i; k > 0; k--)
				for (int j = 1; j < 11; j++)
				{
					fild[k][j] = fild[k - 1][j];	//������ �Ʒ��ٿ� ���� �ٿ��ֱ�
				}
		}
		del = 0;
	}

}
bool main_scrine::is_it_finish() const		//������ ��������2(�� ù�ٿ� ����� �׿��� ���), ���� �ڵ忡�� ��������� ����
{
	for (int j = 0; j < 12; j++)
		if (fild[1][j] > 99)
		{
			return true;
		}

	return false;
}

void main_scrine::make_shadow(block *blocks)
{
	top_shadow = top;

	in_it_fild();
	input_shadow_fild(blocks, 1);
	input_block_fild(blocks, 1);
	
	while (1) {
		if (is_it_ok() && top_shadow<18) {
			input_shadow_fild(blocks, -1);
			top_shadow++;
			input_shadow_fild(blocks, 1);
		}
		else {
			input_shadow_fild(blocks, -1);
			top_shadow--;
			input_shadow_fild(blocks, 1);
			break;
		}
	}
	reprint_scrine(blocks);

}

void main_scrine::input_shadow_fild(block *blocks, int a)
{
	for (int i = top_shadow; i < top_shadow + 4; i++)
		for (int j = right; j < right + 4; j++)
		{
			if (i < 0)
				i = 0;
			if (j < -1)
				j = -1;

			fild[i][j + 1] += blocks->get_block(i - top_shadow, j - right) * 123 * a;
		}
}

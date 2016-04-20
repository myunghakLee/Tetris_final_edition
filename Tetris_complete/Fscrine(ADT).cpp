#include"Fscrine.h"
#include<iostream>
#include<windows.h>
#include<fstream>
#include<time.h>


int calc_num[4][10];						//[��� ��������][���� Ȥ�� ���������� ��ȸ ��������, 5�� ��� 0�� �������� 5��]

static char up_key[2] = { 3, 'u' };
static char down_key[2] = { 2, 'j' };
static char left_key[2] = { 4, 'h' };
static char right_key[2] = { 5, 'k' };
static char space_key[2] = { 32, 'a' };
static char shadow_key[2] = { 's', 'w' };

double delay_time = 1.5;

void main_scrine::print_start_scrine(char name[], char name2[])
{
	scrine_score[0]->draw();
	next_block_scrine[0]->draw();
	name_scrine[0]->draw(name);

	scrine_score[1]->draw();
	next_block_scrine[1]->draw();
	name_scrine[1]->draw(name2);


	draw();
}

void main_scrine::outside_border()		//�� �ٱ��� â ����
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

void score_scrine::draw(int player)
{
	wbkgd(score_win, COLOR_PAIR(1));
	wattron(score_win, COLOR_PAIR(1));
	mvwprintw(score_win, 1, 1, "score");
	mvwprintw(score_win, 2, 1, "%d", score);
	wborder(score_win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(score_win);
}

void next_block::draw(int player)
{
	wbkgd(next_block_win, COLOR_PAIR(1));
	wattron(next_block_win, COLOR_PAIR(1));
	mvwprintw(next_block_win, 1, 3, "NEXT");
	wborder(next_block_win, '|', '|', '-', '-', '+', '+', '+', '+');

	wrefresh(next_block_win);


}

void next_block::redraw(int player)
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

void const user_name_scrine::draw(char name[], int player)
{

	wbkgd(user_win, COLOR_PAIR(1));
	wattron(user_win, COLOR_PAIR(1));
	mvwprintw(user_win, 1, 1, "NAME");
	mvwprintw(user_win, 2, 1, "%s", name);
	wborder(user_win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(user_win);

}

void main_scrine::draw()
{
	for (int p = 0; p < 2; p++) {
		wattron(win[p], COLOR_PAIR(2));
		for (int i = 1; i <= 18; i++)
			mvwprintw(win[p], i, 1, "������������");
		wborder(win[p], '|', '|', '-', '-', '+', '+', '+', '+');
		wattroff(win[p], COLOR_PAIR(2));
		wrefresh(win[p]);
	}
}

void main_scrine::start_game(std::ifstream& instream)
{
	//���� ���⿡ initpair �־���
	int height;
	bool is_break3 = false;


	if (player_complete_down[0]) {
		blocks[0] = new tetrimino_0;
	}
	if (player_complete_down[1]) {
		blocks[1] = new tetrimino_0;
	}

	int random_block[2];		//7�� 8�� ������ ��� �̻��� plus����� ���� �߰���, �� 7���� ���� �ϳ��� �������� �����ϱ� ���Ѱ�
	int random_block2[2];
	random_block[0] = rand() % 7;
	random_block[1] = rand() % 7;


	for (int p = 0; p < 2; p++) {
		if (next_block_scrine[p]->get_first())		//���� �����ϰ� ó�� ���� ������ ���
		{
			random_block2[p] = random_block[p];		//randomblock2�� randomblock�� �����صд�
			random_block[p] = rand() % 7;			//���� random_block�� ������ �����
			color[p] = random_block[p] + 3;			//�� ������ ���� �ٸ��� �ؾ� �ϹǷ�
		}
		else
		{
			if (player_complete_down[p]) {
				random_block2[p] = next_block_scrine[p]->get_block();	//randimblock2�� ���� block�� �����´�
				color[p] = random_block[p] + 3;			//�� ������ ���� �ٸ��� �ؾ� �ϹǷ�
			}
		}

		if (player_complete_down[p]) {
			next_block_scrine[p]->save_blocks_and_color(random_block[p]);	//randomblock�� ������ ������ �Ϳ� ǥ��
			random_block[p] = random_block2[p];	//randomblock�� randomblock2�� �ٽ� ����
			color[p] = random_block[p] + 3;

			player_complete_down[p] = false;
			if (random_block[p] == 0) { blocks[p] = new tetrimino_L; }		//������ 0�� ���� ��� tetrimino_L�� ����
			else if (random_block[p] == 1) { blocks[p] = new tetrimino_J; }		//������ 1�� ���� ��� tetrimino_J�� ����
			else if (random_block[p] == 2) { blocks[p] = new tetrimino_0; }
			else if (random_block[p] == 3) { blocks[p] = new tetrimino_S; }
			else if (random_block[p] == 4) { blocks[p] = new tetrimino_Z; }
			else if (random_block[p] == 5) { blocks[p] = new tetrimino_T; }
			else if (random_block[p] == 6) { blocks[p] = new tetrimino_I; }
			else if (random_block[p] == 7) { blocks[p] = new tetrimino_plus; }

			next_block_scrine[p]->redraw();
			right[p] = 4;						//ó�� ����� ���������κ��� 4ĭ
			top[p] = 1;						//���κ��� 1ĭ �������� ����
			top_shadow[p] = top[p];					//�׸��ڵ� ���� ����
			input_block_fild(blocks[p], 1, p);

			reprint_scrine();			//���ο� ����� ����

			if (!is_it_ok()) {
				finish_scrine(blocks[p], p);
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
		if (shadow_on[0]) { make_shadow(blocks[0], 0); }
		if (shadow_on[1]) { make_shadow(blocks[1], 1); }

		if (key < 0 || instream.fail())		//input.txt�� ��������� ���� ���
		{
			//double nt, nsec;		//����ð�, ���� ��  ����ð��� �� ū���ڷ� ǥ����
			//double ot = clock();    // ���� �ð� ���� 
			//double osec = 0;		//ó���� 0��

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////

			bool is_break = false;
			bool is_break2 = false;

			do {
				//nt = clock();    // ���� �ð� ���� 
				//nsec = difftime(nt, ot) / 1000;    // ��� �ð� 
				present_time = clock();	//starttime�� ¦�� �̷����
				present_sec = difftime(present_time, start_time) / 1000;	//����ð�

				if (/*nsec > osec + delay_time ||*/ present_sec > start_sec + delay_time) {    // �����ð��� ����ϸ� 

					start_sec = present_sec;    // ���� �޼��� ǥ�� �ð� �缳�� 
					//osec = nsec;    // ���� �޼��� ǥ�� �ð� �缳�� 

					for (int p = 0; p < 2; p++) {
						if (move_down(blocks[p], p))	//����� ��ĭ ������ ������ �Ͱ� ���ÿ� ����� �ٴڿ� ��Ҵ��� �Ǵ�
						{
							player_complete_down[p] = true;
							is_break = true;
							is_break2 = true;
						}
					}
					if (AI_on) {
						AI_move(blocks[1], 1);
						is_break = true;
						is_break2 = true;
						player_complete_down[1] = true;
					}
					if (is_break2) {
						break;
					}

				}
			} while (!_kbhit());    // Ű���尡 ������ �ʴ� ���� 


			if (is_break) {
				break;
			}//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			key = getch();

		}

		for (int p = 0; p < 2; p++) {
			if (key == up_key[p])			//up
			{
				blocks[p]->change_block(1);
				in_it_fild(p);
				input_block_fild(blocks[p], 1, p);
				if (!is_it_ok())
				{
					input_block_fild(blocks[p], -1, p);
					blocks[p]->change_block(-1);
					in_it_fild(p);
					input_block_fild(blocks[p], 1, p);
				}
				reprint_scrine();
			}
			else if (key == down_key[p])		//down
			{
				if (move_down(blocks[p], p))	//����� ��ĭ ������ ������ �Ͱ� ���ÿ� ����� �ٴڿ� ��Ҵ��� �Ǵ�
				{
					player_complete_down[p] = true;
					is_break3 = true;
					break;
				}
			}
			else if (key == left_key[p])		//left
			{
				right[p]--;
				move_side(blocks[p], 1, p);		//����� ������ �ű�
			}
			else if (key == right_key[p])		//right
			{
				right[p]++;
				move_side(blocks[p], -1, p);
			}
			else if (key == space_key[p])		//space
			{
				while (1)		//spaceŰ�� ���� ��� ����� �ٴڿ� ������ ���� ����Ͽ� ����
				{
					if (move_down(blocks[p], p))
					{
						player_complete_down[p] = true;
						is_break3 = true;
						break;
					}
				}
				break;
			}
			else if (key == shadow_key[p])
			{
				if (is_it_ok()) {
					if (shadow_on[p]) { shadow_on[p] = false; }
					else { shadow_on[p] = true; }

					in_it_fild(p);
					input_block_fild(blocks[p], 1, p);
					reprint_scrine();
				}
			}
			else if (key == 113 || key == 'q')	//q			q�� ������ ������ ����������
			{
				finish_scrine(blocks[p], p);
			}
			else if (key == 'p') {						//�Ͻ�����
				while (1) {
					mvprintw(23, 8, "Press 'P' if you want resume");
					char pause = getch();
					if (pause == 'p') {
						mvprintw(23, 8, "                              ");//���� press p if you .... �� ���� �����
						refresh();
						key = NULL;
						break;
					}
				}
				reprint_scrine();
			}
			else if (key == 'x')	//�� ���� �����
			{
				scrine_score[0]->score_plus();	//score�� 1 �ø�
				score[0]++;					//���߿� ������ ������ ������ ����ֱ� ���Ѱ�
				if (delay_time > 0.1)
				{
					delay_time -= 0.01;
				}
				for (int k = 18; k > 1; k--)
					for (int j = 1; j < 11; j++)
					{
						fild[0][k][j] = fild[0][k - 1][j];
					}
				reprint_scrine();
			}
			else if (key == 'z')	//���� ��� ��� �ٲٱ�
			{
				input_block_fild(blocks[0], -1, 0);

				in_it_fild(0);
				is_break3 = true;
				player_complete_down[0] = true;
				break;
			}
			else if (key == 'n') {
				AI_move(blocks[0], 0);
				is_break3 = true;

				break;
			}

		}


		if (is_break3) {
			break;
		}
	}


	for (int p = 0; p < 2; p++) {
		if (player_complete_down[p]) {
			delete_line(blocks[p], p);
			reprint_scrine();
		}
	}
}

bool const main_scrine::reprint_scrine()const	//����ȭ���� ���ΰ�ħ(?)��
{
	for (int p = 0; p < 2; p++) {
		for (int i = 1; i < 19; i++)
		{
			for (int j = 1; j < 11; j++)
				if (fild[p][i][j] == 1)
				{
					wattron(win[p], COLOR_PAIR(color[p]));
					mvwprintw(win[p], i, j * 2 - 1, "��");
					wattroff(win[p], COLOR_PAIR(color[p]));
				}
				else if (fild[p][i][j] == 123)//shadow�� �����
				{
					wattron(win[p], COLOR_PAIR(10));
					mvwprintw(win[p], i, j * 2 - 1, "��");
					wattroff(win[p], COLOR_PAIR(10));
				}
				else if (fild[p][i][j] == 124)
				{
					wattron(win[p], COLOR_PAIR(color[p]));
					mvwprintw(win[p], i, j * 2 - 1, "��");
					wattroff(win[p], COLOR_PAIR(color[p]));
				}
				else if (fild[p][i][j] >= 100)
				{
					wattron(win[p], COLOR_PAIR(fild[p][i][j] / 100));
					mvwprintw(win[p], i, j * 2 - 1, "��");
					wattroff(win[p], COLOR_PAIR(fild[p][i][j] / 100));
				}
				else if (fild[p][i][j] == 0)
				{
					wattron(win[p], COLOR_PAIR(2));
					mvwprintw(win[p], i, j * 2 - 1, "��");
					wattroff(win[p], COLOR_PAIR(2));
				}

		}

		wrefresh(win[p]);


	}
	return true;
}

void main_scrine::in_it_fild(int p)		//fild �ʱ�ȭ
{
	for (int i = 1; i < 19; i++)
		for (int j = 1; j < 11; j++)
			if (fild[p][i][j] == 1 || fild[p][i][j] == 123 || fild[p][i][j] == 124)
				fild[p][i][j] = 0;
}

bool main_scrine::is_it_ok() const	//����� ������ ������ �����ϼ� �ֳ� ������ �Ǵ�
{
	for (int p = 0; p < choose; p++)
		for (int i = 0; i < 21; i++)
			for (int j = 0; j < 13; j++)
				if (!(fild[p][i][j] == 0 || fild[p][i][j] == 1 || fild[p][i][j] == 10 || (fild[p][i][j] % 100 == 0) || fild[p][i][j] == 123 || fild[p][i][j] == 124)) {//fild �� 0,1,10,100,200,300,400...900�� ��� �� fild�� �̻��� ���� ���
					return false;
				}
	return true;
}

void main_scrine::input_block_fild(block *blocks, int a, int p)	//block�� �ʵ忡 ǥ��,	a�� 1�ϰ�� ����� ǥ�� -1�� ��� ����� ����
{
	for (int i = top[p]; i < top[p] + 4; i++)
		for (int j = right[p]; j < right[p] + 4; j++)
		{
			if (i < 0)
				i = 0;
			if (j < -1)
				j = -1;

			fild[p][i][j + 1] += blocks->get_block(i - top[p], j - right[p])*a;
		}

}

bool const main_scrine::move_down(block *blocks, int p)
{
	in_it_fild(p);
	if (shadow_on[p]) { input_shadow_fild(blocks, 1, p); }
	top[p]++;
	if (top[p] < 18)
	{
		input_block_fild(blocks, 1, p);	//����� ���� ��ġ�� �׸�
		if (!is_it_ok())	//����� �� �������� ���
		{
			input_block_fild(blocks, -1, p);//���� ����� ����, ����� ����� ������ �����̱� ����
			top[p]--;
			input_block_fild(blocks, 1, p);//����� ��ĭ �÷��� �ٽ� �׸�
			for (int i = 1; i < 19; i++) {
				for (int j = 1; j < 11; j++)
					if (fild[p][i][j] == 1 || fild[p][i][j] == 123 || fild[p][i][j] == 124)
					{
						fild[p][i][j] = 100 * color[p];	//fild�� ���� �ٲپ��� �� 100���ڸ��� �� ����� ���� �ǹ���
					}
			}
			return true;
		}
		reprint_scrine();
		return false;
	}
	else//����� �� �ر��� ������ ���
	{
		top[p]--;
		input_block_fild(blocks, 1, p);
		top[p]++;
		for (int i = 1; i < 19; i++)
		{
			for (int j = 1; j < 11; j++)
				if (fild[p][i][j] == 1 || fild[p][i][j] == 124 || fild[p][i][j] == 123)
				{
					fild[p][i][j] = 100 * color[p];
				}///////////////////////////////////////////////////////////////////////////////////////
		}
		reprint_scrine();
		return true;
	}
	return false;
}

void main_scrine::move_side(block *blocks, int a, int p)
{
	in_it_fild(p);

	input_block_fild(blocks, 1, p);
	if (!is_it_ok())				//�����̴� ���� ��������
	{
		input_block_fild(blocks, -1, p);		//���� ����� ����
		right[p] += a;							//���������� ��ĭ �̵�
		input_block_fild(blocks, 1, p);		//����� �ٽ� �׸�
	}
	reprint_scrine();
}

void main_scrine::delete_line(block *blocks, int p)
{
	int del = 0;
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (100 <= fild[p][i][j] && fild[p][i][j] <= 900)
				del++;
		}
		if (del == 10)		//������ �������
		{
			scrine_score[p]->score_plus();	//score�� 1 �ø�
			score[p]++;					//���߿� ������ ������ ������ ����ֱ� ���Ѱ�
			if (delay_time > 0.1)
			{
				delay_time -= 0.01;
			}
			for (int k = i; k > 0; k--)
				for (int j = 1; j < 11; j++)
				{
					fild[p][k][j] = fild[p][k - 1][j];	//������ �Ʒ��ٿ� ���� �ٿ��ֱ�
				}
		}
		del = 0;
	}

}

bool main_scrine::is_it_finish(int p) const		//������ ��������2(�� ù�ٿ� ����� �׿��� ���), ���� �ڵ忡�� ��������� ����
{
	for (int j = 0; j < 12; j++)
		if (fild[p][1][j] > 99)
		{
			return true;
		}

	return false;
}

void main_scrine::make_shadow(block *blocks, int p)
{
	top_shadow[p] = top[p];

	in_it_fild(p);
	input_shadow_fild(blocks, 1, p);
	input_block_fild(blocks, 1, p);

	while (1) {
		if (is_it_ok() && top_shadow[p] < 18) {
			input_shadow_fild(blocks, -1, p);
			top_shadow[p]++;
			input_shadow_fild(blocks, 1, p);
		}
		else {
			input_shadow_fild(blocks, -1, p);
			top_shadow[p]--;
			input_shadow_fild(blocks, 1, p);
			break;
		}
	}
	reprint_scrine();

}

void main_scrine::input_shadow_fild(block *blocks, int a, int p)
{
	for (int i = top_shadow[p]; i < top_shadow[p] + 4; i++)
		for (int j = right[p]; j < right[p] + 4; j++)
		{
			if (i < 0)
				i = 0;
			if (j < -1)
				j = -1;

			fild[p][i][j + 1] += blocks->get_block(i - top_shadow[p], j - right[p]) * 123 * a;
		}
}

void main_scrine::finish_scrine(block *blocks, int p)
{
	while (!is_it_ok()) {				//�������� ������ ���� �̻��ϰ� ��ġ�� ���� ����
		input_block_fild(blocks, -1, p);//���� ����� ����, ����� ����� ������ �����̱� ����
		top[p]--;
		input_block_fild(blocks, 1, p);//����� ��ĭ �÷��� �ٽ� �׸�
	}
	reprint_scrine();


	mvprintw(22, 2, " Player1's score : %d", score[0]);
	mvprintw(22, 53, "Player2's score : %d", score[1]);
	mvprintw(23, 3 + (choose - 1) * 20, "Press 'Q' Key to exit Tetris");	//2�ο��϶��� 1�ο��϶� �ٸ��� ����� �߰� �ϱ� ���ؼ�
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

void main_scrine::AI_move(block *blocks, int p)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 10; j++)
			calc_num[i][j] = 0;						//[��� ��������][���� Ȥ�� ���������� ��ȸ ��������, 5�� ��� 0�� �������� 5��]

	int cancel[4] = { 0,0,0,0 };	//�� ��縶�� ����� �ٲٱ� ���� ������ ���� ���߿� ���صξ�� �ؼ�



	for (int sh = 0; sh < 4; sh++) {			//sh = shape

		for (int i = 0; i < 11; i++) {				//�ϴ� ������ ������ �ű�
			right[p]++;
			move_side(blocks, -1, p);
		}

		make_shadow(blocks, p);

		calc_num[sh][0] = calc(p);				//�� �����ʿ� �ִ� ���  ca = 0

		for (int i = 1; i < 10; i++) {
			//////////////////////////////�����̵�/////////////////////////////////
			right[p]--;
			move_side(blocks, 1, p);		//����� ������ �ű�
			make_shadow(blocks, p);		//����� ���� shadow�� ����
			////////////////////////////////////////////////////////////////////////
			calc_num[sh][i] = calc(p);
		}
		/////////////////////////////////////���ٲ�////////////////////////////////////////////////////

		for (int C_sha = 0; C_sha < 4; C_sha++) {		//cha�� ��� �ٲ� �� ������ �� �ٲ� ��� 4������ �̵� ����ϰڴٴ°�
			blocks->change_block(1);
			in_it_fild(p);
			input_block_fild(blocks, 1, p);
			if (is_it_ok()) {
				reprint_scrine();
				break;
			}
			else
			{
				input_block_fild(blocks, -1, p);
				blocks->change_block(-1);
				in_it_fild(p);
				input_block_fild(blocks, 1, p);

				right[p]++;
				move_side(blocks, -1, p);
				make_shadow(blocks, p);
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
	}




	int optimum_num = 1000000;			//����ȭ �Ǿ������� ��, ���� ǥ������ ���� ����� �ִ��� ������
	int optimum_shape = 0;
	int optimum_move = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			if (optimum_num > calc_num[i][j]) {
				optimum_num = calc_num[i][j];
				optimum_shape = i;
				optimum_move = j;
			}
		}
	}
	mvprintw(23, 8, "%d %d %d %d", optimum_num, optimum_shape, optimum_move, calc_surface(p));
	refresh();

	for (int i = 0; i < optimum_shape; i++) {		//����� ������� �ٲ�
		blocks->change_block(1);
		in_it_fild(p);
		input_block_fild(blocks, 1, p);
		if (!is_it_ok())
		{
			input_block_fild(blocks, -1, p);
			blocks->change_block(-1);
			in_it_fild(p);
			input_block_fild(blocks, 1, p);
			i--;
			//cancel++;
			right[p]--;
			move_side(blocks, 1, p);
			make_shadow(blocks, p);

		}
		reprint_scrine();

	}
	//for (int i = 0; i < cancel; i++) {
	//	right[p]++;
	//	move_side(blocks, -1, p);
	//	make_shadow(blocks, p);
	//}

	for (int i = 0; i < 11; i++) {				//�ϴ� ������ ������ �ű�
		right[p]++;
		move_side(blocks, -1, p);
	}

	for (int i = 0; i < optimum_move; i++) {			//����� ����ŭ ������
		right[p]--;
		move_side(blocks, 1, p);
	}

	make_shadow(blocks, p);
	while (1)		//�� ������ ����
	{
		if (move_down(blocks, p))
		{
			player_complete_down[p] = true;
			break;
		}
	}
	in_it_fild(p);

}

int main_scrine::calc(int p)
{
	int num = 0;
	int height = calc_height(p);
	int H = height;					//���� ���� ����� ���� ����, ���� ���̿ʹ� ���� ��ƾ���;
	int shadow_height = calc_shadow_height(p);	//���� ������ ������� ���̿� ���ϰ�����
	int remove_line_num = can_remove(p);		//���� ���� �� �ִ���


	for (int i = 10; i < 18; i++) {
		if (height > i) { H++; }
		if (height > 10) {
			H += 1;
			shadow_height += 1;
			if (remove_line_num > 0) { remove_line_num++; }
		}
		if (height > 14) { H += 3; remove_line_num *= 2; shadow_height += 3; }
	}
	if (height > 17) {
		H *= 10000; remove_line_num *= 10000000; shadow_height *= 1000;
	}


	height = H;
	num = calc_surface(p) + H * 2 - remove_line_num * 7 + shadow_height - nearly_remove(p)*3 + calc_blank(p)*2;	//num�� ������ �������� ����

	return num;
}



int main_scrine::calc_height(int p)
{
	int height = 19;
	for (int i = 0; i <= 18; i++) {
		for (int j = 1; j <= 10; j++) {
			if (fild[p][i][j] != 0 && fild[p][i][j] != 1) {
				return height;
			}
		}
		height--;
	}
	return height;

}

int main_scrine::calc_surface(int p)
{
	float surface = 0;

	for (int i = 1; i <= 18; i++) {
		for (int j = 1; j <= 10; j++) {
			if (fild[p][i][j] == 0) {
				if (fild[p][i - 1][j] != 0 && fild[p][i - 1][j] != 1 && fild[p][i - 1][j] != 10) { surface++; }
				if (fild[p][i + 1][j] != 0 && fild[p][i + 1][j] != 1 && fild[p][i + 1][j] != 10) { surface++; }
				if (fild[p][i][j + 1] != 0 && fild[p][i][j + 1] != 1 && fild[p][i][j + 1] != 10) { surface++; }
				if (fild[p][i][j - 1] != 0 && fild[p][i][j - 1] != 1 && fild[p][i][j - 1] != 10) { surface++; }
				if (fild[p][i][j - 1] != 0 && fild[p][i][j + 1] != 0 && fild[p][i - 1][j] != 0 && fild[p][i + 1][j] != 0) { surface += 4; }	//��ĭ�ϳ�
				if (fild[p][i - 1][j] != 0 && fild[p][i + 1][j] != 0) { surface += 2; }
				
			
				if (fild[p][i - 1][j] != 0 && fild[p][i][j - 1] != 0 && (fild[p][i + 1][j] != 0 || fild[p][i + 1][j] != 10)) {	//�����ֱ⸦ �ؾ��ϴ� ��Ȳ
					if (fild[p][i - 1][j] != 1 && fild[p][i][j - 1] != 1 && (fild[p][i + 1][j] != 1)) {	//�����ֱ⸦ �ؾ��ϴ� ��Ȳ

						surface += 3;
					}
				}
				else if (fild[p][i - 1][j] != 0 && fild[p][i][j + 1] != 0 && (fild[p][i + 1][j] != 0 || fild[p][i + 1][j] != 10)) {	//�����ֱ⸦ �ؾ��ϴ� ��Ȳ
					if (fild[p][i - 1][j] != 1 && fild[p][i][j + 1] != 1 && (fild[p][i + 1][j] != 1 )) {	//�����ֱ⸦ �ؾ��ϴ� ��Ȳ
						surface += 3;
					}
				}
			}
			//else if (fild[p][i][j] % 100 == 0 || fild[p][i][j] == 123 || fild[p][i][j] == 124) {					//���� ����ִ� ���
			//	if (fild[p][i][j - 1] == 10 || fild[p][i][j + 1] == 10) { surface++; }
			//}
		}
	}

	//for (int i = 1; i <= 10; i++) {
	//	if (fild[p][18][i] == 0) { surface++; }
	//}
	return surface;
}

int main_scrine::can_remove(int p)
{
	int del_line_num = 0;

	int del = 0;
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (100 <= fild[p][i][j] && fild[p][i][j] <= 900)
				del++;
		}
		if (del == 10)		//������ �������
		{
			del_line_num++;
		}
		del = 0;
	}

	return del_line_num;
}

int main_scrine::calc_shadow_height(int p) {
	int shaodw_height = 19;
	for (int i = 0; i <= 18; i++) {
		for (int j = 1; j <= 10; j++) {
			if (fild[p][i][j] == 123 || fild[p][i][j] == 124) {
				return shaodw_height;
			}
		}
		shaodw_height--;
	}
	return shaodw_height;

}

int main_scrine::nearly_remove(int p) {		//�ʹ� ������ ­��.....
	int N_del_line_num = 0;

	int del = 0;
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (100 <= fild[p][i][j] && fild[p][i][j] <= 900)
				del++;
		}
		if (del > 7)		//������ �������
		{
			N_del_line_num++;
		}
		del = 0;
	}

	return N_del_line_num;

}

int main_scrine::calc_blank(int p) {
	int blank = 0;		//��Ʈ������ �� ĭ��
	for (int i = 0; i < 11; i++) {
		if (fild[p][0][i] == 0) {
			calc_blank_sub(0, i, p);
			break;
		}
	}

	for (int i = 1; i < 19; i++) {
		for (int j = 1; j < 11; j++) {
			if (fild[p][i][j] == 0) {
				blank++;
			}
		}
	}

	for (int i = 0; i < 19; i++) {
		for (int j = 1; j < 11; j++) {
			if (fild[p][i][j] == 2) {
				fild[p][i][j] = 0;
			}
		}
	}
	int pile_num = pile_on_blank(p);

//	blank += pile_num * 0.5;
	return blank;
}

void main_scrine::calc_blank_sub(int i, int j, int p) {
	fild[p][i][j] = 2;

	if (i > 0) {
		if (fild[p][i - 1][j] == 0) {
			calc_blank_sub(i - 1, j, p);
		}
	}
	if (j > 0) {
		if (fild[p][i][j - 1] == 0) {
			calc_blank_sub(i, j - 1, p);
		}
	}

	if (i < 19)
		if (fild[p][i + 1][j] == 0) {
			calc_blank_sub(i + 1, j, p);
		}
	if (j < 11)
		if (fild[p][i][j + 1] == 0) {
			calc_blank_sub(i, j + 1, p);
		}

	
}

int main_scrine::pile_on_blank(int p) {
	int num = 0;
	bool is_test_finish = false;
	for (int i = 1; i < 19; i++) {
		for (int j = 1; j < 11; j++) {
			if (fild[p][i][j] == 123 || fild[p][i][j] == 124) {
				num += pile_on_blank_sub(i, j, p);
				is_test_finish = true;
			}
		}
		if (is_test_finish) { break; }
	}

	return num;
}

int main_scrine::pile_on_blank_sub(int i, int j, int p) {
	int num = 0;	//shadow �Ʒ��� ��ĭ�� �󸶳� �ִ��� �� ����
	int num_blank = 0;	//shadow�� �����ִ� �� ������ ũ��
	while (i < 19) {
		if (fild[p][i][j] == 123 || fild[p][i][j] == 124) {
			num++;
		}
		else if (fild[p][i][j] == 0) {
			num_blank++;
		}
		else if (i == 18) {
			if (num_blank == 0) {
				num = 0;
			}
			break;
		}
		i++;
	}
	return num;
}

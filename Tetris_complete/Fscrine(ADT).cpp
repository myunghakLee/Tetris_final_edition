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

void main_scrine::outside_border() const		//맨 바깥쪽 창 생성
{

	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);		//score, username scrine의 색 변경	글자색, 배경색
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);		//게임 매인 창? 색 변경

	bkgd(COLOR_PAIR(1));			//한attribute로 윈도우 전체 적용
	bkgd(COLOR_PAIR(2));


	attron(COLOR_PAIR(2));			//적용할 attribute설정
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

	if (next_blocks == 0) { blocks = new tetrimino_L; }		//난수가 0이 나올 경우 tetrimino_L을 생성
	else if (next_blocks == 1) { blocks = new tetrimino_J; }		//난수가 1이 나올 경우 tetrimino_J를 생성
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
				mvwprintw(next_block_win, i + 3, j * 2 + 1, "■");
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
	score++;		//score를 1 더해준다.
	draw();			//다시 그린다
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
		mvwprintw(win, i, 1, "□□□□□□□□□□□");
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	wattroff(win, COLOR_PAIR(2));

	wrefresh(win);
	while (1)	//gameover가 되었나?
	{
		start_game(instream);	//그렇지 않을 경우 게임을 계속 진행
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

	int random_block;		//7을 8로 변경할 경우 이상한 plus모양의 블럭이 추가됨, 총 7개의 블럭중 하나를 랜덤으로 생성하기 위한것
	int random_block2;
	random_block = rand() % 7;
	if (next_block_scrine.get_first())		//게임 시작하고 처음 블럭이 나오는 경우
	{
		random_block2 = random_block;		//randomblock2에 randomblock을 저장해둔다
		random_block = rand() % 7;			//새로 random_block에 난수를 만든다
	}
	else
	{
		random_block2 = next_block_scrine.get_block();	//randimblock2에 다음 block을 가져온다
	}
	next_block_scrine.save_blocks_and_color(random_block);	//randomblock을 다음에 나오는 것에 표시
	random_block = random_block2;	//randomblock에 randomblock2를 다시 저장
	
	color = random_block + 3;			//각 블럭마다 색을 다르게 해야 하므로


	if (random_block == 0) { blocks = new tetrimino_L; }		//난수가 0이 나올 경우 tetrimino_L을 생성
	else if (random_block == 1) { blocks = new tetrimino_J; }		//난수가 1이 나올 경우 tetrimino_J를 생성
	else if (random_block == 2) { blocks = new tetrimino_0; }
	else if (random_block == 3) { blocks = new tetrimino_S; }
	else if (random_block == 4) { blocks = new tetrimino_Z; }
	else if (random_block == 5) { blocks = new tetrimino_T; }
	else if (random_block == 6) { blocks = new tetrimino_I; }
	else if (random_block == 7) { blocks = new tetrimino_plus; }












	next_block_scrine.redraw();

	right = 4;						//처음 블록은 오른쪽으로부터 4칸
	top = 1;						//위로부터 1칸 떨어져서 생성
	top_shadow = top;					//그림자도 같이 생성
	input_block_fild(blocks, 1);

	reprint_scrine(blocks);			//새로운 블록을 만듬
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

	while (1)		//블록이 바닥에 닿을때 까지 사용자가 움직일수 있게함
	{
		char key;
		instream >> key;
		if (shadow_on) {make_shadow(blocks);}

		if (key < 0 || instream.fail())		//input.txt에 저장되있지 않을 경우
		{

			double nt, nsec;		//현재시각, 현재 초  현재시각은 좀 큰숫자로 표현됨
			double ot = clock();    // 시작 시각 저장 
			double osec = 0;		//처음엔 0초

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////

			bool is_break = false;
			do {
				nt = clock();    // 현재 시각 저장 
				nsec = difftime(nt, ot) / 1000;    // 경과 시간 
				present_time = clock();	//starttime과 짝을 이룰것임
				present_sec = difftime(present_time, start_time) / 1000;	//경과시간

				if (nsec > osec + delay_time || present_sec > start_sec + delay_time) {    // 일정시간이 경과하면 
					start_sec = present_sec;    // 이전 메세지 표시 시각 재설정 
					osec = nsec;    // 이전 메세지 표시 시각 재설정 
					if (move_down(blocks))	//블록을 한칸 밑으로 내리는 것과 동시에 블록이 바닥에 닿았는지 판단
					{
						is_break = true;
						break;
					}
				}
 			} while (!_kbhit());    // 키보드가 눌리지 않는 동안 
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
			if (move_down(blocks))	//블록을 한칸 밑으로 내리는 것과 동시에 블록이 바닥에 닿았는지 판단
			{
				break;
			}
		}
		else if (key == 4 || key == 'l')		//left
		{
			right--;
			move_side(blocks, 1);		//블록을 옆으로 옮김
		}
		else if (key == 5 || key == 'r')		//right
		{
			right++;
			move_side(blocks, -1);
		}
		else if (key == 32 || key == 'd')		//space
		{
			while (1)		//space키를 누른 경우 블록이 바닥에 닿을때 까지 계속하여 내림
			{
				if (move_down(blocks))
				{
					break;
				}
			}
			break;
		}
		else if (key == 113 || key == 'q')	//q			q를 누르면 게임이 끝나도록함
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
		//else if (key == 'a')	//맨 밑줄 지우기
		//{

		//	for (int k = 18; k > 1; k--)
		//		for (int j = 1; j < 11; j++)
		//		{
		//			fild[k][j] = fild[k - 1][j];
		//		}
		//	reprint_scrine(blocks);
		//}
		//else if (key == 'z')	//현재 블록 모양 바꾸기
		//{
		//	input_block_fild(blocks, -1);
		//	break;
		//}
	}

	delete_line(blocks);
	reprint_scrine(blocks);

}
bool const main_scrine::reprint_scrine(block *blocks)const	//게임화면을 새로고침(?)함
{
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 11; j++)
			if (fild[i][j] == 1)
			{
				wattron(win, COLOR_PAIR(color));
				mvwprintw(win, i, j * 2 - 1, "■");
				wattroff(win, COLOR_PAIR(color));
			}
			else if (fild[i][j] == 123)//shadow를 만들것
			{
				wattron(win, COLOR_PAIR(10));
				mvwprintw(win, i, j * 2 - 1, "□");
				wattroff(win, COLOR_PAIR(10));
			}
			else if (fild[i][j] == 124)
			{
				wattron(win, COLOR_PAIR(color));
				mvwprintw(win, i, j * 2 - 1, "■");
				wattroff(win, COLOR_PAIR(color));
			}
			else if (fild[i][j] >= 100)
			{
				wattron(win, COLOR_PAIR(fild[i][j] / 100));
				mvwprintw(win, i, j * 2 - 1, "■");
				wattroff(win, COLOR_PAIR(fild[i][j] / 100));
			}
			else if (fild[i][j] == 0)
			{
				wattron(win, COLOR_PAIR(2));
				mvwprintw(win, i, j * 2 - 1, "□");
				wattroff(win, COLOR_PAIR(2));
			}
			
	}

	wrefresh(win);

	return true;
}

void main_scrine::in_it_fild()		//fild 초기화
{
	for (int i = 1; i < 19; i++)
		for (int j = 1; j < 11; j++)
			if (fild[i][j] == 1 || fild[i][j] == 123 || fild[i][j] == 124)
				fild[i][j] = 0;
}

bool main_scrine::is_it_ok() const	//블록이 지정된 곳으로 움직일수 있나 없나를 판단
{
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 13; j++)
			if (!(fild[i][j] == 0 || fild[i][j] == 1 || fild[i][j] == 10 || (fild[i][j] % 100 == 0) || fild[i][j] == 123 || fild[i][j] == 124))//fild 가 0,1,10,100,200,300,400...900일 경우 즉 fild에 이상이 없을 경우
			{
				return false;
			}
	return true;
}

void main_scrine::input_block_fild(block *blocks, int a)	//block을 필드에 표시,	a가 1일경우 블록을 표시 -1일 경우 블록을 지움
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
		input_block_fild(blocks, 1);	//블록의 현재 위치를 그림
		if (!is_it_ok())	//블록이 다 내려갔을 경우
		{
			input_block_fild(blocks, -1);//현재 블록을 지움, 현재는 블록이 겹쳐진 상태이기 때문
			top--;
			input_block_fild(blocks, 1);//블록을 한칸 내려서 다시 그림
			for (int i = 1; i < 19; i++){
				for (int j = 1; j < 11; j++)
					if (fild[i][j] == 1 || fild[i][j] == 123 || fild[i][j]==124)
					{
						fild[i][j] = 100 * color;	//fild의 값을 바꾸어줌 그 100의자리는 그 블록의 색을 의미함
					}
			}
			return true;
		}
		reprint_scrine(blocks);
		return false;
	}
	else//블록이 맨 밑까지 내려간 경우
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
	if (!is_it_ok())				//움직이는 것이 가능한지
	{
		input_block_fild(blocks, -1);		//현재 블록을 지움
		right += a;							//오른쪽으로 한칸 이동
		input_block_fild(blocks, 1);		//블록을 다시 그림
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
		if (del == 10)		//한줄이 꽉찬경우
		{
			scrine_score.score_plus();	//score을 1 올림
			score++;					//나중에 게임이 끝난후 점수를 띄워주기 위한것
			if (delay_time > 0.1)
			{
				delay_time -= 0.01;
			}
			for (int k = i; k > 0; k--)
				for (int j = 1; j < 11; j++)
				{
					fild[k][j] = fild[k - 1][j];	//윗줄을 아랫줄에 복사 붙여넣기
				}
		}
		del = 0;
	}

}
bool main_scrine::is_it_finish() const		//게임이 끝날조건2(맨 첫줄에 블록이 쌓였을 경우), 현재 코드에서 사용하지는 않음
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

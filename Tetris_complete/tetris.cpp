//////////////////////////////////////////
/*                                      */
/*          전자 정보통신대학           */
/*            컴퓨터공학과              */
/*          20143086 이명학             */
/*                                      */
//////////////////////////////////////////
#include <iostream>
#include<time.h>
#include"Fscrine.h"
#include<fstream>
#include <process.h>
#include <windows.h>



void make_terminal(int cho);
//void thread(void *game);


int main()
{


	char name[50];
	char name2[50];
	std::ifstream instream;
	instream.open("input.txt");

	instream >> name;
	int a;
	char choose[100] = {0}; //1인용을 할 것인지 2인용을 할 것인지 선택하게한다. 사용자가 다른 값을 입력할 때를 대비하여 문자형 배열로 만듬
	instream >> a;
	srand(900);
	// 4 : 400줄
	if (a < 0)
	{
		while (choose[0] != 1 || choose[0] != 2)						//choose 에 이상한 값을 집어넣었을 경우, 혹은 아직 choose에 값을 집어넣기 전
		{
			std::cout << "테트리스 게임을 시작합니다." << std::endl;
			std::cout << "1. 1인용\n";
			std::cout << "2. 2인용\n";
			std::cout << "3. 1P vs COMPUTER \n";
			std::cin >> choose;
			if (choose[0] == '1' || choose[0] == '2' || choose[0] == '3') { break; }
			else { std::cout << "잘못된 값이 입력되었습니다. '1', '2' 혹은 '3' 셋중 하나만 입력해 주십시오"; }
			Sleep(1500);
			system("cls");
		}
		std::cout << "사용자 이름을 입력하세요." << std::endl;
		std::cout << "이름 : ";
		std::cin >> name;
		if (choose[0] == '2') {
			std::cout << "Player2의 이름을 입력하세요." << std::endl;
			std::cin >> name2;
		}
		else if(choose[0] == '3'){
			strcpy_s(name2, 9, "computer");
		}
		srand(20);
	}

	make_terminal(choose[0]-'0');		//choose값을 cho에 대입 문자형은 0을 나타낼때 아스키코드값의 차이가 있으므로 -0을 해줌
	main_scrine game;

	if (choose[0] == '3') { game.AI_ON(); choose[0]--; }

	
	game.set_choose(choose[0] - '0');	//choose값을 cho에 대입 문자형은 0을 나타낼때 아스키코드값의 차이가 있으므로 -0을 해줌
	game.outside_border();
	game.print_start_scrine(name, name2);

//	main_scrine *game2 = new main_scrine(50);
//	game2->print_start_scrine(name);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);

	while (1)
	{
		game.start_game(instream);	//그렇지 않을 경우 게임을 계속 진행
	}

	//game->gamming_scrine(instream);
	//int memory_address = (int)game;
	//_beginthread(thread, 0, &memory_address);
	//int memory_address2 = (int)game2;
	//_beginthread(thread, 0, &memory_address2);
	
//	_beginthreadex(NULL, 0, thread, NULL, 0, &memory_address);
//	_beginthreadex(NULL, 0, thread, NULL, 0, (unsigned*)&game);

	getch();

	return 0;
}

void make_terminal(int cho)
{
	if (cho == 3) { cho--; }	//최대크기가 2여야 하므로 그러나 1P vs computer를 고르면 3이 들어가므로 1을 빼준다
	initscr();
	noecho();
	resize_term(25, 50*cho);
	keypad(stdscr, TRUE);
	curs_set(0);

	refresh();

	clear();
}

//void thread(void *game)
//{
//	std::ifstream instream;
//	instream.open("input.txt");
//
//
//	int *n = (int*)game;
//	main_scrine * G = new main_scrine;
//
//	G = (main_scrine*)*n;
//	char name[] = "asdf";
//	G->gamming(instream);
//}
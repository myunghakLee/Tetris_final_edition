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



void make_terminal();
//void thread(void *game);


int main()
{


	char name[50];
	char name2[50];
	std::ifstream instream;
	instream.open("input.txt");

	instream >> name;
	int a;
	instream >> a;
	srand(a);

	if (a < 0)
	{
		std::cout << "테트리스 게임을 시작합니다." << std::endl;
		std::cout << "사용자 이름을 입력하세요." << std::endl;
		std::cout << "이름 : ";
		std::cin >> name;
		std::cout << "Player2의 이름을 입력하세요." << std::endl;
		std::cin >> name2;
		srand(time(NULL));
	}

	make_terminal();//터미널을 만듬(크기조정)
	main_scrine game;
	game.outside_border();
	game.print_start_scrine(name, name2);

//	main_scrine *game2 = new main_scrine(50);
//	game2->print_start_scrine(name);


	game.gamming(instream);

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

void make_terminal()
{

	initscr();
	noecho();
	resize_term(25, 100);
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
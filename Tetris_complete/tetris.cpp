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


void make_terminal();



int main()
{

	
	char name[50];
	std::ifstream instream;
	instream.open("input.txt");


	instream >> name;
	int a;
	instream >> a;
	srand(a);

	if (a<0)
	{
		std::cout << "테트리스 게임을 시작합니다." << std::endl;
		std::cout << "사용자 이름을 입력하세요." << std::endl;
		std::cout << "이름 : ";
		std::cin >> name;
		srand(time(NULL));
	}


	make_terminal();//터미널을 만듬(크기조정)
	main_scrine game(2,2);


	game.print_start_scrine(name);

	game.gamming_scrine(instream);


	getch();

	return 0;
}



void make_terminal()
{

	initscr();
	noecho();
	resize_term(25, 50);
	keypad(stdscr, TRUE);
	curs_set(0);

	refresh();

	clear();
}
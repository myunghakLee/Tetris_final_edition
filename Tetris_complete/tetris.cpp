//////////////////////////////////////////
/*                                      */
/*          ���� ������Ŵ���           */
/*            ��ǻ�Ͱ��а�              */
/*          20143086 �̸���             */
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
		std::cout << "��Ʈ���� ������ �����մϴ�." << std::endl;
		std::cout << "����� �̸��� �Է��ϼ���." << std::endl;
		std::cout << "�̸� : ";
		std::cin >> name;
		std::cout << "Player2�� �̸��� �Է��ϼ���." << std::endl;
		std::cin >> name2;
		srand(time(NULL));
	}

	make_terminal();//�͹̳��� ����(ũ������)
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
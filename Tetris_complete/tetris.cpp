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
		std::cout << "��Ʈ���� ������ �����մϴ�." << std::endl;
		std::cout << "����� �̸��� �Է��ϼ���." << std::endl;
		std::cout << "�̸� : ";
		std::cin >> name;
		srand(time(NULL));
	}


	make_terminal();//�͹̳��� ����(ũ������)
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
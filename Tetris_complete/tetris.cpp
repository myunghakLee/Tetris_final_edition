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
	char choose[100] = {0}; //1�ο��� �� ������ 2�ο��� �� ������ �����ϰ��Ѵ�. ����ڰ� �ٸ� ���� �Է��� ���� ����Ͽ� ������ �迭�� ����
	instream >> a;
	srand(900);
	// 4 : 400��
	if (a < 0)
	{
		while (choose[0] != 1 || choose[0] != 2)						//choose �� �̻��� ���� ����־��� ���, Ȥ�� ���� choose�� ���� ����ֱ� ��
		{
			std::cout << "��Ʈ���� ������ �����մϴ�." << std::endl;
			std::cout << "1. 1�ο�\n";
			std::cout << "2. 2�ο�\n";
			std::cout << "3. 1P vs COMPUTER \n";
			std::cin >> choose;
			if (choose[0] == '1' || choose[0] == '2' || choose[0] == '3') { break; }
			else { std::cout << "�߸��� ���� �ԷµǾ����ϴ�. '1', '2' Ȥ�� '3' ���� �ϳ��� �Է��� �ֽʽÿ�"; }
			Sleep(1500);
			system("cls");
		}
		std::cout << "����� �̸��� �Է��ϼ���." << std::endl;
		std::cout << "�̸� : ";
		std::cin >> name;
		if (choose[0] == '2') {
			std::cout << "Player2�� �̸��� �Է��ϼ���." << std::endl;
			std::cin >> name2;
		}
		else if(choose[0] == '3'){
			strcpy_s(name2, 9, "computer");
		}
		srand(20);
	}

	make_terminal(choose[0]-'0');		//choose���� cho�� ���� �������� 0�� ��Ÿ���� �ƽ�Ű�ڵ尪�� ���̰� �����Ƿ� -0�� ����
	main_scrine game;

	if (choose[0] == '3') { game.AI_ON(); choose[0]--; }

	
	game.set_choose(choose[0] - '0');	//choose���� cho�� ���� �������� 0�� ��Ÿ���� �ƽ�Ű�ڵ尪�� ���̰� �����Ƿ� -0�� ����
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
		game.start_game(instream);	//�׷��� ���� ��� ������ ��� ����
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
	if (cho == 3) { cho--; }	//�ִ�ũ�Ⱑ 2���� �ϹǷ� �׷��� 1P vs computer�� ���� 3�� ���Ƿ� 1�� ���ش�
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
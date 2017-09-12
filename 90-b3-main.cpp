/*1551445 童佳燕 计算机科学与技术1班*/
#define _CRT_SECURE_NO_WARNINGS
#include"cmd_console_tools.h"
#include"90-b3.h"
int main()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	char choice;
	while (1)
	{
		setconsoleborder(hout, 120, 50);
		setfontsize(hout, L"新楷体", 16);
		printMenu();
		checkInput(&choice);
		switch (choice)
		{
		case '1':
			printEClockFrame();
			printEClock();
			break;
		case '2':
			system("cls");
			printPClockFrame();
			printPClock();
			break;
		case '3':
			system("cls");
			alarmSet();
			break;
		case '0':
			exit(0);
		}
	}
	return 0;
}
/*1551445 ͯ���� �������ѧ�뼼��1��*/
#define _CRT_SECURE_NO_WARNINGS
#include"cmd_console_tools.h"
#include"90-b3.h"

void printMenu()
{
	cout << "--------------------------" << endl;
	cout << "1.��ʾʱ�ӣ�����ʽ��" << endl;
	cout << "2.��ʾʱ�ӣ�ָ��ʽ��" << endl;
	cout << "3.������������" << endl;
	cout << "0.�˳�" << endl;
	cout << "--------------------------" << endl;
	cout << "������ѡ�";
	return;
}

void checkInput(char *choice )
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int x = 0, y = 0;
	getxy(hout, x, y);
	while (1)
	{
		cin >> *choice;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			gotoxy(hout, x, y);
			cout << "                                   ";
			gotoxy(hout, x, y);
			continue;
		}
		else if (*choice > '4' || *choice < '0')
		{
			gotoxy(hout, 0, y + 1);
			cout << "input error,please input 0-3,again";
			gotoxy(hout, x, y);
			cout << "                                   ";
			gotoxy(hout, x, y);
			continue;
		}
		else
		{
			gotoxy(hout, 0, y + 1);
			cout << "                                    ";
			gotoxy(hout, 0, y + 1);
			break;
		}
	}
	return;
}

Status printBitMapWord(unsigned char *word,int baseX,int baseY)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	ifstream infile("HZK16", ios::in | ios::binary);
	if (infile.is_open() == 0)
	{
		cout << "open error" << endl;
		return FAIL;
	}
	int offset=(94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;//���ƫ����
	infile.seekg(offset, ios::beg);

	unsigned short bit[16];
	infile.read((char *)bit, 32);
	infile.close();
	for (int i = 0; i < 16; i++)
	{   /*�ӵ�λ����λ�洢*/
		int x = bit[i] & 0x00ff;
		for (int j = 0; j < 8; j++)
		{
			if (x & 0x0080)
			{
				gotoxy(hout, baseX + j, baseY + i);
				cout << "*";
			}
			else
			{
				gotoxy(hout, baseX + j, baseY + i);
				cout << " ";
			}
			x <<= 1;//aaaaaaaaa <<=������������   <<
		}

		x = bit[i] & 0xff00;
		for (int j = 0; j < 8; j++)
		{
			if (x & 0x8000)
			{
				gotoxy(hout, baseX + j+8, baseY + i);
				cout << "*";
			}
			else
			{
				gotoxy(hout, baseX + j + 8, baseY + i);
				cout << " ";
			}
			x <<= 1;
		}
		cout << endl;
	}
	return OK;
}

Status printBitMapStr(unsigned char *str,int baseX,int baseY)
{
	unsigned char word[2];
	for (int i = 0; ; i+=2)
	{
		if (str[i] == '\0')
			break;
		word[0] = str[i];
		word[1] = str[i + 1];
		printBitMapWord(word, baseX + 8 * i, baseY);
	}
	return OK;
}

void printFigure(char value, int baseX, int baseY)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (value == '0')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '1')
	    printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '2')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '3')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '4')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '5')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '6')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '7')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '8')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
	else if (value == '9')
		printBitMapWord((unsigned char *)"��", baseX, baseY);
}


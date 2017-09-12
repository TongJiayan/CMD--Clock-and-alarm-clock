/*1551445 童佳燕 计算机科学与技术1班*/
#define _CRT_SECURE_NO_WARNINGS
#include"cmd_console_tools.h"
#include"90-b3.h"

void printEClockFrame()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setfontsize(hout, L"点阵字体", 1);
	setconsoleborder(hout, BORDER_COL, BORDER_LINE);

	gotoxy(hout, EBASEX, EBASEY);

	int N = BORDER_COL/50-1;
	int M = 30;
	for(int i=0;i<N;i++)
	cout << "-------------------------------------------------" ;
	for (int i = 0; i < M; i++)
	{
		gotoxy(hout, EBASEX, EBASEY + 1+i);
		cout << "|";
		gotoxy(hout, EBASEX+N*50-5, EBASEY + 1 + i);
		cout << "|";
	}
	gotoxy(hout, EBASEX, EBASEY+M+1);
	for (int i = 0; i<N; i++)
		cout << "-------------------------------------------------";
	for (int i = 1; i < 3;i++)
		for (int j = 1; j < 3; j++)
		{
			gotoxy(hout, EBASEX + 80*i, EBASEY + 10*j);
			cout << "●";
		}
	unsigned char str1[20] = "Ｋ：切换";
	printBitMapStr(str1, EBASEX-5, EBASEY + 50);
	unsigned char str2[20] = "Ｓ：关闭音乐";
	printBitMapStr(str2, EBASEX + 65, EBASEY + 50);
	unsigned char str3[20] = "Ｂ：返回首页";
	printBitMapStr(str3, EBASEX + 170, EBASEY + 50);
	return;
}

void printDate()
{
	char date[64], word[3];
	time_t t = time(0);
	strftime(date, 64, "%Y %m %d", localtime(&t));

	int leap = 0, x = EBASEX + 12;
	for (int i = 0; ; i++)
	{
		if (date[i] == ' ')
		{
			if (leap == 0)
				strcpy(word, "年");
			else if (leap == 1)
				strcpy(word, "月");
			leap++;
			printBitMapWord((unsigned char*)word, x, EBASEY + 85);
			x += 20;
		}
		else
		{
			printFigure(date[i], x, EBASEY + 85);
			x += 20;
		}
		if (leap == 2 && i == strlen(date) - 1)
		{
			strcpy(word, "日");
			printBitMapWord((unsigned char*)word, x, EBASEY + 85);
			break;
		}
	}
}

void printEClock()
{
	char timeArr[64],word[3];
	int x;
	time_t t = time(0);
	strftime(timeArr, 64, "%X", localtime(&t));
	int numTime[3], preNumTime[3];
	for (int i = 0; i < 8; i += 3)
	{
		word[0] = timeArr[i];
		word[1] = timeArr[i + 1];
		numTime[i / 3] = atoi(word);
		preNumTime[i / 3]=0;
	}

     /*将前一秒的时间记录在preNumTime中，相差大于1或小于-1时才做新的打印，
      [-1,1]是考虑闹铃响的时候，暂停所需的时间*/

	printDate();
	while (!GetAsyncKeyState('B'))//按下A停止
	{
		x = EBASEX + 7;
		for (int i = 0; i < (signed)strlen(timeArr); i++)
		{
			if (timeArr[i] == ':')
				x += 25;
			else
			{
				printFigure(timeArr[i], x, EBASEY + 7);
				x += 30;
			}
		}
		while (1)
		{
			time_t t = time(0);
			strftime(timeArr, 64, "%X", localtime(&t));
			
			/*将字符串中的信息分别提取，转换成数值型，便于判断*/
			for (int i = 0; i < 8; i += 3)
			{
				word[0] = timeArr[i];
				word[1] = timeArr[i + 1];
				numTime[i / 3] = atoi(word);
			}
			if (numTime[2] - preNumTime[2] >= 1 || numTime[2] - preNumTime[2] <= -1)
				break;

			/*转换到指针型的表盘*/
			if (GetAsyncKeyState('K'))
			{
				system("cls");
				printPClockFrame();
				printPClock();
				return;
			}
			if (GetAsyncKeyState('B'))
			{
				HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
				system("cls");
				setconsoleborder(hout, 100, 50);
				setfontsize(hout, L"新楷体", 16);
				return;
			}
			/*返回主菜单*/
		}
		if (preNumTime[1] != numTime[1])
		{
			if (itIsTime(timeArr) == YES)
			{
				unsigned char str[9] = "时间到！";
				printBitMapStr(str, EBASEX + 90, EBASEY - 20);
				mciSendString(TEXT("play 90-b3-ext\\Tomorrow.mp3"), 0, 0, 0);//播放
				while (_getch() != 'S');
				unsigned char str2[9] = "　　　　";
				printBitMapStr(str2, EBASEX + 90, EBASEY - 20);
				mciSendString(TEXT("close 90-b3-ext\\Tomorrow.mp3"), 0, 0, 0);//播放
			}
		}
		for (int i = 0; i < 3; i++)
			preNumTime[i] = numTime[i];
	}
	return;
}

void printPClockFrame()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setfontsize(hout, L"点阵字体", 1);
	setconsoleborder(hout, BORDER_COL, BORDER_LINE);
	for (double x = X - A; x < X + A; x += 0.1)
	{
		double m = pow((1.0 - (x - X)*(x - X) / (A*A))*(B*B), 0.5);
		gotoxy(hout, (int)x, (int)(m + Y));
		printf("%c", '-');
		gotoxy(hout, (int)x, (int)(Y - m));
		printf("%c", '-');
	}
	unsigned char str1[20] = "Ｋ：切换";
	printBitMapStr(str1, X+100, Y-20);
	unsigned char str2[20] = "Ｓ：关闭音乐";
	printBitMapStr(str2, X + 100, Y);
	unsigned char str3[20] = "Ｂ：返回首页";
	printBitMapStr(str3, X + 100, Y +20);
	return;
}


void drawPointer(double t, double pointerLen, int isHour, int isClear)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	double x = X;
	while (1)
	{
		if (t == 0||t==60 || isHour == 1 && (int)t % 12 == 0)
		{
			for (double y = Y; y > Y - pointerLen; y -= 0.1)
			{
				gotoxy(hout, (int)X, (int)y);
				if (isClear)
					printf("%c", ' ');
				else
					printf("%c", '-');
			}
			break;
		}
		else if (t == 30 || isHour == 1 && (int)t % 6 == 0)
		{
			for (double y = Y; y < Y + pointerLen; y += 0.1)
			{
				gotoxy(hout, (int)X, (int)y);
				if (isClear)
					printf("%c", ' ');
				else
					printf("%c", '-');
			}
			break;
		}
		double rad;
		if (!isHour)
			rad = 6 * t / 360.0 * 2 * PI;
		else if (t>12)
			rad = (t - 12) * 30 / 360.0 * 2 * PI;
		else
			rad = t * 30 / 360.0 * 2 * PI;
		double y = (-1)*(tan(0.5*PI - rad))*(x - X) + Y;
		double len = (y - Y)*(y - Y) + (x - X)*(x - X) / 3.2;

		gotoxy(hout, (int)x, (int)y);
		if (isClear)
			printf("%c", ' ');
		else
			printf("%c", '-');
		if (len>pointerLen*pointerLen)
			break;
		if (t < 30 &&isHour!=1||isHour==1 && ((int)t%12)<6)
			x += 0.1;
		else
			x -= 0.1;
	}
	return;
}

void printPClock()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	printDate();
	char timeArr[64], word[3];
	int numTime[3], preNumTime[3];
	time_t t = time(0);
	strftime(timeArr, 64, "%X", localtime(&t));
	for (int i = 0; i < 8; i += 3)
	{
		word[0] = timeArr[i];
		word[1] = timeArr[i + 1];
		numTime[i / 3] = atoi(word);
		preNumTime[i / 3]= 0;
	}
	drawPointer((double)numTime[2], SLEN, 0, 0);
	drawPointer((double)numTime[1], MLEN, 0, 0);
	drawPointer((double)numTime[0], HLEN, 1, 0);
	word[2] = '\0';
	while (!GetAsyncKeyState('B'))
	{
		
		while (!GetAsyncKeyState('B'))
		{
			time_t t = time(0);
			strftime(timeArr, 64, "%X", localtime(&t));
			for (int i = 0; i < 8; i += 3)
			{
				word[0] = timeArr[i];
				word[1] = timeArr[i + 1];
				numTime[i / 3] = atoi(word);
			}
			
			if (numTime[2] - preNumTime[2] >=1|| numTime[2] - preNumTime[2]<=-1)//强调-59的重要性
				break;
			if (GetAsyncKeyState('K'))
			{
				system("cls");
				printEClockFrame();
				printEClock();
				return;
			}
			if (GetAsyncKeyState('B'))
			{
				HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
				system("cls");
				setconsoleborder(hout, 100, 50);
				setfontsize(hout, L"新楷体", 16);
				return;
			}
		}
		drawPointer((double)preNumTime[2], SLEN, 0, 1);
		drawPointer((double)numTime[2], SLEN, 0, 0);
		if (numTime[2] == 0 ||numTime[2]-numTime[1]==1)
		{
			drawPointer((double)preNumTime[1], MLEN, 0, 1);
			drawPointer((double)numTime[1], MLEN, 0, 0);
		}
		if (numTime[1] == 0 || numTime[2]==(numTime[0]%12)*5+1 || numTime[1] == (numTime[0]%12)*5+1)
		{
			drawPointer((double)preNumTime[0], HLEN, 1, 1);
			drawPointer((double)numTime[0], HLEN, 1, 0);
		}

		if (preNumTime[1]< numTime[1])
			if (itIsTime(timeArr) == YES)
			{
				unsigned char str[9] = "时间到！";
				printBitMapStr(str, X + 103, Y - 38);
				mciSendString(TEXT("play 90-b3-ext\\Mercy.mp3"), 0, 0, 0);//播放
				while (_getch() != 'S');
				unsigned char str2[9] = "　　　　";
				printBitMapStr(str2, X + 103, Y - 38);
				mciSendString(TEXT("close 90-b3-ext\\Mercy.mp3"), 0, 0, 0);//播放
			}
		for (int i = 0; i < 3; i++)
			preNumTime[i] = numTime[i];
	}
	return;
}

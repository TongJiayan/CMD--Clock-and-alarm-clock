/*1551445 童佳燕 计算机科学与技术1班*/
#define _CRT_SECURE_NO_WARNINGS
#include"cmd_console_tools.h"
#include"90-b3.h"


Status printSettedAlarm(fstream &file)//输出当前时间以及已经设置的闹钟 
{
	system("cls");
	char timeArr[64];
	cout << "\n\n                          当前时间为：";

	time_t t = time(0);
	strftime(timeArr, 64, "%Y年%m月%d日%X", localtime(&t));
	puts(timeArr);

	cout << "\n   -----------------------------------------------------------------------------" << endl;
	cout << "\n    您已设置的闹钟：\n\n";

	char record[80];
	int recordNum = 0;//记录数量
	file.clear();
	file.seekg(0, ios::beg);
	while (1)
	{
		if (file.peek() == '\r')
			file.ignore();//跳过\r,因为二进制文件换行需要\r\n  ！！！！！！
		file.getline(record, 80);
		if (strlen(record) > 2)
		    printf("  %d     %s\n\n", ++recordNum, record);
		if (file.peek() == EOF)
			break;
	}
	file.seekp(0,ios::beg);
	file.seekg(0, ios::beg);
	return OK;
}

void buttonPrint()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hout,0, 30);
	printf("        %s\n", "--------------");
	printf("%s\n", "        |  添加（I） |");
	printf("        %s\n", "--------------");
	
	gotoxy(hout,30, 30);
	printf("        %s\n", "--------------");
	gotoxy(hout, 30, 31);
	printf("%s\n", "        |  删除（D） |");
	gotoxy(hout,30, 32);
	printf("        %s\n", "--------------");

	gotoxy(hout, 60, 30);
	printf("        %s\n", "--------------");
	gotoxy(hout, 60, 31);
	printf("%s\n", "        |  返回（R） |");
	gotoxy(hout, 60, 32);
	printf("        %s\n", "--------------");
}

Status alarmSet()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setconsoleborder(hout, 100, BORDER_LINE);
	setfontsize(hout, L"新楷体", 16);
	fstream file(fname, ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		printf("%s", "文件打开失败");
		return FAIL;
	}

	char choice;
	while (1)
	{
		printSettedAlarm(file);
		buttonPrint();
		printf("%s", "请输入操作码：");
		scanf("%c", &choice);
		if (choice == 'I')//添加
			alarmInsert(file);
		else if (choice == 'D')//删除
		{
			if(!alarmDelete(file))//如果没有找到要求删除的记录
				printf("%s\n","抱歉，您没有设置该时间的闹钟");
		}
		else if (choice == 'R')
		{
			system("cls");
			return OK;
		}
	}
	file.close();
	return OK;
}

void alarmInsert(fstream &file)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	char insertInfo[80];
	cin.clear();//忽略输入流中前面操作输入的回车键
	cin.sync();
	printf("   \n%s", "  请输入您要设置的时间(精确到分，2020 01 01 00：00前)，以及形式（每天，每工作日，单次），\n\n  如“2017 04 08 12：00*每天”,\n\n  以*作为分割符,以#作为结束符：\n\n");
	printf("\n\n %s", "  请输入添加信息\n");
	
	while (1)
	{
		cin.clear();//忽略输入流中前面操作输入的回车键
		cin.sync();
		cin.getline(insertInfo, 80, '#');//以#作为结束
		if (addInfoCheck(insertInfo)==OK)
			break;
	}
	int l = strlen(insertInfo);
	insertInfo[l] = '#';//配置文件的末尾也需要有#方便读取时进行判断
	insertInfo[l + 1] = '\0';
	file.clear();
	file.seekp(0, ios::end);
	file.write(insertInfo, strlen(insertInfo));
	file.write("\r\n",2);

	gotoxy(hout,50, 10);
	printf("%s", "  添加成功！");
	gotoxy(hout,50, 14);
	printf("%s\n", "-------------");
	gotoxy(hout,50, 15);
	printf("%s\n", "|  返回（B）|");
	gotoxy(hout,50, 16);
	printf("%s\n", "-------------");

	while (cin.get() != 'B');//读到B返回
	return;
}

Status alarmDelete(fstream &file)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int index = 0, index2 = 0;
	char str[80];

	system("cls");
	cin.clear();
	cin.sync();
	printf("   \n%s", "请输入您要删除的是第几条设置：\n\n");
	cin >> index;//用于定位，不需要从文件中一条一条比对
	
	/*将需要删除的记录后面的记录存放在tmpArr动态数组中
	利用experimental::filesystem::resize_file(fname, index);将文件缩小到只剩需要删除记录的前面几条
	在文件末尾添加上tmpArr数组中的文件内容*/
	file.clear();
	file.seekg(0, ios::end);
	int fileLength = (int)file.tellg();
	file.clear();
	file.seekg(0, ios::beg);
	for (int i = 0;i<index-1||fileLength==0; i++)//如果没有记录也要进来，输出找不到记录的提示
	{
		file.getline(str, 80);
		if (file.peek() == EOF||!fileLength)
		{
			printf("%s\n", "抱歉，您没有设置该闹钟!");
			gotoxy(hout, 25, 14);
			printf("%s\n", "-------------");
			gotoxy(hout, 25, 15);
			printf("%s\n", "|  返回（B）|");
			gotoxy(hout, 25, 16);
			printf("%s\n", "-------------");

			while (cin.get() != 'B');//读到B返回
			return FAIL;
		}
	}
	file.clear();//很重要
	index = (int)file.tellg();
	
	while (1)
	{
		file.getline(str, 80);
		if (strlen(str) > 2)
			break;
	}
	index2 = (int)file.tellg();

	file.clear();
	char *tmpArr = (char *)malloc((fileLength - index2 + 10) * sizeof(char));
	if (tmpArr == NULL)
	{
		printf("%s", "申请空间失败");
		return FAIL;
	}
	
	file.read(tmpArr, fileLength - index2);
	experimental::filesystem::resize_file(fname, index-1);
	file.seekp(0, ios::end);
	file.write(tmpArr, fileLength - index2);
	free(tmpArr);


	gotoxy(hout, 25, 10);
	printf("%s", "  删除成功！");
	gotoxy(hout, 25, 14);
	printf("%s\n", "-------------");
	gotoxy(hout, 25, 15);
	printf("%s\n", "|  返回（B）|");
	gotoxy(hout, 25, 16);
	printf("%s\n", "-------------");

	while (cin.get() != 'B');//读到B返回
	return OK;
}


Status itIsTime(char *timeArr)
{
	fstream file(fname, ios::in | ios::binary|ios::out);
	if (file.is_open()==0)
	{
		printf("%s", "文件打开失败");
		return NO;
	}

	char tmp[30];
	char s[64];
	time_t t = time(0);
	strftime(tmp, 30, "%Y %m %d ", localtime(&t));
	strcpy(s, tmp);
	strcat(s, timeArr);
	s[strlen(s)] = '\0';
	
	file.seekg(0, ios::end);
	int fileLength = (int)file.tellg();
	if (fileLength <= 2)
	{
		file.close();
		return NO;
	}
	file.clear();
	file.seekg(0, ios::beg);
	char info[80], tjTime[30], tjForm[20];
	while (1)
	{
		int index1 = (int)file.tellg();//记录需要删除的记录头部的位置
		file.clear();
		file.getline(info, 80);
		if (strlen(info) < 2)
			continue;
		int index2 = (int)file.tellg();//记录需要删除的记录下一条头部的位置
		file.clear();

		getInfo(info, tjTime, tjForm);
		if (strncmp(tjTime, s,16) == 0)
		{
		    
			if (strcmp(tjForm, "单次") == 0)//音乐播放之后就需要删除该条记录
			{
				char *tmpArr = (char *)malloc(sizeof(char)*(fileLength - index2 + 10));
				if (tmpArr == NULL)
				{
					printf("%s", "空间申请失败");
					return FAIL;
				}
				file.read(tmpArr, fileLength - index2);
				experimental::filesystem::resize_file(fname, index1);
				file.seekp(0, ios::end);
				file.write(tmpArr, fileLength - index2);
				free(tmpArr);
				file.close();
				return YES;
			}
			else if (strcmp(tjForm, "每工作日") == 0)//需要对是否是工作日进行判断
			{
				char weekDay;
				time_t t = time(0);
				strftime(&weekDay, 1, "%w", localtime(&t));
				file.close();
				if (weekDay > '0'&&weekDay < '6')
					return YES;
				else
				    return NO;
			}
			else if (strcmp(tjForm, "每天") == 0)
			{
				file.close();
				return YES;
			}
		}
		if (file.peek() == EOF)
			break;
	}
	return NO;
}

void getInfo(char *str,char *tjTime,char *tjForm)
{
	int i,j;
	for (i = 0; str[i] != '*'; i++)
		tjTime[i] = str[i];
	tjTime[i] = '\0';
	i++;
	j = 0;
	for (; str[i]!='#'; i++,j++)
		tjForm[j] = str[i];
	tjForm[j] = '\0';
	return;
}

Status addInfoCheck(char *str)
{
	if (strlen(str) < 18)
	{
		printf("%s\n", "您输入的时间格式不对，请重新输入");
		return FAIL;
	}
	int M[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (str[5] != ' ' || str[8] != ' ' || str[11] != ' ' || str[14] != ':' || str[17] != '*')
	{
		
		if (str[4] != ' ')
			cout << 1;
		if (str[7] != ' ')
			cout << 2;
		if (str[10] != ' ')
			cout << 3;
		if (str[13] != ':')
			cout << 4;
		if (str[16] != '*')
			cout << 5;
		printf("%s\n", "您输入的时间格式不对，请重新输入");
		return FAIL;
	}

	char tjYear[5];
	time_t t = time(0);
	strftime(tjYear, 5, "%Y", localtime(&t));

	char wordY[5];
	for (int i = 1; i < 5; i++)
		wordY[i - 1] = str[i];
	
	if (atoi(tjYear)>atoi(wordY)||atoi(wordY)>2019)
	{
		printf("%s\n", "您输入的年份不符合标准，请重新输入");
		return FAIL;
	}
	int leap = atoi(tjYear) % 400 == 0 || atoi(tjYear) % 4 == 0 && atoi(tjYear) % 100 != 0;
	char tjMonth[3];
	
	strftime(tjMonth, 3, "%m", localtime(&t));

	char wordM[3];
	wordM[0] = str[6];
	wordM[1] = str[7];
	wordM[2] = '\0';
	
	if (atoi(tjYear) == atoi(wordY) && atoi(tjMonth) > atoi(wordM)||atoi(tjMonth)<1||atoi(tjMonth)>12)
	{
		printf("%s\n", "您输入的月份不符合标准，请重新输入");
		return FAIL;
	}

	char tjDay[3];
	strftime(tjDay, 3, "%d", localtime(&t));
	char wordD[3];
	wordD[0] = str[9];
	wordD[1] = str[10];
	if (leap)
		M[1]++;
	if (atoi(wordD) > M[atoi(wordM) - 1] || atoi(wordD) < 1 || atoi(wordD) < atoi(tjDay) && atoi(tjYear) == atoi(wordY) && atoi(tjMonth) == atoi(wordM))
	{
		printf("%s\n", "您输入的日期不符合标准，请重新输入");
		return FAIL;
	}

	char tjHour[3];
	strftime(tjHour, 3, "%H", localtime(&t));
	char wordH[3];
	wordH[0] = str[12];
	wordH[1] = str[13];
	wordH[2] = '\0';
	if (atoi(wordH) < 0 || atoi(wordH) > 24 || atoi(wordH)<atoi(tjHour)&& atoi(wordD) == atoi(tjDay) && atoi(tjYear) == atoi(wordY) && atoi(tjMonth) == atoi(wordM))
	{
		printf("%s\n", "您输入的小时不符合标准，请重新输入");
		return FAIL;
	}

	char tjMin[3];
	strftime(tjMin, 3, "%M", localtime(&t));
	char wordMin[3];
	wordMin[0] = str[15];
	wordMin[1] = str[16];
	wordMin[2] = '\0';
	if (atoi(wordMin) < 0 || atoi(wordMin) > 60 || atoi(wordH)==atoi(tjHour) && atoi(wordD) == atoi(tjDay) && atoi(tjYear) == atoi(wordY) && atoi(tjMonth) == atoi(wordM) && atoi(tjMin)>atoi(wordMin))
	{
		printf("%s\n", "您输入的分钟不符合标准，请重新输入");
		return FAIL;
	}

	char wordForm[10];
	int i = 18;
	for (; str[i]; i++)
		wordForm[i - 18] = str[i];
	wordForm[i-18] = '\0';
	if (strcmp(wordForm, "每工作日") == 0 || strcmp(wordForm, "单次") == 0 || strcmp(wordForm, "每天") == 0)
		return OK;
	else
	{
		printf("%s\n", "您输入的形式不符合标准，请重新输入");
		return FAIL;
	}
}
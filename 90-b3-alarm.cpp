/*1551445 ͯ���� �������ѧ�뼼��1��*/
#define _CRT_SECURE_NO_WARNINGS
#include"cmd_console_tools.h"
#include"90-b3.h"


Status printSettedAlarm(fstream &file)//�����ǰʱ���Լ��Ѿ����õ����� 
{
	system("cls");
	char timeArr[64];
	cout << "\n\n                          ��ǰʱ��Ϊ��";

	time_t t = time(0);
	strftime(timeArr, 64, "%Y��%m��%d��%X", localtime(&t));
	puts(timeArr);

	cout << "\n   -----------------------------------------------------------------------------" << endl;
	cout << "\n    �������õ����ӣ�\n\n";

	char record[80];
	int recordNum = 0;//��¼����
	file.clear();
	file.seekg(0, ios::beg);
	while (1)
	{
		if (file.peek() == '\r')
			file.ignore();//����\r,��Ϊ�������ļ�������Ҫ\r\n  ������������
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
	printf("%s\n", "        |  ��ӣ�I�� |");
	printf("        %s\n", "--------------");
	
	gotoxy(hout,30, 30);
	printf("        %s\n", "--------------");
	gotoxy(hout, 30, 31);
	printf("%s\n", "        |  ɾ����D�� |");
	gotoxy(hout,30, 32);
	printf("        %s\n", "--------------");

	gotoxy(hout, 60, 30);
	printf("        %s\n", "--------------");
	gotoxy(hout, 60, 31);
	printf("%s\n", "        |  ���أ�R�� |");
	gotoxy(hout, 60, 32);
	printf("        %s\n", "--------------");
}

Status alarmSet()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setconsoleborder(hout, 100, BORDER_LINE);
	setfontsize(hout, L"�¿���", 16);
	fstream file(fname, ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		printf("%s", "�ļ���ʧ��");
		return FAIL;
	}

	char choice;
	while (1)
	{
		printSettedAlarm(file);
		buttonPrint();
		printf("%s", "����������룺");
		scanf("%c", &choice);
		if (choice == 'I')//���
			alarmInsert(file);
		else if (choice == 'D')//ɾ��
		{
			if(!alarmDelete(file))//���û���ҵ�Ҫ��ɾ���ļ�¼
				printf("%s\n","��Ǹ����û�����ø�ʱ�������");
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
	cin.clear();//������������ǰ���������Ļس���
	cin.sync();
	printf("   \n%s", "  ��������Ҫ���õ�ʱ��(��ȷ���֣�2020 01 01 00��00ǰ)���Լ���ʽ��ÿ�죬ÿ�����գ����Σ���\n\n  �硰2017 04 08 12��00*ÿ�족,\n\n  ��*��Ϊ�ָ��,��#��Ϊ��������\n\n");
	printf("\n\n %s", "  �����������Ϣ\n");
	
	while (1)
	{
		cin.clear();//������������ǰ���������Ļس���
		cin.sync();
		cin.getline(insertInfo, 80, '#');//��#��Ϊ����
		if (addInfoCheck(insertInfo)==OK)
			break;
	}
	int l = strlen(insertInfo);
	insertInfo[l] = '#';//�����ļ���ĩβҲ��Ҫ��#�����ȡʱ�����ж�
	insertInfo[l + 1] = '\0';
	file.clear();
	file.seekp(0, ios::end);
	file.write(insertInfo, strlen(insertInfo));
	file.write("\r\n",2);

	gotoxy(hout,50, 10);
	printf("%s", "  ��ӳɹ���");
	gotoxy(hout,50, 14);
	printf("%s\n", "-------------");
	gotoxy(hout,50, 15);
	printf("%s\n", "|  ���أ�B��|");
	gotoxy(hout,50, 16);
	printf("%s\n", "-------------");

	while (cin.get() != 'B');//����B����
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
	printf("   \n%s", "��������Ҫɾ�����ǵڼ������ã�\n\n");
	cin >> index;//���ڶ�λ������Ҫ���ļ���һ��һ���ȶ�
	
	/*����Ҫɾ���ļ�¼����ļ�¼�����tmpArr��̬������
	����experimental::filesystem::resize_file(fname, index);���ļ���С��ֻʣ��Ҫɾ����¼��ǰ�漸��
	���ļ�ĩβ�����tmpArr�����е��ļ�����*/
	file.clear();
	file.seekg(0, ios::end);
	int fileLength = (int)file.tellg();
	file.clear();
	file.seekg(0, ios::beg);
	for (int i = 0;i<index-1||fileLength==0; i++)//���û�м�¼ҲҪ����������Ҳ�����¼����ʾ
	{
		file.getline(str, 80);
		if (file.peek() == EOF||!fileLength)
		{
			printf("%s\n", "��Ǹ����û�����ø�����!");
			gotoxy(hout, 25, 14);
			printf("%s\n", "-------------");
			gotoxy(hout, 25, 15);
			printf("%s\n", "|  ���أ�B��|");
			gotoxy(hout, 25, 16);
			printf("%s\n", "-------------");

			while (cin.get() != 'B');//����B����
			return FAIL;
		}
	}
	file.clear();//����Ҫ
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
		printf("%s", "����ռ�ʧ��");
		return FAIL;
	}
	
	file.read(tmpArr, fileLength - index2);
	experimental::filesystem::resize_file(fname, index-1);
	file.seekp(0, ios::end);
	file.write(tmpArr, fileLength - index2);
	free(tmpArr);


	gotoxy(hout, 25, 10);
	printf("%s", "  ɾ���ɹ���");
	gotoxy(hout, 25, 14);
	printf("%s\n", "-------------");
	gotoxy(hout, 25, 15);
	printf("%s\n", "|  ���أ�B��|");
	gotoxy(hout, 25, 16);
	printf("%s\n", "-------------");

	while (cin.get() != 'B');//����B����
	return OK;
}


Status itIsTime(char *timeArr)
{
	fstream file(fname, ios::in | ios::binary|ios::out);
	if (file.is_open()==0)
	{
		printf("%s", "�ļ���ʧ��");
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
		int index1 = (int)file.tellg();//��¼��Ҫɾ���ļ�¼ͷ����λ��
		file.clear();
		file.getline(info, 80);
		if (strlen(info) < 2)
			continue;
		int index2 = (int)file.tellg();//��¼��Ҫɾ���ļ�¼��һ��ͷ����λ��
		file.clear();

		getInfo(info, tjTime, tjForm);
		if (strncmp(tjTime, s,16) == 0)
		{
		    
			if (strcmp(tjForm, "����") == 0)//���ֲ���֮�����Ҫɾ��������¼
			{
				char *tmpArr = (char *)malloc(sizeof(char)*(fileLength - index2 + 10));
				if (tmpArr == NULL)
				{
					printf("%s", "�ռ�����ʧ��");
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
			else if (strcmp(tjForm, "ÿ������") == 0)//��Ҫ���Ƿ��ǹ����ս����ж�
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
			else if (strcmp(tjForm, "ÿ��") == 0)
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
		printf("%s\n", "�������ʱ���ʽ���ԣ�����������");
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
		printf("%s\n", "�������ʱ���ʽ���ԣ�����������");
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
		printf("%s\n", "���������ݲ����ϱ�׼������������");
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
		printf("%s\n", "��������·ݲ����ϱ�׼������������");
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
		printf("%s\n", "����������ڲ����ϱ�׼������������");
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
		printf("%s\n", "�������Сʱ�����ϱ�׼������������");
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
		printf("%s\n", "������ķ��Ӳ����ϱ�׼������������");
		return FAIL;
	}

	char wordForm[10];
	int i = 18;
	for (; str[i]; i++)
		wordForm[i - 18] = str[i];
	wordForm[i-18] = '\0';
	if (strcmp(wordForm, "ÿ������") == 0 || strcmp(wordForm, "����") == 0 || strcmp(wordForm, "ÿ��") == 0)
		return OK;
	else
	{
		printf("%s\n", "���������ʽ�����ϱ�׼������������");
		return FAIL;
	}
}
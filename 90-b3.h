#pragma once
/*1551445 ͯ���� �������ѧ�뼼��1��*/

#include<iostream>
#include<fstream>
#include<stdlib.h>//C��ʽ�Ķ�̬����
#include<time.h>//��ȡʱ��ĺ���
#include<stdio.h>
#include<Windows.h>
#include <io.h>
#include<conio.h>
#include <mmsystem.h>
#include <experimental/filesystem>
#pragma comment (lib, "winmm.lib")
using namespace std;

#define FAIL -1
#define OK 0
#define YES 1
#define NO 0

typedef int Status;




#define EBASEX 30
#define EBASEY 30
#define BORDER_COL 300
#define BORDER_LINE 160
#define A 90//��Բ����Բ��ʱ��������a
#define B 45//��Բ����Բ��ʱ��������b
#define X 100//Բ��λ��xֵ
#define Y 50//Բ��λ��yֵ
#define SLEN 40
#define MLEN 30
#define HLEN 15
#define PI 3.1415926
#define fname "alarmRecord.txt"

/*���ߺ���*/
void printMenu();
void checkInput(char *choice);
Status printBitMapWord(unsigned char *word,int baseX,int baseY);
Status printBitMapStr(unsigned char *str, int baseX, int baseY);
void printFigure(char value, int baseX, int baseY);

/*clockʵ�ֺ���*/
void printEClockFrame();
void printEClock();
void printDate();
void printPClockFrame();
void printPClock();

/*alarmʵ�ֺ���*/
Status printSettedAlarm(fstream &file);
void buttonPrint();
Status alarmSet();
void alarmInsert(fstream &file);
Status alarmDelete(fstream &file);
void getInfo(char *str, char *tjTime, char *tjForm);
Status itIsTime(char *timeArr);
Status addInfoCheck(char *str);
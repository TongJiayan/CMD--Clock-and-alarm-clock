#pragma once
/*1551445 童佳燕 计算机科学与技术1班*/

#include<iostream>
#include<fstream>
#include<stdlib.h>//C方式的动态申请
#include<time.h>//获取时间的函数
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
#define A 90//画圆（椭圆）时函数参数a
#define B 45//画圆（椭圆）时函数参数b
#define X 100//圆心位置x值
#define Y 50//圆心位置y值
#define SLEN 40
#define MLEN 30
#define HLEN 15
#define PI 3.1415926
#define fname "alarmRecord.txt"

/*工具函数*/
void printMenu();
void checkInput(char *choice);
Status printBitMapWord(unsigned char *word,int baseX,int baseY);
Status printBitMapStr(unsigned char *str, int baseX, int baseY);
void printFigure(char value, int baseX, int baseY);

/*clock实现函数*/
void printEClockFrame();
void printEClock();
void printDate();
void printPClockFrame();
void printPClock();

/*alarm实现函数*/
Status printSettedAlarm(fstream &file);
void buttonPrint();
Status alarmSet();
void alarmInsert(fstream &file);
Status alarmDelete(fstream &file);
void getInfo(char *str, char *tjTime, char *tjForm);
Status itIsTime(char *timeArr);
Status addInfoCheck(char *str);
#include "stdafx.h"
#include <string>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <random>

#define BUFFERSIZE 32
#define STRINGLENGTH 256
#define escape 27


using namespace std;

void CLibFunc(char inputFilesPath[]);
void WinFunc(char inputFilesPath[]);
void SecWinFunc(char inputFilesPath[]);
void DataGenerator();
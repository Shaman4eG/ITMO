// TestCritical.cpp : Defines the entry point for the console application.
//


#include <windows.h>
#include <iostream>
#include <string>
#include <process.h>

#define MAX_ARRAY 13

CRITICAL_SECTION critsect;

int array[MAX_ARRAY];

void EmptyArray(void *);
void PrintArray(void *);
void FillArray(void *);

using namespace std;

int main()
{

	InitializeCriticalSection(&critsect);
	if (_beginthread(FillArray,1024,NULL)==-1)
		cout << "Error begin thread " << endl; 
	if (_beginthread(PrintArray,1024,NULL)==-1)
		cout << "Error begin thread " << endl; 
	if (_beginthread(EmptyArray,1024,NULL)==-1)
		cout << "Error begin thread " << endl;
	if (_beginthread(PrintArray,1024,NULL)==-1)
		cout << "Error begin thread " << endl;
	if (_beginthread(FillArray,1024,NULL)==-1)
		cout << "Error begin thread " << endl;
	if (_beginthread(PrintArray,1024,NULL)==-1)
		cout << "Error begin thread " << endl; 
	system("Pause");
	return 0;
}

void EmptyArray(void *)
{
	EnterCriticalSection(&critsect);
	cout << "EmptyArray" << endl;
	for (int x=0;x<(MAX_ARRAY+1); x++) array[x]=0;
	Sleep(1000);
	LeaveCriticalSection(&critsect);
	_endthread();
}

void PrintArray(void *)
{
	EnterCriticalSection(&critsect);
	cout << "PrintArray" << endl;
	for (int x=0;x<(MAX_ARRAY+1); x++) cout << array[x] << " ";
	cout << endl;
	Sleep(1000);
	LeaveCriticalSection(&critsect);
	_endthread();
}

void FillArray(void *)
{
	EnterCriticalSection(&critsect);
	cout << "FillArray" << endl;
	for (int x=0;x<(MAX_ARRAY+1); x++) array[x]=x;
	Sleep(1000);
	LeaveCriticalSection(&critsect);
	_endthread();
}
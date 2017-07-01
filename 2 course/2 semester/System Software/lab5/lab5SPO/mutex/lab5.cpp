#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

#define FILE_1 "file1"
#define FILE_2 "file2"
#define FILE_3 "file3"
#define THREADS_NUMBER 3
using namespace std;

HANDLE hMutex;

DWORD WINAPI Output_without_mutex(CONST LPVOID path)
{
	char buf[50];
	ifstream ifs((char*)path);
	
	while (!ifs.eof())
	{
		ifs.getline(buf, 256);
		cout << buf<< endl;
	}
	ifs.close();
}


DWORD WINAPI Output_with_mutex(CONST LPVOID path)
{
	
	WaitForSingleObject(hMutex, INFINITE);
	char buf[50];
	ifstream ifs((char*)path);
	
	while (!ifs.eof())
	{
		ifs.getline(buf, 256);
		cout << buf<< endl;
	}
	ifs.close();
	ReleaseMutex(hMutex);
	cout << "Mutex Released"<< endl;
}

void Output(int i)
{
	
	LPTHREAD_START_ROUTINE lpstart=NULL;
	if (i==1)
	{
		lpstart=&Output_without_mutex;
	}else
	{
		lpstart = &Output_with_mutex;
		hMutex = CreateMutex(NULL, false, NULL);
		cout << "Mutex Opened\n"<< endl;
	}
	
	char *Paths[3]={"file1.txt", "file2.txt", "file3.txt"};
	HANDLE hThreads[THREADS_NUMBER];
	for (int i=0; i<3; i++)
	{
		hThreads[i]=CreateThread(NULL, 0, lpstart, Paths[i],0, NULL);
	}
	WaitForMultipleObjects(THREADS_NUMBER, hThreads, TRUE, 1000*15);
}


int main()
{
	int i;
	cout << "1) Output without mutex\n2) Output with mutex\n";
	cin >> i;
	switch(i)
	{
		case 1:
		{
			Output(i);
			break;
		}
		
		case 2:
		{
			Output(i);
			break;
		}
	}
	cin >> i;
	return 0;
}
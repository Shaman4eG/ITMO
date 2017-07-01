#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
// TestEvent.cpp : Defines the entry point for the console application.
//

#include <process.h> 
using namespace std;

HANDLE event;

void Test1(void *);
void Test2(void *);
void Test3(void *);

int main()
{
	event=CreateEvent(NULL,true,false,"FirstStep");
	if (_beginthread(Test1,1024,NULL)==-1)
		cout << "Error begin thread " << endl;
	if (_beginthread(Test2,1024,NULL)==-1)
		cout << "Error begin thread " << endl;
	if (_beginthread(Test3,1024,NULL)==-1)
		cout << "Error begin thread " << endl;
	if (event!=NULL){
		Sleep(10);
		SetEvent(event);
		cout << "Set event " << endl;
		Sleep(1000);
		ResetEvent(event);
		cout << "Reset event " << endl;
		CloseHandle(event);
	} else {
		cout << "error create event" << endl;
	}
getchar();
	return 0;
}

void Test1(void *)
{
	DWORD dwWaitResult=3;
	while(dwWaitResult!=WAIT_OBJECT_0) {
		dwWaitResult = WaitForSingleObject(event,1);
		cout << "Test 1 TIMEOUT" << endl;
	}
	cout << "Event Test 1 " << endl;
	_endthread();
}

void Test2(void *)
{
	DWORD dwWaitResult=3;
	while(dwWaitResult!=WAIT_OBJECT_0){
		dwWaitResult = WaitForSingleObject(event,1);
		cout << "Test 2 TIMEOUT" << endl;
	}
	cout << "Event Test 2 " << endl;
	_endthread();
}

void Test3(void *)
{
	DWORD dwWaitResult=3;
	while(dwWaitResult!=WAIT_OBJECT_0){
		dwWaitResult = WaitForSingleObject(event,1);
		cout << "Test 3 TIMEOUT" << endl;
	}
	cout << "Event Test 3 " << endl;
	_endthread();
}
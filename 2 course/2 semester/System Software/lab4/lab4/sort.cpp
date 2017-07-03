#include <windows.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

#define SIZE 5001

void insertionSortUp(int *arrayPtr, int length) ;
void insertionSortDown(int *arrayPtr, int length); 

int main(int argc, char** argv)
{
	if (argc!=3)
	{
		getchar();
		return 1;
	}
	
	string file_name = argv[2];
	string mod = argv[1];
	
	if(mod!="up" && mod!="down")
	{
		getchar();
		return 1;
	}
	
	ifstream ifs;
	ifs.open(file_name);
	int arr[SIZE];
	int i=0;
	
	while (!ifs.eof())
	{
		ifs >> arr[i];
		i++;
	}
	
	if (mod=="up")
		insertionSortUp(arr, --i);
	else
		insertionSortDown(arr, --i);
	
	ofstream ofs;
	ofs.open(file_name+"new");
	for (int j=0; j<i; j++)
		ofs << arr[j]<< endl;
	
	ofs.close();
	ifs.close();
	
	cout << "Array sorted" << endl;
	
	return 0;
}

void insertionSortUp(int *arrayPtr, int length) // ���������� ���������
{
    int temp, // ��������� ���������� ��� �������� �������� �������� ������������ �������
        item; // ������ ����������� ��������
    for (int counter = 1; counter < length; counter++)
    {
        temp = arrayPtr[counter]; // �������������� ��������� ���������� ������� ��������� �������� �������
        item = counter-1; // ���������� ������ ����������� �������� �������
        while(item >= 0 && arrayPtr[item] > temp) // ���� ������ �� ����� 0 � ���������� ������� ������� ������ ��������
        {
            arrayPtr[item + 1] = arrayPtr[item]; // ������������ ��������� �������
            arrayPtr[item] = temp;
            item--;
        }
    }
}

void insertionSortDown(int *arrayPtr, int length) // ���������� ���������
{
    int temp, // ��������� ���������� ��� �������� �������� �������� ������������ �������
        item; // ������ ����������� ��������
    for (int counter = 1; counter < length; counter++)
    {
        temp = arrayPtr[counter]; // �������������� ��������� ���������� ������� ��������� �������� �������
        item = counter-1; // ���������� ������ ����������� �������� �������
        while(item >= 0 && arrayPtr[item] < temp) // ���� ������ �� ����� 0 � ���������� ������� ������� ������ ��������
        {
            arrayPtr[item + 1] = arrayPtr[item]; // ������������ ��������� �������
            arrayPtr[item] = temp;
            item--;
        }
    }
}


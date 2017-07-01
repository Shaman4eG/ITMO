#include<iostream>
#include<fstream>
#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<string>

using namespace std;

int main(int argc, char** argv)
{
	/*
		this shit generates file with random numbers for sorting programms
		PARAMETERS
		0 - prog name(obviously)
		1 - file name
		2 - lenght
		3 - down border for elements
		4 - up border 	-"-
		
		*/
	if(argc!=5)
		return 1;
	
	
	
	string Name = argv[1];
	int length = stoi(argv[2]);
	int down_border = stoi(argv[3]);
	int up_border = stoi(argv[4]);
	
	if (down_border>up_border)
		return 1;
	
	ofstream ofs;
	ofs.open(Name);
	
	srand(time(NULL));
	for (int i=0; i<length; i++)
	{
		ofs << rand()%(up_border-down_border)+down_border << endl;
	}
	ofs.close();
	return 0;
}
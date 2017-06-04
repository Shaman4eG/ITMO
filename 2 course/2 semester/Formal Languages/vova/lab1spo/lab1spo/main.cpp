#include "./Headers/Lab1Header.h"

int main()
{
	char choise;
	CHAR currentDirectory[BUFFERSIZE];
	do
	{
		system("cls");
		std::cout << " \tLab2." << endl;
		//std::cout << " 1 - Library function." << endl;
		//std::cout << " 2 - Windows function." << endl;
		//std::cout << " 3 - Second function." << endl;
		//std::cout << " 4 - Generate data file." << endl;
		//std::cout << " 5 - Second part." << endl;
		//std::cout << "esc-Exit." << endl;
		//choise = _getch();
		time_t secondsStart = time(NULL);
		switch (choise)
		{
		case '1':
		{
			//CLibFunc(".\\Data\\inputData.txt");
			break;
		}
		case '2':
		{
			//WinFunc(".\\Data\\inputData.txt");
			break;
		}
		case '3':
		{
			//SecWinFunc(".\\Data\\inputData.txt");
			break;
		}
		case '4':
		{
			//DataGenerator();
			break;
		}
		case '5':
		{
			std::cout << "\'C\' library func | "
				<< "\'Windows\' API func | "
				<< "\'CopyFile\' func |" << endl;
			for (int i = 0; i < 5; i++)
			{
				char inputFilesPath[30];
				char numBuf[12];
				ZeroMemory(inputFilesPath, 30);
				inputFilesPath[0] = '.';
				strcat(inputFilesPath, "\\Data\\inputData");
				itoa(i, numBuf, 2);
				strcat(inputFilesPath, numBuf);
				strcat(inputFilesPath, ".txt");
				time_t cFuncSecondsStart = time(NULL);
				CLibFunc(inputFilesPath);
				time_t cFuncSecondsEnd = time(NULL);
				WinFunc(inputFilesPath);
				time_t winFuncSecondsEnd = time(NULL);
				SecWinFunc(inputFilesPath);
				time_t secWinFuncSecondsEnd = time(NULL);
				// Results of copying.
				std::cout << cFuncSecondsEnd - cFuncSecondsStart << "\t\t | "
					<< winFuncSecondsEnd - cFuncSecondsEnd << "\t\t      | "
					<< secWinFuncSecondsEnd - winFuncSecondsEnd << "\t\t| "
					<< endl;

			}
			break;
		}

		case escape:
		{
			return 0;
		}
		default:
		{
			continue;
		}
		}
		time_t secondsEnd = time(NULL);
		std::cout << "Total action time is: " << secondsEnd - secondsStart << " sec's." << endl;
		int bytes = GetCurrentDirectory((DWORD)STRINGLENGTH, (LPSTR)currentDirectory);
		std::cout << "Current directory is: " << currentDirectory << endl;
		system("pause");
	} while (true);
	system("pause");
	return 0;
}

void DataGenerator()
{
	FILE *inputFile = NULL;
	char inputFilesPath[24];
	strcpy(inputFilesPath, ".\\Data\\inputData.txt");
	char bufferForChar[12];
	char bufferForNumb[2];
	inputFile = fopen(inputFilesPath, "wb");
	std::cout << "Output file's location is: " << inputFilesPath << endl;
	for (int i = 0; i < 1000000; i++)
	{
		srand(time(NULL));
		int semesterNum, mark;
		char surname[11], lessonName[11];

		strcpy(surname, "Kluchnikov ");
		strcpy(bufferForChar, surname);
		fwrite(bufferForChar, 1, 11, inputFile);

		semesterNum = rand() % 4 + 1;
		itoa(semesterNum, bufferForNumb, 2);
		fwrite(bufferForNumb, 1, 1, inputFile);


		strcpy(lessonName, " SomeLesson");
		strcpy(bufferForChar, lessonName);
		fwrite(bufferForChar, 1, 12, inputFile);

		mark = rand() % 5 + 2;
		itoa(mark, bufferForNumb, 2);
		fwrite(bufferForNumb, 1, 2, inputFile);

		strcpy(bufferForNumb, "\r\n");
		fwrite(bufferForNumb, 1, 2, inputFile);
	}
	fclose(inputFile);
	for (int i = 0; i < 5; i++)
	{
		char numBuf[1];
		char inputFilesPath[30];
		char bufferForChar[12];
		ZeroMemory(inputFilesPath, 30);
		inputFilesPath[0] = '.';
		strcat(inputFilesPath, "\\Data\\inputData");
		itoa(i, numBuf, 2);
		strcat(inputFilesPath, numBuf);
		strcat(inputFilesPath, ".txt");
		inputFile = fopen(inputFilesPath, "wb");
		std::cout << "Output file's location is: " << inputFilesPath << endl;

		for (int j = 0; j < 1000000 * (2 + i); j++)
		{
			srand(time(NULL));
			int semesterNum, mark;
			char surname[11], lessonName[11];

			strcpy(surname, "Kluchnikov ");
			strcpy(bufferForChar, surname);
			fwrite(bufferForChar, 1, 11, inputFile);

			semesterNum = rand() % 4 + 1;
			itoa(semesterNum, bufferForNumb, 2);
			fwrite(bufferForNumb, 1, 1, inputFile);


			strcpy(lessonName, " SomeLesson");
			strcpy(bufferForChar, lessonName);
			fwrite(bufferForChar, 1, 12, inputFile);

			mark = rand() % 5 + 2;
			itoa(mark, bufferForNumb, 2);
			fwrite(bufferForNumb, 1, 2, inputFile);

			strcpy(bufferForNumb, "\r\n");
			fwrite(bufferForNumb, 1, 2, inputFile);
		}

		fclose(inputFile);
	}
}

void CLibFunc(char inputFilesPath[])
{

	FILE *inputFile = NULL, *outputFile = NULL;
	char outputFilesPath[] = ".\\Data\\outputData.txt";
	char buffer[BUFFERSIZE];
	size_t inputBufferSize, outputBufferSize;
	inputFile = fopen(inputFilesPath, "rb");
	outputFile = fopen(outputFilesPath, "wb");

	if (outputFile == NULL)
	{
		std::cout << "Error, cann't open destination file!" << endl;
		system("pause");
		return;
	}
	while (inputBufferSize = fread(buffer, 1, BUFFERSIZE, inputFile) > 0)
	{
		outputBufferSize = fwrite(buffer, 1, BUFFERSIZE, outputFile);
		//std::cout << buffer << endl;
	}
	fclose(inputFile);
	fclose(outputFile);
	return;
}

void WinFunc(char inputPath[])
{
	HANDLE inputHandle, outputHandle;
	DWORD numberOfInput, numberOfOutput;
	CHAR buffer[BUFFERSIZE];
	LPCSTR inputFilesPath = (LPCSTR)inputPath;
	LPCSTR outputFilesPath = ".\\Data\\outputData.txt";
	inputHandle = CreateFile(inputFilesPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (inputHandle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Cann't open input file." << endl;
		return;
	}
	outputHandle = CreateFile(outputFilesPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (outputHandle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Cann't open output file." << endl;
		return;
	}
	while (ReadFile(inputHandle, buffer, BUFFERSIZE, &numberOfInput, NULL) && numberOfInput > 0)
	{
		WriteFile(outputHandle, buffer, numberOfInput, &numberOfOutput, NULL);
	}

	if (numberOfInput > numberOfOutput)
	{
		std::cout << "Writing error!" << endl;
		system("pause");
		return;
	}
	CloseHandle(inputHandle);
	CloseHandle(outputHandle);
	return;
}

void SecWinFunc(char inputPath[])
{
	LPCSTR inputFilesPath = ".\\Data\\inputData.txt";
	LPCSTR outputFilesPath = ".\\Data\\outputData.txt";
	if (!CopyFile(inputFilesPath, outputFilesPath, FALSE))
	{
		std::cout << "Writing error!" << endl;

	}
	return;
}

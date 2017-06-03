#include <stdio.h>
#include <locale.h>
#include <Windows.h>

#define strSize 50
#define sentenceSize 1000

//ѕќћ≈Ќя“№ Ў–»‘“ ¬  ќЌ—ќЋ»

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Arguments were not found.");
		exit(1);
	}

	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода


	FILE *p_textF;
	int working = 1;

	while (working)
	{
		rewind(stdin);

		char currentSymbol;
		char wordKeeper[strSize];
		char wordFromFile[strSize];
		char currentSentence[sentenceSize];
		int i = 0;
		int j = 0;
		int charsInStr = 0;
		int charsInWordFromFile = 0;
		int numOfWordsMatches = 0;
		int lastSymbolNum = 0;

		if (NULL == (p_textF = fopen(argv[1], "r"))) //argv[1] "text.txt"
		{
			printf("Unable to open file\n");
			getchar();
			exit(2);
		}

		printf("Input word: ");
		scanf("%49[а-€ј-я]s", &wordKeeper);
		if (getchar() != '\n')
		{
			printf("Invalid input.\n");
			continue;
		}

		while (wordKeeper[charsInStr] != '\0')
		{
			charsInStr++;
		}

		i = 0;
		j = 0;
		while (EOF != (currentSymbol = fgetc(p_textF)))
		{
			if ((currentSymbol != ' ') && (currentSymbol != '.') && (currentSymbol != ',') && (currentSymbol != ';') && (currentSymbol != '\n'))
			{
				wordFromFile[i] = currentSymbol;
				i++;
			}
			else
			{
				charsInWordFromFile = i;
				for (i = 0; i < charsInStr; i++)
				{
					if (wordKeeper[i] != wordFromFile[i])
					{
						i = charsInStr;
					}
				}
				if ((i == charsInStr) && (charsInWordFromFile == charsInStr))
				{
					numOfWordsMatches++;
				}
				i = 0;
			}

			if ((currentSymbol != '.') && (currentSymbol != '\n'))
			{
				if (j < sentenceSize)
				{
					currentSentence[j] = currentSymbol;
					j++;
				}
				else
					j = 0;
			}
			else if (numOfWordsMatches > 0)
			{
				lastSymbolNum = j;
				for (j = 0; j < lastSymbolNum; j++)
				{
					printf("%c", currentSentence[j]);
				}
				printf(".\n");
				j = 0;
				numOfWordsMatches = 0;
			}
			else
			{
				j = 0;
			}
		}

		fclose(p_textF);
		working = 0;
		rewind(stdin);
	}
	getchar();
	return 0;
}

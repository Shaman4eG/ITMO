#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define arrayElements 5

void task1();
	
void array1InitialisationWithRandomFilling(double*);
	//int userArrayFillingAndVisualisation();
	void array1SortingAndVisualisation(double*);
	void part1(double*);
	void part2(double*);
		void MaxAndMinValuesSignCheck(double*, double*, double*);
		void ifNegative(int*, double*, double*, int*, int*, double*);
		void ifPositiveOrEqual(int*, double*, double*, int*, int*, double*);
		void betweenAbsNumsMultiplicationAndResult(int, int, int, int, double*);

/*

Task 2

*/
void task2();
	int dataInput(int*, int*, int*);
		int linesAndColumnsInputAndCheck(int);
	int array2InitialisationWithRandomFillingAndVisualisation(int*, int*, int*);
	void part1_2(int*);
	void part2_2(int*, int*, int*, int*);
		void linesCharacterEvaluation(int*, int*, int*, int*);
		void array2SortByLinesCharactersAndVisualisation(int*, int*, int*, int*);
void menu();
 
int main()
{
	short working = 1; 
	while (1 == working)
	{
		task1();
		task2();
		
		menu();
	}

	return 0;
}

void task1()
{
	double array1[arrayElements];

	array1InitialisationWithRandomFilling(array1);

	part1(array1);
	part2(array1);

	array1SortingAndVisualisation(array1);
}

void array1InitialisationWithRandomFilling(double *p_array1)
{
	srand(time(NULL));
	printf("Array1\n");
	int i = 0;
	for (i; i < arrayElements; i++)
	{
		p_array1[i] = (double)(((double)(rand() % 10 + 1)) / ((double)(rand() % 10 + 1)) * ((rand() % 2) ? 1 : -1));
		printf("%lf ", p_array1[i]);
	}
	printf("\n");	
}

void part1(double *p_array1)
{
	double sumOfPositive = 0;
	short i = 0;
	for (i; i < arrayElements; i++)
	{
		if (p_array1[i] > 0)
		{
			sumOfPositive += p_array1[i];
		}
	}
	printf("\nSum of positive elements of Array1:\n%lf \n", sumOfPositive);
}

void part2(double *p_array1)
{
	double minAbsoluteValue = fabs(p_array1[0]);
	int indexOfMinAbsoluteValue = 0;
	double maxAbsoluteValue = fabs(p_array1[0]);
	int indexOfMaxAbsoluteValue = 0;

	short i = 1;
	for (i; i < arrayElements; i++)
	{
			ifPositiveOrEqual(&i, &maxAbsoluteValue, &minAbsoluteValue, &indexOfMaxAbsoluteValue, &indexOfMinAbsoluteValue, p_array1);
	}
	betweenAbsNumsMultiplicationAndResult(indexOfMaxAbsoluteValue, indexOfMinAbsoluteValue, maxAbsoluteValue, minAbsoluteValue, p_array1);
}

void ifPositiveOrEqual(short *p_indexOfFor, double *p_maxAbsoluteValue, double *p_minAbsoluteValue, int *p_indexOfMaxAbsoluteValue, int *p_indexOfMinAbsoluteValue, double *p_array1)
{
	if (*p_maxAbsoluteValue < (fabs(p_array1[*p_indexOfFor])))
	{
		*p_maxAbsoluteValue = fabs(p_array1[*p_indexOfFor]);
		*p_indexOfMaxAbsoluteValue = *p_indexOfFor;
	}
	else if (*p_minAbsoluteValue > (fabs(p_array1[*p_indexOfFor])))
	{
		*p_minAbsoluteValue = fabs(p_array1[*p_indexOfFor]);
		*p_indexOfMinAbsoluteValue = *p_indexOfFor;
	}
}

void betweenAbsNumsMultiplicationAndResult(int indexOfMaxAbsoluteValue, int indexOfMinAbsoluteValue, int maxAbsoluteValue, int minAbsoluteValue, double *p_array1)
{
	double resultOfAbsNumsMultiplication = 1;
	short i = 0;

	if (indexOfMaxAbsoluteValue > indexOfMinAbsoluteValue)
	{
		for (i = indexOfMinAbsoluteValue + 1; i < indexOfMaxAbsoluteValue; i++)
		{
			resultOfAbsNumsMultiplication *= p_array1[i];
		}
	}
	else
	{
		for (i = indexOfMaxAbsoluteValue + 1; i < indexOfMinAbsoluteValue; i++)
		{
			resultOfAbsNumsMultiplication *= p_array1[i];
		}
	}
	if (abs(indexOfMaxAbsoluteValue - indexOfMinAbsoluteValue) == 1)
	{
		resultOfAbsNumsMultiplication = 0;
	}

	printf("\nMultiplication of elements, which are situated between absolutes of highest and lowest numbers: \n%lf\n", resultOfAbsNumsMultiplication);
}

void array1SortingAndVisualisation(double *p_array1)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < arrayElements - 1; i++)
	{
		for (j = 0; j < arrayElements - i - 1; j++)
		{
			if (p_array1[j] < p_array1[j + 1])
			{
				double tmp = p_array1[j];
				p_array1[j] = p_array1[j + 1];
				p_array1[j + 1] = tmp;
			}
		}
	}

	i = 0;
	printf("\nSorted Array1:\n");
	for (i; i < arrayElements; i++)
	{
		printf("%lf ", p_array1[i]);
	}
	printf("\n");
}

void task2()
{
	int task2 = 1;
	while (1 == task2)
	{
		int numberOfLines = 0;
		int numberOfColumns = 0;
		int arraySize = 0;
		int failCheck = dataInput(&numberOfLines, &numberOfColumns, &arraySize);
		if (0 == failCheck)
		{
			continue;
		}
		int *p_array2;
		if ((p_array2 = (int*)malloc(arraySize*sizeof(int))) == NULL)
		{
			printf("Unable to allocate memory.\n");
			getchar();
			exit(1);
		}

		int *p_characterOfLine;
		if ((p_characterOfLine = (int*)malloc(arraySize*sizeof(int))) == NULL)
		{
			printf("Unable to allocate memory.\n");
			getchar();
			exit(1);
		}

		array2InitialisationWithRandomFillingAndVisualisation(&arraySize, p_array2, &numberOfColumns);
		
		part1_2(p_array2, &numberOfColumns, &arraySize);
		part2_2(p_characterOfLine, p_array2, &numberOfLines, &numberOfColumns);

		free(p_array2);
		free(p_characterOfLine);
		task2 = 0;
	}
}

int dataInput(int *p_numberOfLines, int *p_numberOfColumns, int *p_arraySize)
{
	printf("\nNumber of lines: ");
	*p_numberOfLines = linesAndColumnsInputAndCheck(*p_numberOfLines);
	if (0 == *p_numberOfLines)
	{
		return 0;
	}

	printf("Number of columns: ");
	*p_numberOfColumns = linesAndColumnsInputAndCheck(*p_numberOfColumns);
	if (0 == *p_numberOfColumns)
	{
		return 0;
	}

	*p_arraySize = *p_numberOfLines * *p_numberOfColumns;

	return 1;
}

int linesAndColumnsInputAndCheck(int numOfLinesOrColumns)
{
	rewind(stdin);
	scanf("%3i", &numOfLinesOrColumns);
	if ((getchar() != '\n') || (numOfLinesOrColumns < 1))
	{
		printf("Invalid input.\n");
		rewind(stdin);
		return 0;
	}
	return numOfLinesOrColumns;
}

int array2InitialisationWithRandomFillingAndVisualisation(int *p_arraySize, int *p_p_array2, int *p_numberOfColumns)
{
	srand(time(NULL));

	printf("\nArray2:\n");

	int i = 0;
	int matrixMaker = 0;
	for (i; i < *p_arraySize; i++)
	{
		p_p_array2[i] = (int)((rand() % 10) * ((rand() % 2) ? 1 : -1));
		printf("%4i ", p_p_array2[i]);
		matrixMaker++;
		if (matrixMaker == *p_numberOfColumns)
		{
			printf("\n");
			matrixMaker = 0;
		}
	}
	printf("\n");

	return 0;
}

void part1_2(int *p_p_array2, int *p_numberOfColumns, int *p_arraySize)
{
	int i = 0;
	int j = 0;
	short zeroInColumn = 0;
	int columnsWithoutZero = 0;
	for (j; j < *p_numberOfColumns; j++)
	{
		zeroInColumn = 0;
		for (i = j; i < *p_arraySize; i += *p_numberOfColumns)
		{
			if (0 == p_p_array2[i])
			{
				zeroInColumn = 1;
				break;
			}
		}
		if (zeroInColumn == 0)
		{
			columnsWithoutZero++;
		}
	}
	printf("\nColumns without zero = %i\n", columnsWithoutZero);
}

void part2_2(int *p_p_characterOfLine, int *p_p_array2, int *p_numberOfLines, int *p_numberOfColumns)
{
	linesCharacterEvaluation(p_p_characterOfLine, p_p_array2, p_numberOfLines, p_numberOfColumns);
	
	array2SortByLinesCharactersAndVisualisation(p_p_characterOfLine, p_p_array2, p_numberOfLines, p_numberOfColumns);
}

void linesCharacterEvaluation(int *p_p_characterOfLine, int *p_p_array2, int *p_numberOfLines, int *p_numberOfColumns)
{
	int j = 0;
	int i = 0;
	int currentLine = 1;
	printf("\nLines character:\n");
	for (j; j < *p_numberOfLines; j++)
	{
		p_p_characterOfLine[j] = 0;
		for (i; i < *p_numberOfColumns*currentLine; i++)
		{
			if ((0 == p_p_array2[i] % 2) && (p_p_array2[i] > 0))
			{
				p_p_characterOfLine[j] += p_p_array2[i];
			}
		}
		currentLine++;
		printf("p_p_characterOfLine[%i] = %i\n", j, p_p_characterOfLine[j]);
	}
}


void array2SortByLinesCharactersAndVisualisation(int *p_p_characterOfLine, int *p_p_array2, int *p_numberOfLines, int *p_numberOfColumns)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < *p_numberOfLines - 1; i++)
	{
		for (j = 0; j < *p_numberOfLines - i - 1; j++)
		{
			if (p_p_characterOfLine[j] > p_p_characterOfLine[j + 1])
			{
				int tmp = p_p_characterOfLine[j];
				p_p_characterOfLine[j] = p_p_characterOfLine[j + 1];
				p_p_characterOfLine[j + 1] = tmp;
				for (k = j * *p_numberOfColumns; k < (j + 1) * *p_numberOfColumns; k++)
				{
					tmp = p_p_array2[k];
					p_p_array2[k] = p_p_array2[k + *p_numberOfColumns];
					p_p_array2[k + *p_numberOfColumns] = tmp;
				}
			}
		}
	}

	
	printf("\nSorted Array2:\n");
	
	i = 0;
	int matrixMaker = 0;
	for (i; i < (*p_numberOfColumns)*(*p_numberOfLines); i++)
	{
		printf("%4i ", p_p_array2[i]);
		matrixMaker++;
		if (matrixMaker == *p_numberOfColumns)
		{
			printf("\n");
			matrixMaker = 0;
		}
	}
	printf("\n");
	printf("\n");
}

void menu()
{
	short working = 1;
	while (1 == working)
	{
		rewind(stdin);

		int menuItemNumber = 0;

		printf("1 - Evaluate\n");
		printf("2 - Quit\n");

		scanf("%i", &menuItemNumber);

		if (getchar() != '\n')
		{
			printf("Invalid input.\n\n");
			continue;
		}

		switch (menuItemNumber)
		{
			case 1:
			{
				working = 0;
				break;
			}
			case 2:
			{
				exit(0);
			}
			default:
			{
				printf("Invalid input.\n\n");
				continue;
			}
		}
	}
}

/*
	printf("p_p_characterOfLine = %p\n", p_p_characterOfLine);
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < *p_numberOfLines - 1; i++)
	{
		printf("i = %i  ", i);
		for (j = 0; j < *p_numberOfLines - i - 1; j++)
		{
			printf("j = %i\n", j);
			printf("%i > %i\n", p_p_characterOfLine[j], p_p_characterOfLine[j + 1]);
			if (p_p_characterOfLine[j] > p_p_characterOfLine[j + 1])
			{
				int tmp = p_p_characterOfLine[j];
				printf("tmp = %i\n", tmp);
				printf("& p_p_characterOfLine[%i] = %p\n", j, p_p_characterOfLine[j]);
				printf("& p_p_characterOfLine[%i] = %p\n", j + 1, p_p_characterOfLine[j + 1]);
				printf("INT p_p_characterOfLine[%i] = %i\n", j, p_p_characterOfLine[j]);
				printf("INT p_p_characterOfLine[%i] = %i\n", j + 1, p_p_characterOfLine[j + 1]);
				p_p_characterOfLine[j] = p_p_characterOfLine[j + 1];
				printf("& p_p_characterOfLine = %p\n", &p_p_characterOfLine);
				printf("NEJAVNO p_p_characterOfLine = %p\n", p_p_characterOfLine);
				printf("JAVNO p_p_characterOfLine = %p\n", p_p_characterOfLine[j]);
				printf("INT p_p_characterOfLine = %i\n", p_p_characterOfLine[j]);
				p_p_characterOfLine[j + 1] = tmp;
				printf("p_p_characterOfLine[%i] = %i\n", j, p_p_characterOfLine[j]);
				printf("p_p_characterOfLine[%i] = %i\n", j + 1, p_p_characterOfLine[j + 1]);
				for (k = j * *p_numberOfColumns; k < (j + 1) * *p_numberOfColumns; k++)
				{
					tmp = p_p_array2[k];
					p_p_array2[k] = p_p_array2[k + *p_numberOfColumns];
					p_p_array2[k + *p_numberOfColumns] = tmp;
					printf("p_p_array2[%i] = %i\n", k, p_p_array2[k]);
					printf("p_p_array2[%i] = %i\n", k + *p_numberOfColumns, p_p_array2[k + *p_numberOfColumns]);
				}
			}
		}
	}
*/
/*
int userArrayFillingAndVisualisation()
{
	short i = 0;
	for (i; i < arrayElements; i++)
	{
	printf("Input element number %i", i);
	printf(" of array: ");
	scanf("%lf", &array1[i]);
	if (getchar() != '\n')
		{
		printf("Invalid input.");
		rewind(stdin);
		return 0;
		}
	}
	return 1;
}
*/
#include <stdio.h>

void yeah(int *p_arraySize, int *p_p_array2, int *p_numberOfColumns)
{
	srand(time(NULL));

	printf("Array1\n");

	short i = 0;
	short matrixMaker = 0;
	for (i; i < *p_arraySize; i++)
	{
		p_p_array2[i] = (int)(rand() % 10); //((rand() % 2) ? 1 : -1));// / (double)(rand() % 10 + 1)) * ((rand() % 2) ? 1 : -1));
		printf("%6i ", p_p_array2[i]);
		matrixMaker++;
		if (matrixMaker == *p_numberOfColumns)
		{
			printf("\n");
			matrixMaker = 0;
		}
	}
	printf("\n");
}

int main()
{
	int *p_array2;
	int arraySize = 9;
	int numberOfColumns = 3;
	if ((p_array2 = (int*)malloc(arraySize  * sizeof(int))) == NULL)
	{
		printf("Unable to allocate memory.\n");
		getchar();
		exit(1);
	}
	yeah(&arraySize, p_array2, &numberOfColumns);
	getchar();

	return 0;
}

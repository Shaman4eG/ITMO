#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    //DATA INPUT AND ARRAY CREATION;
    int numberOfLines = 0;
    printf("Number of lines: ");
    scanf("%i", &numberOfLines);

    int numberOfColumns = 0;
    printf("Number of columns: ");
    scanf("%i", &numberOfColumns);

    int arraySize = numberOfLines * numberOfColumns;

    int *p_array2;
    if ((p_array2 = (int*) malloc(arraySize*sizeof(int))) == NULL)
    {
        printf("Unable to allocate memory.\n");
        getchar();
        exit(1);
    }

    // RANDOM ARRAY FILLING AND VISUALISATION
    srand(time(NULL));

	printf("Array1\n");

    short i = 0;
	short matrixMaker = 0;
	for (i; i < arraySize; i++)
	{
		p_array2[i] = (int)(rand() % 10); //((rand() % 2) ? 1 : -1));// / (double)(rand() % 10 + 1)) * ((rand() % 2) ? 1 : -1));
		printf("%6i ", p_array2[i]);
		matrixMaker++;
		if (matrixMaker == numberOfColumns)
        {
            printf("\n");
            matrixMaker = 0;
        }
	}
	printf("\n");

    //part1.2

	i = 0;
	short j = 0;
	short zeroInColumn = 0;
	short columnsWithoutZero = 0;
    for (j; j < numberOfColumns; j++)
    {
        zeroInColumn = 0;
        for (i = j; i < arraySize; i += numberOfColumns)
        {
            if (0 == p_array2[i])
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
    printf("Columns without zero = %i\n", columnsWithoutZero);

    int p_numberOfLines = 3;
    int p_arraySize = 9;

    int *p_p_characterOfLine;
    if ((p_p_characterOfLine = (int*)malloc(p_arraySize*sizeof(int))) == NULL)
    {
        printf("Unable to allocate memory.\n");
        getchar();
        exit(1);
    }

    /*int *p_p_array2;
    if ((p_p_array2 = (int*)malloc(p_arraySize*sizeof(int))) == NULL)
    {
        printf("Unable to allocate memory.\n");
        getchar();
        exit(1);
    */

    i = 0;
    for (i; i < arraySize; i++)
	{
        //((rand() % 2) ? 1 : -1));// / (double)(rand() % 10 + 1)) * ((rand() % 2) ? 1 : -1));
		printf("%2i ", p_array2[i]);
	}
    printf("\n");

	j = 0;
    i = 0;
    int currentLine = 1;
	for (j; j < p_numberOfLines; j++)
	{
		p_p_characterOfLine[j] = 0;
		for (i; i < numberOfColumns*currentLine; i++)
		{
		    printf("%2i \n", p_array2[i]);
			if ((0 == p_array2[i] % 2) && (p_array2[i] > 0))
			{
				p_p_characterOfLine[j] += p_array2[i];
			}
		}
		currentLine++;
		printf("p_p_characterOfLine[%i] = %i\n", j, p_p_characterOfLine[j]);
	}


    //

    free(p_array2);

    return 0;
}


#include <stdio.h>

int main()
{
    int *p_numberOfLines;
    int *p_arraySize;
    int a = 3;
    int b = 10;
    p_numberOfLines = &a;
    p_arraySize = &b;
    printf("*p_arraySize = %i\n", *p_arraySize);
    printf("p_arraySize = %p\n", p_arraySize);
    printf("%i\n", (*p_arraySize * (a+1)));
    printf("a = %i\n", a);
    printf("p_arraySize = %p\n", p_arraySize);


    /*int *p_p_characterOfLine;
    if ((p_p_characterOfLine = (int*)malloc(p_arraySize*sizeof(int))) == NULL)
    {
        printf("Unable to allocate memory.\n");
        getchar();
        exit(1);
    }

    int *p_p_array2;
    if ((p_p_array2 = (int*)malloc(p_arraySize*sizeof(int))) == NULL)
    {
        printf("Unable to allocate memory.\n");
        getchar();
        exit(1);
    }*/



	return 0;
}

















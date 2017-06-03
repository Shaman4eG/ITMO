#include <stdio.h>
#include <conio.h>
#include <math.h>

//йнпмх йбюдпюрмнцн спюбмемхъ
/*
void squareRoot(int a, int b, int c, float *p_x1, float *p_x2)
{	
	int D;

	D = b * b - 4 * a * c;
	if (D < 0)
	{
		printf("\nD < 0");
		getchar();
		exit(1);
	}
	else
	{
		*p_x1 = ((-b) + sqrt(D)) / (2 * a);
		printf("*p_x1 = %f\n", *p_x1);
		printf("p_x1 = %p\n", p_x1);
		*p_x2 = ((-b) - sqrt(D)) / (2 * a);
		printf("*p_x2 = %f\n", *p_x2);
		printf("p_x2 = %p\n", p_x2);
	}
}
*/

//дхмюлхвеяйне бшдекемхе оюлърх
/*
int kek(int *p_p_calloc1)
{
	printf("*p_calloc1[1] = %i\n", p_p_calloc1[1]);
	printf("*p_calloc1[1] = %p\n\n", &p_p_calloc1[1]);
	return *p_p_calloc1;
}
*/

int main()
{
	//дхмюлхвеяйне бшдекемхе оюлърх
	/*
	int size = 10;
	int *p_calloc1;

	//scanf("%i", &size);
	if (!(p_calloc1 = (int*)calloc(size, sizeof(int))))
		exit(1);
	printf("*p_calloc1 = %i\n", *p_calloc1);
	printf("p_calloc1  = %p\n\n", p_calloc1);
	int i = 0;
	for (i; i < size; i++)
	{
		printf("*p_calloc1[%i] = %i  ", i, p_calloc1[i]);
		printf("p_calloc1[%i] = %p\n", i, &p_calloc1[i]);
	}
	int sir = kek(p_calloc1);
	printf("sir = %i", sir);

	free(p_calloc1);
	p_calloc1 = NULL;
	*/

	
	//йнпмх йбюдпюрмнцн спюбмемхъ
	/*
	int a, b, c;
	float x1, x2;

	printf("a = ");
	scanf("%i", &a);
	printf("b = ");
	scanf("%i", &b);
	printf("c = ");
	scanf("%i", &c);
	printf("%+ix^2%+ix%+i = 0\n", a, b, c);
	rewind(stdin);

	squareRoot(a, b, c, &x1, &x2);

	printf("\nx1 = %f\nx2 = %f", x1, x2);
	*/
	
	//ярпнйх
	/*
	char kach[10] = "cash";
	int i;
	fgets(kach, 10, stdin);
	if ('\n' == kach[strlen(kach) - 1])
		kach[strlen(kach) - 1] = '\0';
	printf("%s\n", kach);
	puts(kach);
	fputs(kach, stdout);
	char *boro = kach;
	printf("\n&kach = %p\n", &kach);
	printf("boro = %p\n", boro);
	boro = &kach[3];
	printf("boro = %p\n", boro);
	printf("*boro = %c\n", *boro);
	for (i = 0; i < 10; i++)
	{
		if (kach[i] == '\0')
		{
			printf("\ngg\n");
			printf("%c", kach[i]);
			i = 10;
		}
		else
			printf("%c", kach[i]);
	}
	printf("\n%i", strlen(kach));
	*/
	
	//дбслепмше люяяхбш
	/*
	int a[2][3] = { 
					{1,2,3},
					{4,5,6} 
				  };
	int *p = &a[0][0];
	int i = 0;
	int j = 0;
	for (i; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("&a[%i][%i] = %p\n", i, j, &a[i][j]);
		}
	}
	printf("\n&p = %p\n", &p);
	printf("p  = %p\n", p);
	p += 2;
	printf("p  = %p\n", p);
	p += 1;
	printf("p  = %p\n", p);
	printf("\np[0] = %i or &%p\n", p[0], &p[0]);
	printf("p[1] = %i or &%p\n", p[1], &p[1]);
	printf("p[-1] = %i or &%p\n", p[-1], &p[-1]);
	printf("p[-4] = %i or &%p\n", p[-4], &p[-4]);
	printf("p[3] = %i or &%p\n", p[3], &p[3]);
	p = &a[0][0];
	//printf("p[1][1] = %i or &%p\n", p[1][1], &p[1][1]);
	*/
	
	/*
	int b[2][3] = {
					  {1,2,3},
					  {4,5,6}
				  };
	int *r = b;
	int i = 0;
	int j = 0;
	for (i; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("&b[%i][%i] = %p\n", i, j, &b[i][j]);
		}
	}
	printf("\n&b       = %p\n", &b);
	printf("b        = %p\n", b);
	printf("&b[0][0] = %p\n", &b[0][0]);
	printf("&b[1][1] = %p\n", &b[1][1]);
	printf("*b       = %p\n", *b);
	printf("b[0][0]  = %p\n", b[0][0]);
	printf("r        = %p\n", r);
	printf("*r       = %p\n", *r);
	r = b[0][0];
	printf("r        = %p\n", r);
	r = &b[0][0];
	printf("*r       = %p\n", *r);
	printf("r        = %p\n", r);

	printf("\n&b[0] = %p\n", &b[0]);
	printf("&b[1] = %p\n", &b[1]);
	printf("&b[2] = %p\n", &b[2]);
	printf("&b[3] = %p\n", &b[3]);
	printf("b[0] = %p\n", b[0]);
	printf("b[1] = %p\n", b[1]);
	printf("b[2] = %p\n", b[2]);
	printf("b[3] = %p\n", b[3]);
	printf("b[0][0] = %i\n", b[0][0]);
	printf("b[1][1] = %i\n", b[1][1]);
	printf("b[0][2] = %i\n", b[0][2]);
	printf("b[1][2] = %i\n\n", b[1][2]);
	
	printf("r        = %p\n", r[1]);
	printf("r        = %p\n", r[2]);
	printf("r        = %p\n", &r[0]);
	*/

	getch();
	return 0;
}
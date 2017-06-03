#include <stdio.h>

void menuVisualisation();
void menuNumberInputAndCheck(int*);
void menuNumberSwitch(int*);
void mathVariablesStorageAndInput();
int mathVariablesInputAndCheck(int*, int);
void funcChoice();

double radius = 0;
double xStart = 0;
double xFinish = 0;
double dx = 0;
double xNow = 0;

void main()
{
	short working = 1;

	while (working)
	{
		menuVisualisation();

		short menuNumberChosen = 0;
		menuNumberInputAndCheck(&menuNumberChosen);

		menuNumberSwitch(&menuNumberChosen);
	}
}


void menuVisualisation()
{
	printf("\n1 - Evaluate\n");
	printf("2 - Quit\n");
}

void menuNumberInputAndCheck(int *p_menuNumberChosen)
{
	rewind(stdin);
	scanf("%i", &*p_menuNumberChosen);
	if (getchar() != '\n')
	{
		*p_menuNumberChosen = 0;
	}
}

void menuNumberSwitch(int *p_menuItemNumber)
{
	switch (*p_menuItemNumber)
	{
		case 1:
		{
			mathVariablesStorageAndInput();
			break;
		}
		case 2:
		{
			exit();
		}
		default:
		{
			printf("Invalid input.\n");
			break;
		}
	}
}

void mathVariablesStorageAndInput()
{
	//printf("Note: arguments take only first 16 digits or 15, if fractional, 6 of which can be fractional.\n");
	/*scanf("%16lf", &xStart);
	rewind(stdin);
	printf("xFinish: ");
	scanf("%16lf", &xFinish);
	rewind(stdin);
	printf("dx: ");
	scanf("%16lf", &dx);
	rewind(stdin);*/

	short switchCounter = 1;
	while (switchCounter)
	{
		switch (switchCounter)
		{
			case 1:
			{
				printf("radius: ");
				switchCounter = mathVariablesInputAndCheck(&radius, switchCounter);
				break;
			}
			case 2:
			{
				printf("xStart: ");
				switchCounter = mathVariablesInputAndCheck(&xStart, switchCounter);
				break;
			}
			case 3:
			{
				printf("xFinish: ");
				switchCounter = mathVariablesInputAndCheck(&xFinish, switchCounter);
				break;
			}
			case 4:
			{
				printf("dx: ");
				switchCounter = mathVariablesInputAndCheck(&dx, switchCounter);
				break;
			}
			case 5:
			{
				xNow = xStart;
				funcChoice();
				return;
			}
			default:
			{
				printf("Invalid input.\n");
				return;
			}
		}
	}


	//printf("radius: %lf\n", radius);
	//printf("Start x: %lf\n", xStart);
	//printf("Finish x: %lf\n", xFinish);
	//printf("dx: %lf\n", dx);
}

int mathVariablesInputAndCheck(int *p_mathVariable, int switchCounter)
{
	scanf("%16lf", &*p_mathVariable);
	if (getchar() != '\n')
	{
		printf("Invalid input.\n");
		return 0;
	}
	rewind(stdin);
	return ++switchCounter;
}


void funcChoice()
{
	printf("gg\n");
	return;
}


/*
int a = 0;
scanf("%i", &a);
printf("a = %i\n", a);
*/





























































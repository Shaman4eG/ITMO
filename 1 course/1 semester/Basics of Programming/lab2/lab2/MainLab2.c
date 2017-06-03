#include <stdio.h>
#include <math.h>

void menuVisualisation();
void menuNumberInputAndCheck(int*);
void menuNumberSwitch(int*);
void mathVariablesInputInitiation();
int mathVariablesInputAndCheck(int*, int);
int radius_xStart_xFinish_dx_Checker();
void funcChoice();
void resultTableHeader();
void resultOutput();
void circleEvaluation();

double radius = 0;
double xStart = 0;
double xFinish = 0;
double dx = 0;
double xNow = 0;
double result = 0;

int main()
{
	short working = 1;
	mathVariablesInputInitiation();

	while (working)
	{
		menuVisualisation();

		short menuNumberChosen = 0;
		menuNumberInputAndCheck(&menuNumberChosen);

		menuNumberSwitch(&menuNumberChosen, &working);

		return 0;			
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
			mathVariablesInputInitiation();
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

void mathVariablesInputInitiation()
{
	//printf("Note: arguments take only first 16 digits or 15, if fractional, 6 of which can be fractional.\n");

	short switchCounter = 1;
	while (switchCounter)
	{
		switch (switchCounter)
		{
			case 1:
			{
				printf("Radius: ");
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
				switchCounter = radius_xStart_xFinish_dx_Checker();
				break;
			}
			case 5:
			{
				xNow = xStart;;
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

int radius_xStart_xFinish_dx_Checker()
{
	if (((xStart < xFinish) && (dx <= 0)) || ((xStart > xFinish) & (dx >= 0)) || (radius < 0))
	{
		if (radius < 0)
		{
			printf("Radius can't be negative.");
		}
		else
		{
			printf("Inappropriate dx. Unable to reach xFinish.\n");
		}
		return 0;
	}
	else if ((xStart > xFinish) && (dx < 0))
	{
		short keeper = xStart;
		xStart = xFinish;
		xFinish = keeper;
		dx *= -1;
	}
	return 5;
}

void funcChoice()
{
	resultTableHeader();
	while (xNow <= xFinish)
	{
		if (xNow <= -8)
		{
			result = -3;
			resultOutput();
			if ((radius >= 8) && (radius >= (-1*xNow)))
			{
				circleEvaluation();
			}
		}
		else if ((xNow > -8) && (xNow <= -3))
		{
			result = 0.6*xNow + 1.8;
			resultOutput();
			if (radius >= 3)
			{
				circleEvaluation();
			}
		}
		else if ((xNow > -3) && (xNow <= 3))
		{
			circleEvaluation();
		}
		else if ((xNow > 3) && (xNow <= 5))
		{
			result = xNow - 3;
			resultOutput();
			if (radius >= 3)
			{
				circleEvaluation();
			}
		}
		else if (xNow > 5)
		{
			result = 3;
			resultOutput();
			if ((radius > 5) && (radius >= xNow))
			{
				circleEvaluation();
			}
		}
		xNow += dx;
	}
	printf("|-----------------------------------|\n");
	return;
}

void resultTableHeader()
{
	printf("\n    Function values and arguments\n");
	printf("|-----------------------------------|\n");
	printf("|        X        |        Y        |\n");
	printf("|-----------------------------------|\n");
}

void resultOutput()
{
	if (xNow >= 0)
	{
		printf("|    %11.6lf    ", xNow);
	}
	else
	{
		printf("|    %11.6lf    ", xNow);
	}
	printf("|   %11.6lf |\n", result);
}

void circleEvaluation()
{
	result = -1 * sqrt(radius*radius - xNow*xNow);
	resultOutput();
}

/*
printf("radius: %lf\n", radius);
printf("Start x: %lf\n", xStart);
printf("Finish x: %lf\n", xFinish);
printf("dx: %lf\n", dx);
*/



























































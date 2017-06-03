#include <math.h>
#include <stdio.h>

int t = 0;

int overflow()
{
     t = 0;
     char str, ro;
     int mas[40];
     int i = 0;
     int l = 0;
     int k = 0;
     for (i = 0; ((str = getchar()) != '\n') && (i < 40); i++)
     {
        if (39 == i)
        {
            t = -1;
            return;
        }
        else if (isdigit(str))
        {
            mas[i] = atoi(&str);
            l++;
            if (t != 1)
            {
                k++;
            }

        }
        else if ((str == '.') && (t == 0))
        {
            mas[i] = 10;
            t++;
            l++;
        }
        else
        {
            t = -1;
            return;
        }
        ro = str;
     }

     float gg = 0;
     int d = -1;

     if ((t > -1) && (ro != '.'))
     {
        for (i = 0; i < (l-t); i++)
        {
            if (k != 0)
            {
                gg += pow(10,k-1)*mas[i];
                k--;
            }
            else
            {
                gg += pow(10,d)*mas[i+t];
                d--;
            }
        }
     }
     return gg;
}

void main(void)
{
	int working = 1;

	while (working)
	{
        fflush(stdin);

		short menuItemNumber = 0, Vvod1 = 0, a = 0;

		printf("1 - Evaluate\n");
		printf("2 - Quit\n");

        scanf("%i", &Vvod1);

        while (getchar()!='\n')
        {
            a++;
        }
        if (a > 0)
        {
            printf("Not valid number entered\n");
            continue;
        }

        menuItemNumber = Vvod1;

		switch (menuItemNumber)
		{
			case 1:
			{
				float arg1 = 0, result = 0, result2 = 0;
				short b = 0;
				char str[39];

				printf("Argument: ");

                arg1 = overflow();

                if (-1 == t)
                {
                    printf("Not valid number entered\n");
                    continue;
                }

				result = cosf(arg1) + sinf(arg1) + cosf(3*arg1) + sinf(3*arg1);
                result2 = 2 * sqrtf(2) * cosf(arg1) * sinf(M_PI / 4 + 2 * arg1);

				printf("Result: %f\n", result);
				printf("Result2: %f\n", result2);
				break;
			}
			case 2:
			{
				working = 0;
				break;
			}
			default:
			{
				printf("Wrong choice, please, try again.\n");
				break;
			}
		}
	}
}

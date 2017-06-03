#include <math.h>
#include <stdio.h>

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

                scanf("%f", &arg1);

                while (getchar()!='\n')
                {
                    b++;
                }
                if (b > 0)
                {
                    printf("Not valid number entered\n");
                    continue;
                }

                /*while (getchar()!='\n')
                    b++;
                if (b > 0)
                {
                    printf("Not valid number entered\n");
                    break;
                }*/

               /* int j, n = 0;
                int checker = arg1;
                while (checker != 0)
                {
                    checker /= 10;
                    printf("checker = %i\n", checker);
                    n++;
                }
                if (n > 39)
                {
                    printf("Too big argument entered\n");
                    continue;
                }*/

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

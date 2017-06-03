#include <stdio.h>

int main()
{
    short working = 1;
    printf("working = %i\n", working);
	while (1 == working)
	{
		rewind(stdin);
		printf("working = %i\n", working);

		int menuItemNumber = 0;

        printf("menuItemNumber = %i\n", menuItemNumber);
		printf("1 - Evaluate\n");
		printf("2 - Quit\n");

        printf("menuItemNumber = %i\n", menuItemNumber);
        printf("working = %i\n", working);
		scanf("%i", &menuItemNumber);
        printf("working = %i\n", working);

        printf("menuItemNumber = %i\n", menuItemNumber);
		if (getchar() != '\n')
		{
			printf("Invalid input.\n");
			continue;
		}

		printf("working = %i\n", working);
		printf("menuItemNumber = %i\n", menuItemNumber);
		switch (menuItemNumber)
		{
			case 1:
			{
			    printf("menuItemNumber = %i\n", menuItemNumber);
			    printf("working = %i\n", working);
				working = 0;
				printf("working = %i\n", working);
				break;
			}
			case 2:
			{
			    printf("menuItemNumber = %i\n", menuItemNumber);
			    printf("working = %i\n", working);
				exit(0);
			}
			default:
			{
			    printf("menuItemNumber = %i\n", menuItemNumber);
			    printf("working = %i\n", working);
				printf("Invalid input.\n");
				continue;
			}
		}
	}

    return 0;
}

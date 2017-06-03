#include <stdio.h>

void main()
{
	short working = 1;

	while (working)
	{
		rewind(stdin);

		short menuItemNumber = 0;
		short input1 = 0;

		printf("1 - Evaluate\n");
		printf("2 - Quit\n");

		scanf("%i", &menuItemNumber);
		if (getchar() != '\n')
		{
			printf("Not valid number entered\n");
			continue;
		}

		rewind
		(stdin);

		printf("ItemNumber = %i\n\n", menuItemNumber);

		switch (menuItemNumber)
		{
            case 1:
            {
                printf("case1\n");
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






























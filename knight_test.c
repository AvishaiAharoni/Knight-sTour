#include <stdio.h>	/* printf */

#include "knight.h"

int main()
{
	int i = 0;
	int j = 0;
/*	int count = 0;
	int can = 0;
	
	for (i = 0; i < 5; ++i)
	{
		for (j = 0; j < 5; ++j)
		{
			++can;
			if (SUCSSESS == KnightsTour(5, i, j))
			{
				++count;
			}
		}
	}
	
	printf("%d"\n", can);
	printf("%d\n", count);*/

	printf("insert number between 0 to 7 for row\n");
	scanf("%d", &i);
	printf("insert number between 0 to 7 for column\n");
	scanf("%d", &j);

	printf("for points: %d and %d:\n", i,j);

	if (SUCSSESS == KnightsTour(8, i, j))
	{
		printf("good points!\n");
	}
	else
	{
		printf("bad points!\n");
	}

	return (0);

}

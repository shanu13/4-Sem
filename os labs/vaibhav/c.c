	/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{

	char input = '\0';

	while (1)
	{
		input = getchar();

		if (input == EOF)
		{
			printf("\n");
			exit(0);
		}

		if (isalpha(input))
			input = (input > 91) ? input - 32 : input + 32;

		putchar(input);
	}

	return 0;
}

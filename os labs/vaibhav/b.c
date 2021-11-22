/*
 * Using fscanf and fprintf in the input and output
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	printf("EOF value: %d\n", EOF);

	int non_alpha_count = 0;
	//char input_string[];
	char input = '\0';

	while (1)
	{
		input = getchar();

		if (input == EOF)
		{
			fprintf(stderr, "Total non alphabetic characters count: %d\n", non_alpha_count);
			exit(0);
		}

		if (!isalpha(input))
			non_alpha_count++;

		putchar(input);
	//	printf("Character count: %d\n", non_alpha_count);
	}

	return 0;
}

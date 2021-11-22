/*
 * argc - tells the number of arguments during running the executable
 * 	By default, argc = 1, with one item being the name of program.
 *
 * argv - stores the arguments as a string as array of pointers
 *
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
//	printf("By default, Argument count: %d, Argument vector: %s\n", argc, *argv);
	int valid_arg = 0;

	for (int i = 1; i < argc; i++)
	{
		if (*(*(argv + i) + 0) == '-')
			continue;

		valid_arg++;
		printf("%s ", *(argv + i));
	}

	if (valid_arg)
		printf("\n");

	return 0;
}

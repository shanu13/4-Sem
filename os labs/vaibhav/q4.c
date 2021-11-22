

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>	
#include <unistd.h>

#define STDIN 0
#define STDOUT 1

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, " name of input or output file is missing.\n");
		exit(EXIT_FAILURE);
	}

	int fdInput = 0, fdOutput = 0;

	
	if ((fdInput = open(argv[1], O_RDONLY)) == -1)
	{
		perror("Input_File_Opening: ");
		exit(EXIT_FAILURE);
	}
	

	if ((fdOutput = creat(argv[2], 0644)) == -1)
	{
		perror("Output_File_Opening: ");
		exit(EXIT_FAILURE);
	}

	
	if (close(STDIN) == -1)
	{
		perror("Closing_STDIN_Parent: ");
		exit(EXIT_FAILURE);
	}

	if (dup(fdInput) == -1)
	{
		perror("dup_fdInput_Parent: ");
		exit(EXIT_FAILURE);
	}

	if (close(fdInput) == -1)
	{
		perror("Closing_fdInput: ");
		exit(EXIT_FAILURE);
	}

	
	if (close(STDOUT) == -1)
        {
                perror("Closing_STDOUT_Parent: ");
                exit(EXIT_FAILURE);
        }

        if (dup(fdOutput) == -1)
        {
                perror("dup_fdOutput_Parent: ");
                exit(EXIT_FAILURE);
        }

        if (close(fdOutput) == -1)
        {
                perror("Closing_fdOutput: ");
                exit(EXIT_FAILURE);
        }
	
	int fdPipe[2] = {0, 0};

	if (pipe(fdPipe) == -1)
	{
		perror("Pipelinig_Parent: ");
		exit(EXIT_FAILURE);
	}

	int read_fork = 0, write_fork = 0;
	int status = 0;

	printf(" I am going to fork the program.\n");

	read_fork = fork();

	if (read_fork > 0)
	{
		write_fork = fork();

		if (write_fork > 0)
		{
			close(fdPipe[STDOUT]);
			
			wait(&status);

			wait(&status);

		} else if (write_fork == 0)
		{
			if (close(STDOUT) == -1)
			{
				perror("Closing_STDOUT_Child: ");
				exit(EXIT_FAILURE);
			}

			if (dup(fdPipe[STDOUT]) == -1)
			{
				perror("Pipeling_STDOUT_Child: ");
				exit(EXIT_FAILURE);
			}

			if (close(fdPipe[STDOUT]) == -1)
			{
				perror("Closing_Pipeline_STDOUT_Child: ");
				exit(EXIT_FAILURE);
			}

			execl("./c", "./c", NULL);
		} else {
			perror("Forking_Write: ");
			exit(EXIT_FAILURE);
		}

		printf("Executed write child part\n");
	} else if (read_fork == 0)
	{
		if (close(STDIN) == -1) 
		{   
			perror("Closing_STDIN_Child: ");
			exit(EXIT_FAILURE);
		}   

		if (dup(fdPipe[STDIN]) == -1) 
		{
			perror("Pipeling_STDIN_Child: ");
			exit(EXIT_FAILURE);
		}   

		if (close(fdPipe[STDIN]) == -1) 
		{   
			perror("Closing_Pipeline_STDIN_Child: ");
			exit(EXIT_FAILURE);
		}

		close(fdPipe[STDOUT]);

		execl("./b", "./b", NULL);

		printf("Executed read child part.\n");
	} else {
		perror("Forking_Read: ");
		exit(EXIT_FAILURE);
	}

	close(fdPipe[STDIN]);
	close(fdPipe[STDOUT]);

	return 0;

}












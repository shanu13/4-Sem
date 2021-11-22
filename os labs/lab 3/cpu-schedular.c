
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_PROCESS 16
#define PROCESS_NAME 8

typedef struct
{
	char *name;
	int arrival;
	int cpuburst;
	int turnaround;
	int wait;
} Process;


Process processtable[MAX_PROCESS];
int given_processes = 0;

//Prints turnaround and wait time statistics
void PrintStatistics()
{
	int total_turnaround = 0, total_wait = 0;

	for (int i = 0; i < given_processes; i++)
	{
		total_turnaround += processtable[i].turnaround;
		total_wait += processtable[i].wait;
	}

	printf("\nTurnaround times: ");
	for (int i = 0; i < given_processes; i++)
		printf("%s[%d]  ", processtable[i].name, processtable[i].turnaround);
	printf("\n");

	printf("Wait times:\t  ");
	for (int i = 0; i < given_processes; i++)
		printf("%s[%d]  ",processtable[i].name, processtable[i].wait);
	printf("\n");

	printf("\nAverage turnaround time: %.2f\n", (float)total_turnaround / given_processes);
	printf("Average wait time: %.2f\n", (float)total_wait / given_processes);
}


//Resets the wait and turnaround time after a particular scheduling scheme is run
void Reset()
{
	for (int i = 0; i < given_processes; i++)
	{
		processtable[i].wait = 0;
		processtable[i].turnaround = 0;
	}
}


//implementation FCFS - First Come First Serve
void FCFS()
{
	int current_time = 0;
	int start_time = 0, end_time = 0;

	printf("\n-----------------------------------------------------\n"
			"         FIRST COME FIRST SERVE SCHEDULING\n"
			"-----------------------------------------------------\n\n");

	for (int i = 0; i < given_processes; i++)
	{
		start_time = current_time;
		end_time = processtable[i].cpuburst + start_time;

		processtable[i].wait = start_time - processtable[i].arrival;
		processtable[i].turnaround = end_time - processtable[i].arrival;

		current_time = end_time;

		printf("[%d-%d]\t %s running\n", start_time, end_time, processtable[i].name);
	}

	PrintStatistics();

	Reset();
}


void RR(int quantum)
{
	//manageing time burst
	int remaining_processes = given_processes;
	int index = 0;
	int current_time = 0, running_time = 0;

	int cpuburst_remaining[given_processes];
	for (int i = 0; i < given_processes; i++)
	{
		cpuburst_remaining[i] = processtable[i].cpuburst;
		//printf("CPU burst remaining at index %d is %d\n", i, cpuburst_remaining[i]);
	}

	printf("\n----------------------------------------------------\n"
			"		ROUND ROBIN SCHEDULING\n"
			"----------------------------------------------------\n\n");

	while (remaining_processes)
	{
		if (current_time >= processtable[index].arrival && cpuburst_remaining[index] != 0)
		{
			running_time = (cpuburst_remaining[index] - quantum) >= 0 ? quantum : cpuburst_remaining[index];

			//checking if remaining cpuburst is less than or equal to quantum
			if (running_time == cpuburst_remaining[index])
				remaining_processes--;

			for (int i = 0; i < given_processes; i++)
			{
				if (i == index)
				{
					cpuburst_remaining[index] -= running_time;
				} else
				{
					if (current_time + running_time >= processtable[i].arrival && cpuburst_remaining[i] != 0)
					{
						if (current_time < processtable[i].arrival)
							processtable[i].wait += current_time +running_time - processtable[i].arrival;
						else
							processtable[i].wait += running_time;
					}
				}
			}

		}

		if (running_time)
		{
			printf("[%d-%d]\t %s running\n", current_time, current_time + running_time, processtable[index].name);
			current_time += running_time;
		}

		index = (index + 1) % given_processes;
		running_time = 0;
	}

	//calculating total turnaround time
	for (int i = 0; i <given_processes; i++)
		processtable[i].turnaround = processtable[i].wait + processtable[i].cpuburst;

	PrintStatistics();

	Reset();
}


//Finds the next smallest process burst time and return its index
int shortest_remaining(int cpuburst_remaining[], int current_time)
{
	//printf("Current time in function: %d\n", current_time);

	int index = -1, value = INT_MAX;

	for (int i = 0; i < given_processes; i++)
	{
		if (cpuburst_remaining[i] && value > cpuburst_remaining[i] && current_time >= processtable[i].arrival)
		{
			value = cpuburst_remaining[i];
			index = i;
		}
	}

	//printf("current_time: %d, next_interrupt:%d, index: %d\n", current_time, value, index);

	return index;
}


//find next process arrival time and return it, if not more process to arrive or any other case return -1
int next_arrival(int current_time)
{
	for (int i = 0; i < given_processes; i++)
	{
		if (current_time < processtable[i].arrival)
			return processtable[i].arrival;
	}

	return -1;
}


void SRBF()
{
	int cpuburst_remaining[given_processes];
	for (int i = 0; i < given_processes; i++)
		cpuburst_remaining[i] = processtable[i].cpuburst;

	int remaining_processes = given_processes;
	int index = 0, current_time = 0, running_time = 0, next_interrupt = 0;

	printf("----------------------------------------------------------------\n"
		"	SHORTEST REMAINING BURST-TIME FIRST SCHEDULE\n"
		"----------------------------------------------------------------\n");

	while (remaining_processes)
	{
		if ((index = shortest_remaining(cpuburst_remaining, current_time)) != -1)
		{
			//printf("Got value of shortest_remaining at index %d\n", index);

			//gettng -1 as next_arrival means no new processes are arriving
			if ((next_interrupt = next_arrival(current_time)) != -1)
			{

				//printf("Got next_interrupt value %d\n", next_interrupt);

				if (current_time + cpuburst_remaining[index] <= next_interrupt)
					running_time = cpuburst_remaining[index];
				else
					running_time = next_interrupt - current_time;
			}else
			{
				running_time = cpuburst_remaining[index];
			}

			if (running_time == cpuburst_remaining[index])
				remaining_processes--;

			//printf("Running time: %d, remaining_processes: %d\n", running_time, remaining_processes);

			for (int j = 0; j < given_processes; j++)
			{
				if (index == j)
				{
					cpuburst_remaining[j] -= running_time;
				} else
				{
					if (cpuburst_remaining[j] != 0 && current_time >= processtable[j].arrival)
						processtable[j].wait += running_time;
				}
			}

			printf("[%d-%d]\t%s running\n", current_time, current_time + running_time, processtable[index].name);
			current_time += running_time;

			//printf("Current time: %d\n", current_time);
		}
	}

	for (int i = 0; i < given_processes; i++)
		processtable[i].turnaround = processtable[i].wait + processtable[i].cpuburst;

	PrintStatistics();

	Reset();
}


int main(int argc, char *argv[])
{
	//check if input file is present or not
	if (argc != 2)
	{
		perror("Input file missing");
		exit(EXIT_FAILURE);
	}

	//Read the input file using fscanf 
	FILE *fpInput = NULL;

	if ((fpInput = fopen(argv[1], "r")) == NULL)
	{
		perror("Error opening input file for reading processes: ");
		exit(EXIT_FAILURE);
	}

	//allocating processtable name with calloc
	for (int i = 0; i < MAX_PROCESS; i++)
		processtable[i].name = (char *) calloc (PROCESS_NAME, sizeof(char));


	//printf("Allocated name and now going for reading input from file\n");

	//reafing input from file and updating given_processes number
	for (int i = 0; i < MAX_PROCESS; i++)
	{
		if (!feof(fpInput))
		{
			fscanf(fpInput, " %s %d %d", processtable[i].name, &(processtable[i].arrival), &(processtable[i].cpuburst));
		} else
		{
			given_processes = i - 1;
			break;
		}
	}

	int selection = 0, quantum = 0;

	while (1)
	{
		printf("\n---------------------------------------------------------\n"
			"	CPU Scheduling Simulation\n"
			"---------------------------------------------------------\n"
			"Select the scheduling algorithm [1, 2, 3 or 4]:\n"
			"1. First Come First Serve (FCFS)\n"
			"2. Round Robin (RR)\n"
			"3. Shortest Remaining Burt-time First (SRBT)\n"
			"4. Exit\n");

		scanf("%d", &selection);

		if (selection == 4)
			break;

		switch (selection)
		{
			case 1:	FCFS();
				break;
			case 2: printf("Enter the quantum number: ");
				scanf("%d", &quantum);
				RR(quantum);
				break;
			case 3:	SRBF();
				break;
			default: printf("Invalid Selection\n");
				 break;
		}

		printf("\nHit any key to continue...\n");
		getchar();
		getchar();

	}

	//print_table();

	//FCFS();

	//Reset();

	//RR(2);

	//Reset();

	//SRBF();

	fclose(fpInput);

	return 0;
}

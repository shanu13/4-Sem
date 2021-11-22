#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/wait.h>


int main(int argc, char *argv[])
{
 int pipeEnds1[2];
 int fd_in, fd_out;
 int status;
 fd_in = open(argv[1], O_RDONLY);
 if (fd_in < 0)
 {
  fprintf(stderr, "No File\n");
  return 0;
 }
 fd_out=creat(argv[2],0644);
 if (fd_out < 0)
 {
  fprintf(stderr, "File creation Error\n");
  return 0;
 }

 close(0);

dup (fd_in);

close(1);
int f = dup(fd_out);
if(f<0)
{
	perror("Problem ");

}
 pipe(pipeEnds1);
 
 if (fork() > 0)
 {
  if (fork() > 0)
  {
   close(pipeEnds1[1]);
   close(pipeEnds1[0]);
   wait(&status);
   wait(&status);
  }
  else 
		{
			dup2(pipeEnds1[1],1);
			close(pipeEnds1[0]);
			execl("UpperLower", "UpperLower", (char *) 0);
		}
	}
	else {
		dup2(pipeEnds1[0],0);
		close(pipeEnds1[1]);
		execl("standardIO", "standardIO", (char *) 0);
	}
}

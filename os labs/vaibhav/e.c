#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include</usr/include/setjmp.h>
#include</usr/include/signal.h>

jmp_buf env[BUFSIZ];

void sig_handler(int sig);

int main(int argc, char* argv[]){
    int child_pid[2] = {-1};
    int n_present = 0;
    int fd_in = -1, fd_out = -1;
    
    if(argc > 1){
        if(argv[1][0] == '-'){
            n_present = 1;
            if(argc > 2){
                fd_in = open(argv[2], O_RDONLY);
                if(fd_in == -1){
                    fprintf(stderr, "Error in opening file %s : ", argv[2]);
                    perror("");
                    exit(1);
                }
                
                if(argc > 3){
                    fd_out = creat(argv[3], (1 << 9) - 1);
                    if(fd_out == -1){
                        fprintf(stderr, "Error in opening file %s : ", argv[3]);
                        perror("");
                        exit(1);
                    }
                }
            }
        }
        else{
            fd_in = open(argv[1], O_RDONLY);
            if(fd_in == -1){
                fprintf(stderr, "Error in opening file %s ", argv[1]);
                perror("");
                exit(1);
            }
            if(argc > 2){
                fd_out = creat(argv[2], (1 << 9) - 1);
                if(fd_out == -1){
                    fprintf(stderr, "Error in opening file %s ", argv[2]);
                    perror("");
                    exit(1);
                }
            }
        }
    }

    if(fd_in != -1){
        if(dup2(fd_in, 0) == -1){
            perror("Error in duping down to stdin");
            exit(2);
        }
        close(fd_in);
    }
    if(fd_out != -1){
        if(dup2(fd_out, 1) == -1){
            perror("Error in duping down to stdout");
            exit(2);
        }
        close(fd_out);
    }

    signal(SIGALRM, sig_handler);
    if(setjmp(env) != 0){
        // fake return
        kill(child_pid[0], SIGTERM);
        kill(child_pid[1], SIGTERM);
        fprintf(stderr, "Read timeout in second child, killing both children...\n");
        wait(NULL);
        wait(NULL);
        exit(1);
    }
    
    int fd[2];
    if(pipe(fd) == -1){
        perror("Error");
        exit(3);
    }
    
    alarm(15);
    if((child_pid[0] = fork()) > 0){
        if((child_pid[1] = fork()) > 0){
            int pid, status;
            close(fd[0]);
            close(fd[1]);
            while((pid = wait(&status)) > 0){
                fprintf(stderr, "Process %d with exit status %d\n", pid, WEXITSTATUS(status));
                if(pid == child_pid[1] && WEXITSTATUS(status) == 2){
                    int kill_val = kill(child_pid[0], SIGTERM);
                    if(kill_val == -1){
                        fprintf(stderr, "Convert is already dead!\n");
                    }
                    exit(2);
                }
            }
            wait(&status);
        }
        else{
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            fprintf(stderr, "Child 2 pid : %d\n", getpid());
            if(n_present > 0){
                execl("count", "count %s", argv[1], (char*) NULL);
            }
            execl("count", "count", (char*) NULL);
            
        }
    }
    else{
        // child 1
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        fprintf(stderr, "Child 1 pid : %d\n", getpid());
        execl("convert", "convert", (char*) NULL);
    }

    alarm(0);
    fprintf(stderr, "\nNormal children exit...\n");
    
    return 0;
}

void sig_handler(int sig){
    //fprintf(stderr, "Read timeout in second child, killing both children!\n");
    longjmp(env, 1);
}
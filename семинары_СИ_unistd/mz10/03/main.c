#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
int main(int argc, char **argv) { // cmd 1-3 file 1-2
    int fd[2];
    pipe(fd);
    int cm12 = fork();
    if (!cm12) {
        if (!fork()){
            dup2(fd[1], 1);
            close(fd[1]);
            int file = open(argv[4], O_RDONLY);
            dup2(file, 0);
            close(file);
            close(fd[0]);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
        int st;
        wait(&st);
        if (WIFEXITED(st) && WEXITSTATUS(st) == 0){
            dup2(fd[1], 1);
            close(fd[1]);
            close(fd[0]);
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
        exit(0);
    }
    pid_t cm3 = fork();
    if (!cm3){
        int file = open(argv[5], O_WRONLY | O_APPEND | O_WRONLY, 0660);
        dup2(file, 1);
        close(file);
        dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }
    int st3;
    waitpid(cm3, st3, 0);
    waitp
    int st;
    wait(&st);
    
    exit(1);
}
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv){
    enum 
    {
        YEAR = 1900
    };
    int fd[2];
    if (pipe(fd) < 0) {
        return 1;
    }
    struct tm *data;
    time_t t;
    pid_t pid_son = fork();
    if (!pid_son) {
        pid_son = fork();
        if (!pid_son) {
            pid_son = fork();
            if (!pid_son) {
                t = time(NULL);
                for (int i = 0; i < 3; ++i){
                    if (write(fd[1], &t, sizeof(t)) != sizeof(t)) {
                        exit(1);
                    }
                }
                exit(0);
            }
            wait(NULL);
            if (read(fd[0], &t, sizeof(t)) != sizeof(t)) {
                exit(1);
            }
            data = localtime(&t);
            printf("D:%02d\n", data->tm_mday);
            close(fd[0]);
            close(fd[1]);
            exit(0);
        }
        wait(NULL);
        if (read(fd[0], &t, sizeof(t)) != sizeof(t)){
            exit(1);
        }
        data = localtime(&t);
        printf("M:%02d\n", data->tm_mon + 1);
        close(fd[0]);
        close(fd[1]);
        exit(0);
    }
    wait(NULL);
    if (read(fd[0], &t, sizeof(t)) != sizeof(t)){
        exit(1);
    }
    data = localtime(&t);
    printf("Y:%04d\n", data->tm_year + YEAR);
    close(fd[0]);
    close(fd[1]);
    return 0;
}
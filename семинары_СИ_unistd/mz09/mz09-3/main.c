#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char **argv){
    if (argc != 4) {
        return 1;
    }
    pid_t id = fork();
    if (id == - 1){
        return 1;
    } else if (id == 0) {
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }
    int stat;
    wait(&stat);
    int flag = 1;
    if (!WIFEXITED(stat) || WEXITSTATUS(stat)) {
        flag = 0;
        id = fork();
        if (id == - 1){
            return 1;
        } else if (id == 0) {
            execlp(argv[2], argv[2], NULL);
            exit(1);
        }
        wait(&stat);
        if (WIFEXITED(stat) && WEXITSTATUS(stat) == 0) {
            flag = 1;
        }
    }
    if (flag) {
        flag = 0;
        id = fork();
        if (id == - 1){
            return 1;
        } else if (id == 0) {
            execlp(argv[3], argv[3], NULL);
            exit(1);
        }
        wait(&stat);
        if (WIFEXITED(stat) && WEXITSTATUS(stat) == 0) {
            flag = 1;
        }
    } 
    if (flag){
        return 0;
    } else {
        return 1;
    }
    return 0;
}
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
enum
{
    RIGHTS = 0660,
    RIGHT_ARGS = 5,
    IN = 0,
    OUT = 1,
    ERR = 2,
    ALL_FILES = 3
};
int main(int argc, char **argv) {
    if (argc != RIGHT_ARGS) {
        return 1;
    }
    pid_t id = fork();
    if (id == -1) {
        return 1;
    } else if (id == 0) {
        int fd[3];
        fd[IN] = open(argv[2], O_RDONLY);
        if (fd[IN] < 0){
            exit(42);
        }
        fd[OUT] = open(argv[3], O_APPEND | O_WRONLY | O_CREAT, RIGHTS);
        if (fd[OUT] < 0) {
            exit(42);
        }
        fd[ERR] = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, RIGHTS);
        if (fd[ERR] < 0) {
            exit(42);
        }
        if (dup2(fd[IN], STDIN_FILENO) == -1) {
            exit(42);
        }
        if (dup2(fd[OUT], STDOUT_FILENO) == -1) {
            exit(42);
        }
        if (dup2(fd[ERR], STDERR_FILENO) == -1) {
            exit(42);
        }
        if (close(fd[IN]) == -1){
            exit(42);
        }
        if (close(fd[OUT]) == -1){
            exit(42);
        }
        if (close(fd[ERR]) == -1) {
            exit(42);
        }
        execlp(argv[1], argv[1], NULL);
        exit(42);
    }
    int stat;
    wait(&stat);
    printf("%d\n", stat);
    return 0;
}
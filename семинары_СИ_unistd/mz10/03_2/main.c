#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <inttypes.h>
int main(int argc, char **argv) {
    enum
    {
        IN = 0,
        OUT = 1
    };
    if (argc != 6) {
        return 1;
    }
    int fd[2];
    if (pipe(fd) < 0) {
        return 1;
    }
    pid_t first_exp = fork();
    if (first_exp == 0) {
        close(fd[IN]);
        pid_t exp1 = fork();
        if (exp1 == 0) {
            int file_in = open(argv[4], O_RDONLY);
            if (file_in < 0) {
                close(fd[OUT]);
                exit(1);
            }
            if (dup2(file_in, STDIN_FILENO) == -1) {
                close(fd[OUT]);
                close(file_in);
                exit(1);
            }
            if (dup2(fd[OUT], STDOUT_FILENO) == -1) {
                close(fd[OUT]);
                close(file_in);
                exit(1);
            }
            close(fd[OUT]);
            close(file_in);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        } else if (exp1 == -1) {
            exit(1);
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                if (dup2(fd[OUT], STDOUT_FILENO) < 0) {
                    close(fd[OUT]);
                    exit(1);
                }
                close(fd[OUT]);
                execlp(argv[2], argv[2], NULL);
                _exit(1);
            } else {
                close(fd[OUT]);
                exit(1);
            }
        }
    } else if (first_exp == -1) {
        return 1;
    } else {
        pid_t last = fork();
        if (last == 0) {
            close(fd[OUT]);
            int file = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0660);
            if (file < 0) {
                close(fd[IN]);
                exit(1);
            }
            if (dup2(file, STDOUT_FILENO) < 0) {
                close(fd[IN]);
                close(file);
                exit(1);
            }
            close(file);
            if (dup2(fd[IN], STDIN_FILENO) < 0) {
                close(fd[IN]);
                exit(1);
            }
            close(fd[IN]);
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        } else if (last == -1) {
            return 1;
        } else {
            close(fd[IN]);
            close(fd[OUT]);
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}
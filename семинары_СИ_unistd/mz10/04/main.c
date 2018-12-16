#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <inttypes.h>

void kill_all(pid_t *pid, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        kill(pid[i], SIGKILL);
    }
    for (size_t i = 0; i < count; ++i) {
        wait(NULL);
    }
    free(pid);
}

int main(int argc, char **argv) {
    enum
    {
        IN = 0,
        OUT = 1
    };
    int fd[2][2]; // 0 - для пред 1 - для след
    pid_t *id = calloc(argc - 1, sizeof(*id));
    size_t count = 0;
    pipe(fd[0]);
    for (int i = 1; i < argc; ++i) {
        if (pipe(fd[1]) < 0) {
            kill_all(id, count);
            return 1;
        }
        pid_t pid = fork();
        if (pid == -1) {
            kill_all(id, count);
            return 1;
        } else if (pid == 0) {
            if (i != 1) {
                if (dup2(fd[0][IN], STDIN_FILENO) < 0){
                    exit(1);
                }
            } 
            close(fd[0][IN]);
            close(fd[0][OUT]);
            if (i != argc - 1) {
                if (dup2(fd[1][OUT], STDOUT_FILENO) < 0){
                    exit(1);
                }
            }
            close(fd[1][IN]);
            close(fd[1][OUT]);
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }
        id[count++] = pid;
        close(fd[0][IN]);
        close(fd[0][OUT]);
        fd[0][IN] = fd[1][IN];
        fd[0][OUT] = fd[1][OUT];
    }
    close(fd[0][IN]);
    close(fd[0][OUT]);
    free(id);
    for (int i = 1; i < argc; ++i) {
        wait(NULL);
    }
    return 0;
}
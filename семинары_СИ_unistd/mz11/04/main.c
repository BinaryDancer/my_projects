#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <inttypes.h>
#include <limits.h>

int target = 0;
FILE *in;
FILE *out;
void pingpong(int sig) {
    signal(SIGUSR1, pingpong);
}
int main(int argc, char **argv) {
    signal(SIGUSR1, pingpong);
    enum
    {
        IN = 0,
        OUT = 1
    };
    int max_shot;
    sscanf(argv[1], "%d", &max_shot);
    if (max_shot <= 1) {
        printf("Done\n");
        return 0;
    }
    int fd[2];
    if (pipe(fd) < 0) {
        return 1;
    }
    in = fdopen(fd[IN], "r");
    if (in == NULL) {
        close(fd[IN]);
        close(fd[OUT]);
        return 1;
    }
    out = fdopen(fd[OUT], "w");
    if (out == NULL) {
        fclose(in);
        close(fd[IN]);
        close(fd[OUT]);
        return 1;
    }
    int shot = 1;
    pid_t first = fork();
    if (!first) {
        signal(SIGUSR1, pingpong);
        fscanf(in, "%d", &target);
        while (fscanf(in, "%d", &shot) == 1) {
            printf("1 %d\n", shot);
            fflush(stdout);
            shot++;
            if (shot >= max_shot) {
                break;
            }
            fprintf(out, "%d ", shot);
            fflush(out);
            if (shot == max_shot - 1) {
                break;
            } else {
                kill(target, SIGUSR1);
            }
            pause();
        }
        fclose(in);
        fclose(out);
        close(fd[IN]);
        close(fd[OUT]);
        kill(target, SIGUSR1);
        exit(0);
    }
    target = first;
    pid_t second = fork();
    if (!second) {
        signal(SIGUSR1, pingpong);
        fprintf(out, "%d ", getpid());
        fflush(out);
        fprintf(out, "%d ", shot);
        fflush(out);
        pause();
        if (shot < max_shot - 1) {
            while (fscanf(in, "%d", &shot) == 1) {
                printf("2 %d\n", shot);
                fflush(stdout);
                shot++;
                if (shot >= max_shot) {
                    break;
                }
                fprintf(out, "%d ", shot);
                fflush(out);
                if (shot == max_shot - 1) {
                    break;
                } else {
                    kill(target, SIGUSR1);
                }
                pause();
            }
        }
        fclose(in);
        fclose(out);
        close(fd[IN]);
        close(fd[OUT]);
        kill(target, SIGUSR1); 

        exit(0);
    }
    fclose(in);
    fclose(out);
    close(fd[IN]);
    close(fd[OUT]);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    fflush(stdout);
    return 0;
}
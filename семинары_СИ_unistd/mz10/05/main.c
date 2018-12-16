#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
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
    if (argc < 2) {
        return 1;
    }
    int max_shot;
    sscanf(argv[1], "%d", &max_shot);
    int fd1[2];
    int fd2[2];
    if (pipe(fd1) < 0) {
        return 1;
    }
    if (pipe(fd2) < 0) {
        close(fd1[1]);
        close(fd1[0]);
        return 1;
    }
    if (!fork()) {
        close(fd2[IN]);
        close(fd1[OUT]);
        FILE *in = fdopen(fd1[IN], "r");
        if (in == NULL) {
            close(fd1[IN]);
            close(fd2[OUT]);
            exit(1);
        }
        FILE *out = fdopen(fd2[OUT], "w");
        if (out == NULL) {
            fclose(in);
            close(fd1[IN]);
            close(fd2[OUT]);
            exit(1);
        }
        int elem = 1;
        while (fscanf(in, "%d", &elem) == 1) {
            fprintf(stdout, "1 %d\n", elem);
            fflush(stdout);
            elem++;
            if (elem >= max_shot) {
                break;
            }
            fprintf(out, "%d ", elem);
            fflush(out);
        }
        fclose(in);
        fclose(out);
        close(fd1[IN]);
        close(fd2[OUT]);
        exit(0);
    }
    if (!fork()) {
        close(fd1[IN]);
        close(fd2[OUT]);
        FILE *in = fdopen(fd2[IN], "r");
        if (in == NULL) {
            close(fd2[IN]);
            close(fd1[OUT]);
            exit(1);
        }
        FILE *out = fdopen(fd1[OUT], "w");
        if (out == NULL) {
            fclose(in);
            close(fd2[IN]);
            close(fd1[OUT]);
            exit(1);
        }
        int elem = 1;
        if (elem < max_shot) {
            fprintf(out, "%d ", elem);
            fflush(out);
            while (fscanf(in, "%d", &elem) == 1) {
                fprintf(stdout, "2 %d\n", elem);
                fflush(stdout);
                elem++;
                if (elem >= max_shot) {
                    break;
                }
                fprintf(out, "%d ", elem);
                fflush(out);
            }
        }
        fclose(in);
        fclose(out);
        close(fd2[IN]);
        close(fd1[OUT]);
        exit(0);
    }
    close(fd1[IN]);
    close(fd1[OUT]);
    close(fd2[IN]);
    close(fd2[OUT]);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    return 0;
}
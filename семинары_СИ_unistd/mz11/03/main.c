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
#include <signal.h>
int main(int argc, char **argv){
    if (argc < 2){
        return 1;
    }
    int n;
    sscanf(argv[1], "%d", &n);
    char path[PATH_MAX];
    int min = (n > argc - 2) ? argc - 2 : n;
    for (int i = 0; i < min; ++i) {
        if (!fork()) {
            FILE *f = fopen(argv[i + 2], "r");
            fscanf(f, "%s", path);
            fclose(f);
            execlp(path, path, NULL);
            _exit(1);
        }
    }
    int count = 0;
    for (int i = 0; i < min; ++i) {
        int stat;
        wait(&stat);
        if  (WIFEXITED(stat) && WEXITSTATUS(stat) == 0){
            count++;
        }
    }
    for (int i = min + 2; i < argc; ++i) {
        if (!fork()) {
            FILE *f = fopen(argv[i], "r");
            fscanf(f, "%s", path);
            fclose(f);
            execlp(path, path, NULL);
            _exit(1);
        } else {
            int stat;
            wait(&stat);
            if  (WIFEXITED(stat) && WEXITSTATUS(stat) == 0){
                count++;
            }
        }
    }
    printf("%d\n", count);
    fflush(stdout);
    return 0;
}
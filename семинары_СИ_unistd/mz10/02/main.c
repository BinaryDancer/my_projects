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
int main(int argc, char **argv){
    int fd[2];
    pipe(fd);
    if (!fork()) {
        close(fd[1]);
        if (!fork()){
            int32_t elem;
            int64_t sum = 0;
            while(read(fd[0], &elem, sizeof(elem))){
                sum += elem;
            }
            printf("%"PRId64"\n", sum);
            close(fd[0]);
            exit(0);
        }
        close(fd[1]);
        wait(NULL);
        exit(0);
    }
    int32_t el;
    close(fd[0]);
    while (scanf("%"SCNd32, &el) == 1) {
        write(fd[1], &el, sizeof(el));
    }
    close(fd[1]);
    wait(NULL);
    return 0;
}
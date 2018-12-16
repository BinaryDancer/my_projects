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

void sig(int sign) {
    static int elem = 0;
    if (elem < 5) {
        printf("%d\n", elem++);
        fflush(stdout);
        signal(SIGHUP, sig);
    } else {
        exit(0);
    }
    
}
int main() {
    signal(SIGHUP, sig);
    int pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);
    for(;;) {
        pause();
    }
    return 0;
}
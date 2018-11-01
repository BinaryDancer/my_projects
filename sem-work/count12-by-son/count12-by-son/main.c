//
//  main.c
//  count12-by-son
//
//  Created by Мамаев Павел on 31/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
void usr1(int sig) {
    static int count = 0;
    printf("%d %d\n", 1, ++count);
}
void usr2(int sig) {
    static int count = 0;
    printf("%d %d\n", 2, ++count);
    fflush(stdout);
}
int main(int argc, const char * argv[]) {
    signal(SIGUSR1, usr1);
    pid_t ppid = getpid();
    pid_t pid;
    if (!(pid = fork())) {
        signal(SIGUSR1, usr2);
        if (!fork()) {
            FILE *file = fopen(argv[1], "r");
            if (file == NULL){
                printf("NOFILE\n");
                exit(0);
            }
            int elem;
            while (fscanf(file, "%d", &elem) == 1) {
                if (elem == 1) {
                    kill(ppid, SIGUSR1);
                } else if (elem == 2) {
                    kill(pid, SIGUSR1);
                }
            }
            fclose(file);
            exit(0);
        }
        wait(NULL);
        exit(0);
    }
    wait(NULL);
    return 0;
}

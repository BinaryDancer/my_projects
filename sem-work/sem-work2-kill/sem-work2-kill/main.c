//
//  main.c
//  sem-work2-kill
//
//  Created by Мамаев Павел on 24/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
int max = 100;
int fd[2];
void func(void) {
    int a;
    read(fd[0], &a, sizeof(a));
    printf("%d\n", a);
    ++a;
    write(fd[1], &a, sizeof(a));
    if (a >= max) {
        kill(0, SIGKILL);
    }
}
void func1(int sig) {
    signal(SIGUSR1, func1);
    func();
    kill(0, SIGUSR2);
}
void func2(int sig) {
    signal(SIGUSR2, func2);
    func();
    kill(0, SIGUSR1);
}

int main(int argc, const char * argv[]) {
    pipe(fd);
    int a = 0;
    if (!fork()) {
        signal(SIGUSR2, func2);
        printf("+\n");
        while(1){
        }
        printf("%d", a);
        exit(0);
    }
    if (!fork()) {
        printf("!!!\n");
        signal(SIGUSR1, func1);
        write(fd[1], &a, sizeof(a));
        kill(0, SIGUSR2);
        printf("#\n");
        while(1){
        }
        printf("%d", a);
        exit(0);
    }
    return 0;
}

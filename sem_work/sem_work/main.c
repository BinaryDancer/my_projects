//
//  main.c
//  sem_work
//
//  Created by Мамаев Павел on 17/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, const char * argv[]) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        if (!fork()) {
            execlp(argv[1], argv[1], NULL);
            exit(1);
        }
        int st;
        wait(&st);
        if (WIFEXITED(st) && WEXITSTATUS(st) == 0) {
            execlp(argv[2], argv[2], NULL);
        }
        exit(1);
    }
    if (!fork()){
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        int file;
        file = open(argv[4], O_WRONLY | O_APPEND);
        dup2(file, 1);
        close(file);
        execlp(argv[3], argv[3], NULL);
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}

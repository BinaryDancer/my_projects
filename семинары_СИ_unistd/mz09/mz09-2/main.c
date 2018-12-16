#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int mysys(const char *str){
    enum { MAX_RET = 128 };
    pid_t id = fork();
    if (id == -1) {
        return -1;
    } else if (!id) {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(MAX_RET - 1);
    }
    int stat;
    waitpid(id, &stat, 0);
    if (WIFEXITED(stat)) {
        return WEXITSTATUS(stat);
    }
    if (WIFSIGNALED(stat)) {
        return MAX_RET + WTERMSIG(stat);
    }
    abort();
}
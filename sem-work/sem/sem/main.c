#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
enum
{
    NUMBER_OF_PROC = 3,
    SIZE_BUF = 8
};
int getelem(void) {
    char s[SIZE_BUF];
    read(STDIN_FILENO, s, sizeof(s));
    int elem;
    sscanf(s, "%d", &elem);
    return elem;
}

int main(void) {
    for (int i = 0; i < NUMBER_OF_PROC; ++i) {
        if (!fork()) {
            int elem = getelem();
            printf("%d %d\n", i + 1, elem * elem);
            exit(0);
        }
    }
    for (int i = 0; i < NUMBER_OF_PROC; ++i){
        wait(NULL);
    }
    return 0;
}

#if 1
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(void) {
    printf("my %d\n", getpid());
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        if (i < n) {
            printf("%d %d ", getpid(), i);
            fflush(stdout);
            pid_t id = fork();
            if (id > 0) {
                wait(NULL);
                exit(0);
            }
        } else {
            printf("%d %d\n", getpid(), i);
            exit(0);
        }
    }
    return 0;
}
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
int main(void)
{
    printf("tan %d\n", getpid());
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        pid_t pid = 0;
        if (i < n - 1) {
            pid = fork();
        }
        if (pid == -1) {
            exit(1);
        } else if (pid != 0){
            printf("pid = %d %d ", getpid(), i + 1);
            fflush(stdout);
            wait(NULL);
            exit(0);
        } else if (pid == 0 && i == n - 1) {
            printf("%d %d\n", getpid(), i + 1);
        }
    }
    return 0;
}

#endif

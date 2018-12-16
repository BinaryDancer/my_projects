#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <limits.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main(int argc, char **argv) {
    key_t key;
    sscanf(argv[1], "%d", &key);
    int n;
    sscanf(argv[2], "%d", &n);
    long long val1;
    sscanf(argv[3], "%lld", &val1);
    long long val2;
    sscanf(argv[4], "%lld", &val2);
    long long maxval;
    sscanf(argv[5], "%lld", &val1);
    
    
    int msg_id = msgget(key, IPC_CREAT | 0666);
    int *pid = malloc(n * sizeof(*pid));
    struct mes {
        long type;
        int el;
    };
    struct mes m;
    m.type = 1;
    m.el = val1;
    msgsnd(msg_id, &m, )
    for (int i = 0; i < n; ++i) {
        pid[i] = fork();
        if (pid[i] == 0) {
            int nporc = i;

            exit(0);
        }
        if (pid[i] == -1) {
            for (int j = 0; j < i; ++j) {
                kill(pid[j], SIGKILL);
            }
            break;
        }
    }
    while (wait(NULL) > 0)
    {}
    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}
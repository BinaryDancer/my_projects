#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    if (argc != 4) {
        return 1;
    }
    int n;
    sscanf(argv[1], "%d", &n);
    key_t key;
    sscanf(argv[2], "%d", &key);
    int maxval;
    sscanf(argv[3], "%d", &maxval);
    
    int sem_id = semget(key, n, IPC_CREAT | 0666);
    int *val = mmap (NULL, sizeof(*val), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    int *nsem = mmap (NULL, sizeof(*nsem), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    short *opp = malloc(n * sizeof(*opp));
    *val = 0;
    *nsem = 0;
    opp[0] = 1;
    for (int i = 1; i < n; ++i) {
        opp[i] = 0;
    }
    semctl(sem_id, n, SETALL, opp);
    free(opp);
    
    for (int i = 0; i < n; ++i) {
        if (!fork()) {
            int proc = i;
            struct sembuf op;
            op.sem_flg = 0;
            op.sem_op = -1;
            op.sem_num = proc;
            struct sembuf op1;
            op1.sem_flg = 0;
            op1.sem_op = 1;
            op1.sem_num = proc;

            while (semop(sem_id, &op, 1) != -1) {
                printf("%d %d %d\n", proc + 1, *val, *nsem);
                fflush(stdout);
                *nsem = proc + 1;
                *val = *val + 1;
                if (*val > maxval) {
                    break;
                } else {
                    long long v = *val;
                    op1.sem_num = ((v * v) % n * (v * v) % n) % n;
                    semop(sem_id, &op1, 1);
                }
            }
            exit(0);
        }
    }
    wait(NULL);
    munmap(val, sizeof(*val));
    munmap(nsem, sizeof(*nsem));
    semctl(sem_id, 0, IPC_RMID, NULL);
    for (int i = 0; i < n-1; ++i) {
        wait(NULL);
    }
    return 0;
}
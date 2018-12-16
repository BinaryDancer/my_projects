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
    enum
    {   
        VALUE = 10,
        ADDN = 5
    };
    int count;
    sscanf(argv[1], "%d", &count);
    key_t key;
    sscanf(argv[2], "%d", &key);
    int n;
    sscanf(argv[3], "%d", &n);
    int iter_cout;
    sscanf(argv[4], "%d", &iter_cout);
    int sem_id = semget(key, 1, IPC_CREAT | 0666);
    int *val = mmap (NULL, sizeof(*val) * count, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    for (int i = 0; i < count; ++i) {
        scanf("%d", &val[i]);
    }
    semctl(sem_id, 0, SETVAL, 1);

    for (int i = 0; i < n; ++i) {
        if (!fork()) {
            struct sembuf op;
            op.sem_flg = 0;
            op.sem_op = -1;
            op.sem_num = 0;
            struct sembuf op1;
            op1.sem_flg = 0;
            op1.sem_op = 1;
            op1.sem_num = 0;
            int st;
            sscanf(argv[i + 1 + ADDN], "%d", &st);
            srand(st);
            for (int j = 0; j < iter_cout; ++j) {
                int ind1 = rand() / RAND_MAX * count;
                int ind2 = rand() / RAND_MAX * count;
                int v = rand() / RAND_MAX * VALUE;
                semop(sem_id, &op, 1);
                operation(val, ind1, ind2, v);
                semop(sem_id, &op1, 1);
            }
            exit(0);
        }
    }
    for (int i = 0; i < n; ++i) {
        wait(NULL);
    }
    for (int i = 0; i < count; ++i) {
        printf("%d ", val[i]);
    }
    printf("\n");
    fflush(stdout);
    munmap(val, sizeof(*val));
    semctl(sem_id, 0, IPC_RMID, NULL);
    
    return 0;
}
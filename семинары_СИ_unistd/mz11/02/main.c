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
enum
{
    MULT = '*',
    SUM = '+'
};
int oper = SUM;
void sign(int sig){
    if (sig == SIGINT) {
        oper = SUM;
    } else {
        oper = MULT;
    }
}
int main(void){
    if (signal(SIGINT, sign) == SIG_ERR) {
        return 1;
    };
    if (signal(SIGQUIT, sign) == SIG_ERR) {
        return 1;
    }
    printf("%d\n", getpid());
    fflush(stdout);
    int32_t elem;
    int32_t res = 0;
    while (scanf("%"SCNd32, &elem) == 1) {
        if (oper == SUM) {
            res = (uint32_t) elem + res;
        } else {
            res = (uint32_t) elem * res;
        }
        printf("%"PRId32"\n", res);
        fflush(stdout);
    }
    return 0;
}
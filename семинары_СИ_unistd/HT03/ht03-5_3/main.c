#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
enum
{
    MAX_SIZE = 4,
    MAX_SPACE = 0x0020
};
int main(void) {
    size_t size_now = 4;
    char *now = calloc(size_now, sizeof(*now));
    if (now == NULL) {
        return 1;
    }
    size_t useful = 0, useful_max = 0;
    size_t len = 0, max_len = 0;
    char *max = NULL;
    size_t first = 0;
    int get_elem;
    while ((get_elem = getc_unlocked(stdin)) != EOF) {
        if (get_elem > MAX_SPACE) {
            now[first] = (char) get_elem;
            unsigned shift = 1 << (CHAR_BIT - 1);
            ++useful;
            if (now[first] & shift) {
                shift >>= 1;
                while (now[first] & shift) {
                    if (useful == size_now) {
                        size_now *= 2;
                        char *tmp = realloc(now, size_now * sizeof(*tmp));
                        if (tmp == NULL) {
                            free(now);
                            if (max) {
                                free(max);
                            }
                            return 1;
                        }
                        now = tmp;
                    }
                    if ((get_elem = getc_unlocked(stdin)) == EOF) {
                        return 1;
                    }
                    now[useful] = (char) get_elem;
                    ++useful;
                    shift >>= 1;
                }
            }
            ++len;
        } else {
            if (len > max_len) {
                free(max);
                useful_max = useful;
                max_len = len;
                max = now;
                size_now = 4;
                now = calloc(size_now, sizeof(*now));
                if (now == NULL) {
                    free(max);
                    return 1;
                }
            }
            useful = 0;
            len = 0;
        }
        if (useful + 1 >= size_now) {
            size_now *= 2;
            char *tmp = realloc(now, size_now * sizeof(*tmp));
            if (tmp == NULL) {
                free(now);
                free(max);
                return 1;
            }
            now = tmp;
        }
        first = useful;
    }
    if (len > max_len) {
        free(max);
        useful_max = useful;
        max_len = len;
        max = now;
        now = NULL;
    }
    printf("%llu\n", (unsigned long long) max_len);
    if (max_len > 0){
        for (int i = 0; i < useful_max; ++i) {
            putchar(max[i]);
        }
        putchar('\n');
    }
    free(now);
    free(max);
    return 0;
}
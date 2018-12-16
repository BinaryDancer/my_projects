#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
enum
{
    MAX_SIZE = 4,
    MAX_SPACE = 0x0020,
    BUF_SIZE = 1024,
    ADD_LINE = 0x000a
};
int main(void) {
    const char new_line = ADD_LINE;
    size_t size_now = 0;
    size_t len_now = 0;
    char *now = NULL;
    size_t useful_max = 0;
    size_t max_len = 0;
    char *max = NULL;
    size_t len_buf = 0;
    size_t useful_buf = 0;
    size_t start_in_buf = 0;
    char buf[BUF_SIZE + MAX_SIZE];
    while ((useful_buf = read(STDIN_FILENO, buf, sizeof(*buf) * BUF_SIZE)) > 0) {
        size_t i = 0;
        while (i < useful_buf) {
            unsigned template = 1 << (CHAR_BIT - 1);
            unsigned checker = (unsigned) buf[i];
            ++i;
            if (checker & template) {
                len_buf++;
                template >>= 1;
                while (i < useful_buf && (checker & template)) {
                    template >>= 1;
                    ++i;
                }
                if (i == useful_buf && (checker & template)) {
                    while (checker & template) {
                        if (read(STDIN_FILENO, &buf[i], sizeof(buf[i])) != sizeof(buf[i])){
                            return 1;
                        }
                        template >>= 1;
                        ++i;
                    }
                    size_t add_size = i - start_in_buf;
                    if (size_now == 0) {
                        now = calloc(add_size, sizeof(*now));
                        if (now == NULL) {
                            free(max);
                            return 1;
                        }
                    } else {
                        char *tmp = realloc(now, (add_size + size_now) * sizeof(*tmp));
                        if (tmp == NULL) {
                            free(now);
                            free(max);
                            return 1;
                        }
                        now = tmp;
                    }
                    memcpy(&now[size_now], &buf[start_in_buf], add_size * sizeof(*buf));
                    size_now += add_size;
                    len_now += len_buf;
                    useful_buf = read(STDIN_FILENO, buf, sizeof(*buf) * BUF_SIZE);
                    i = 0;
                    start_in_buf = 0;
                    len_buf = 0;
                }
            } else {
                if (checker <= MAX_SPACE) {
                    if (len_now + len_buf > max_len) {
                        size_t add_size = i - start_in_buf - 1;
                        if (add_size > 0) {
                            if (size_now == 0) {
                                now = calloc(add_size, sizeof(*now));
                                if (now == NULL) {
                                    free(max);
                                    return 1;
                                }
                            } else {
                                char *tmp = realloc(now, (add_size + size_now) * sizeof(*tmp));
                                if (tmp == NULL) {
                                    free(now);
                                    free(max);
                                    return 1;
                                }
                                now = tmp;
                            }
                            memcpy(&now[size_now], &buf[start_in_buf], add_size * sizeof(*buf));
                            size_now += add_size;
                            len_now += len_buf;
                        }
                        free(max);
                        max = now;
                        useful_max = size_now;
                        max_len = len_now;
                        now = NULL;
                    } else {
                        free(now);
                    }
                    len_now = 0;
                    size_now = 0;
                    start_in_buf = i;
                    len_buf = 0;
                } else {
                    ++len_buf;
                }
            }
        }
        size_t add_size = i - start_in_buf;
        if (size_now == 0) {
            now = calloc(add_size, sizeof(*now));
            if (now == NULL) {
                free(max);
                return 1;
            }
        } else {
            char *tmp = realloc(now, (add_size + size_now) * sizeof(*tmp));
            if (tmp == NULL) {
                free(now);
                free(max);
                return 1;
            }
            now = tmp;
        }
        memcpy(&now[size_now], &buf[start_in_buf], add_size * sizeof(*buf));
        size_now += add_size;
        len_now += len_buf;
        fflush(stdout);
        i = 0;
        start_in_buf = 0;
        len_buf = 0;
    }
    /////
    if (len_now > max_len) {
        free(max);
        max = now;
        useful_max = size_now;
        max_len = len_now;
        now = NULL;
    } else {
        free(now);
    }
    /////
    printf("%llu\n", (unsigned long long) max_len);
    fflush(stdout);
    if (max_len > 0) {
        size_t size_out = sizeof(*max) * useful_max;
        if (write(STDOUT_FILENO, max, size_out) != size_out) {
            return 1;
        }
    }
    if (write(STDOUT_FILENO, &new_line, sizeof(new_line)) != sizeof(new_line)) {
        return 1;
    }
    free(now);
    free(max);
    return 0;
}

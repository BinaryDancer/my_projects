#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

unsigned long long hash_function(unsigned long long);
ssize_t sequence(unsigned long long h, unsigned long long number, unsigned long long count, int fd) {
    ssize_t err = 0;
    if (count == 0) {
        return err;
    }
    if (number < count) {
        err = sequence(hash_function(h), number+1, count, fd);
    } else {
        return 0;
    }
    if (err == 1) {
        return err;
    }
    err = write(fd, &h, sizeof(h));
    if (err < sizeof(h)) {
        return 1;
    }
    return 0;
}
int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_CREAT | O_WRONLY, 0660);
    if (fd < 0) {
        return 1;
    }
    off_t err1 = lseek(fd, 0, SEEK_END);
    if (err1 < 0) {
        close (fd);
        return 1;
    }
    unsigned long long hh ,count;
    sscanf(argv[2], "%llxu", &hh);
    sscanf(argv[3], "%llu", &count);
    ssize_t err = sequence(hh, 0, count, fd);
    close(fd);
    return err;
}
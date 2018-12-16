#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int file = open(argv[1], O_RDWR);
    if (file < 0){
        return 1;
    }
    long long min_elem;
    off_t min_pos = 0, pos = sizeof(min_elem);
    ssize_t err;
    err = read(file, &min_elem, sizeof(min_elem));
    if (err <= 0){
        close(file);
        return 0;
    }
    long long temp;
    while (read(file, &temp, sizeof(temp)) > 0){
        if (temp < min_elem){
            min_elem = temp;
            min_pos = pos;
        }
        pos += sizeof(temp);
    }
    min_elem = -min_elem;
    lseek(file, min_pos, SEEK_SET);
    write(file, &min_elem, sizeof(min_elem));
    close(file);
    return 0;
}
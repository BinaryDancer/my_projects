#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <inttypes.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};
int read_tree(int file, int32_t index) {
    struct Node temp;
    if (lseek(file, index * sizeof(temp), SEEK_SET) == -1) {
        return -1;
    }
    if (read(file, &temp, sizeof(temp)) != sizeof(temp)){
        return -1;
    }
    if (temp.right_idx) {
        int check = read_tree(file, temp.right_idx);
        if (check == -1) {
            return check;
        }
    }
    printf("%"PRId32" ", temp.key);
    if (temp.left_idx) {
        int check = read_tree(file, temp.left_idx);
        if (check == -1) {
            return check;
        }
    }
    return 0;
}
int main(int argc, char **argv){
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    int check = read_tree(fd, 0);
    close(fd);
    if (check == -1) {
        return 1;
    }
    printf("\n");
    return 0;
}
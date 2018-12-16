#include <stdio.h>

int main(int argc, char *argv[]) {
    const char rights[] = { "rwxrwxrwx" };
    enum { ALL_BITS = sizeof(rights) - 1 };
    for (int i = 1; i < argc; ++i) {
        int temp_rights;
        sscanf(argv[i], "%o", &temp_rights);
        int bit_number = ALL_BITS;
        int check_bit = 1 << (bit_number - 1);
        while (check_bit) {
            if (check_bit & temp_rights) {
                putchar(rights[ALL_BITS - bit_number]);
            } else {
                putchar('-');
            }
            bit_number--;
            check_bit >>= 1;
        }
        putchar('\n');
    }
    return 0;
}
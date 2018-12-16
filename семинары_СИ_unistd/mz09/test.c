#include <stdio.h>
#include <limits.h>

enum
{
    ALL_ELEMENTS = 8
};

int main(void) {
    unsigned char is_ok = 1;
    while (is_ok) {
        unsigned char in[ALL_ELEMENTS];
        for (int i = 0; i < ALL_ELEMENTS; ++i) {
            if (scanf("%hhx", &in[i]) != 1) {
                is_ok = 0;
                break;
            }
        }
        if (is_ok != 0){
            unsigned char out[ALL_ELEMENTS] = {};
            for (int i = 0; i < ALL_ELEMENTS; ++i) {
                for (int j = 0; j < CHAR_BIT; ++j) {
                    out[j] |= (in[i] >> (CHAR_BIT - 1 - j) & 1) << i;
                }
            }
            for (int i = ALL_ELEMENTS - 1; i > -1; --i) {
                printf("%hhx ", out[i]);
            }
        }
    }
    printf("\n");
    return 0;
}
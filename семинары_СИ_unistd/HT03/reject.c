#include <stdio.h>
#include <limits.h>

enum
{
    ALL_ELEMENTS = 8
};

int main(void) {
    unsigned char is_ok = 1;
    while (is_ok){
        unsigned char in[ALL_ELEMENTS];
        for (int i = 0; i < ALL_ELEMENTS; ++i) {
            if (scanf("%hhx", &in[i]) != 1) {
                is_ok = 0;
                break;
            }
        }
        if (is_ok != 0){
            unsigned char out[ALL_ELEMENTS];
            for (int i = 0; i < ALL_ELEMENTS; ++i) {
                for (int j = 0; j < CHAR_BIT; ++j) {
                    unsigned char temp_bit = (in[j] >> i) & 1;
                    out[i] = (out[i] & ~(1 << j)) | (temp_bit << j);
                }
            }
            for (int i = 0; i < ALL_ELEMENTS; ++i) {
                printf("%hhx ", out[i]);
            }
        }
    }
    printf("\n");
    return 0;
}
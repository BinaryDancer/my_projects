#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
int main(void) {
    int w, n;
    scanf("%o%o", &n, &w);
    uint32_t max_elem = 1 << n;
    uint32_t max_sign_elem = 1 << (n - 1);
    for (uint32_t i = 0; i < max_elem; ++i){
        printf("|%*"PRIo32"|%*"PRIu32"|%*"PRId32"|\n", w, i, w, i, w, (i >= max_sign_elem) ? -i + max_sign_elem : i);
    }
    return 0;
}
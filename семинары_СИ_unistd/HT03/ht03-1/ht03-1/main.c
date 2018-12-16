//
//  main.c
//  ht03-1
//
//  Created by Мамаев Павел on 29/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    int count, low, high;
    unsigned seed;
    if (argc < 5) {
        return 1;
    }
    sscanf(argv[1], "%d", &count);
    sscanf(argv[2], "%d", &low);
    sscanf(argv[3], "%d", &high);
    sscanf(argv[4], "%u", &seed);
    srand(seed);
    for (int i = 0; i < count; ++i){
        int random = rand();
        double tmp = random / (RAND_MAX + 1.0);
        tmp = tmp * (high - low);
        int ans = (int) tmp + low;
        printf("%d\n", ans);
    }
    return 0;
}

//
//  main.c
//  ht03-2
//
//  Created by Мамаев Павел on 29/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int
main(void) {
    enum {
        PERCENT = 100
    };
    int probability[PERCENT];
    int n;
    scanf("%d", &n);
    int ready_percents = 0;
    for (int i = 0;  i < n; ++i) {
        int value;
        int chance;
        scanf("%d%d", &value, &chance);
        for (int j = 0; j < chance; ++j) {
            probability[ready_percents++] = value;
        }
    }
    int m;
    scanf("%d", &m);
    unsigned seed;
    scanf("%u", &seed);
    srand(seed);
    for (int i = 0; i < m; ++i) {
        double tmp = rand() / (RAND_MAX + 1.0);
        int ans = tmp * PERCENT;
        printf("%d\n", probability[ans]);
    }
    return 0;
}

//
//  main.c
//  ре03-3
//
//  Created by Мамаев Павел on 29/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
enum
{
    MULT = 1103515245,
    INC = 12345,
    MOD = (int) 1LL << 31
};
struct RandomGenerator;

typedef struct RandomOperations {
    int (*next)(struct RandomGenerator*);
    void (*destroy)(struct RandomGenerator*);
} RandomOperations;

typedef struct RandomGenerator {
    RandomOperations *ops;
    int value;
} RandomGenerator;

void destroyRG(RandomGenerator *elem) {
    free(elem);
}
int getnext(RandomGenerator *elem) {
    long long temp = (((long long) elem->value * MULT) + INC) % MOD;
    elem->value = (int) temp;
    return elem->value;
}

RandomOperations operations = {getnext, destroyRG};

RandomGenerator *random_create(int seed){
    RandomGenerator *tmp = calloc(1, sizeof(*tmp));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->value = seed;
    tmp->ops = &operations;
    return tmp;
}

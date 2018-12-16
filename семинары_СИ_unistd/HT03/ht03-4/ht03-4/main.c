//
//  main.c
//  ht03-4
//
//  Created by Мамаев Павел on 31/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//  2745

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
enum
{
    MULT = 1103515245,
    INC = 12345,
    MOD = 0x80000000,
    MODD = 0x7fffffff,
    NUMBER_OF_LETTERS = 62,
    NUMBERS = 10,
    BIG_LETTERS = 26,
    MAX_LEN = 32
};
int main(void) {
    char letters[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
        '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
        'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
        'v', 'w', 'x', 'y', 'z'};
    char template[MAX_LEN + 1] = {};
    int broken = 0;
    scanf("%32s", template);
    if (template[0] == '.') {
        printf("#\n");
        return 0;
    }
    int end;
    int indx = template[0];
    for (int i = 0; i < NUMBER_OF_LETTERS; ++i){
        if (letters[i] == indx) {
            indx = i;
            i = NUMBER_OF_LETTERS;
        }
    }
    int begin = (int) ceil((double)indx++ / NUMBER_OF_LETTERS * MOD);
    if (indx == 62) {
        end = MODD;
    } else {
        end = (int) ceil((double)indx / NUMBER_OF_LETTERS * MOD);
    }
    int cnt = 0;
    for (int i = begin; i < end; ++i) {
        begin = i;
        int j = 1;
        begin = ((begin * (long long) MULT) + INC) & (MODD);
        while (template[j]) {
            if (template[j] != '.'){
                char now = letters[(int)((double)begin / MOD * NUMBER_OF_LETTERS)];
                if (template[j] != now) {
                    break;
                }
            }
            begin = ((begin * (long long) MULT) + INC) & (MODD);
            ++j;
        }
        if (!template[j]) {
            ++cnt;
            if (cnt > 1) {
                break;
            }
            broken = i;
        }
    }
    if (cnt != 1) {
        printf("#\n");
    } else {
        int j = 0;
        while (template[j]) {
            char now = letters[(int)((double)broken / MOD * NUMBER_OF_LETTERS)];
            broken = ((broken * (long long) MULT) + INC) & (MODD);
            printf("%c", now);
            ++j;
        }
    }
    return 0;
}

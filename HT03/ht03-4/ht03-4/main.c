//
//  main.c
//  ht03-4
//
//  Created by Мамаев Павел on 31/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
enum
{
    MULT = 1103515245,
    INC = 12345,
    MOD = (int) 1LL << 31,
    NUMBER_OF_LETTERS = 62,
    NUMBERS = 10,
    BIG_LETTERS = 26,
    MAX_LEN = 32
};
long long MOD2 = (1LL << 31) - 1;
long long getnext(long long elem) {
    return ((elem * (long long)MULT) + INC) & (MOD2);
}

char getletter(long long value) {
    double tmp = value / (INT_MAX + 1.0);
    int shift = tmp * NUMBER_OF_LETTERS;
    if (shift < NUMBERS) {
        return shift + '0';
    }
    shift -= NUMBERS;
    if (shift < BIG_LETTERS) {
        return shift + 'A';
    }
    shift -= BIG_LETTERS;
    return shift + 'a';
}
int getbackletter(char letter, char add) {
    if (letter >= '0' && letter <= '9') {
        letter -= '0';
    } else if (letter >= 'A' && letter <= 'Z') {
        letter -= 'A';
        letter += NUMBERS;
    } else if (letter >= 'a' && letter <= 'z'){
        letter -= 'a';
        letter += NUMBERS + BIG_LETTERS;
    }
    if (letter == 61) {
        return MOD;
    }
    letter = (letter + add) % (NUMBER_OF_LETTERS);
    double tmp = letter / (NUMBER_OF_LETTERS * 1.0);
    tmp *= INT_MAX;
    return (int) tmp;
}
int main(int argc, const char * argv[]) {
    char template[MAX_LEN + 1] = {};
    char broken[MAX_LEN + 1] = {};
    char not_broken[MAX_LEN + 1] = {};
    char *try = broken;
    scanf("%32s", template);
    if (template[0] == '.') {
        printf("#\n");
        return 0;
    }
    int begin, end;
    begin = getbackletter(template[0], 0);
    end = getbackletter(template[0], 1);
    int cnt = 0;
    for (int i = begin; cnt < 2 && i < end; ++i) {
        begin = i;
        int j = 0;
        while (template[j] != '\0') {
            char now = getletter(begin);
            begin = (int) getnext(begin);
            if (template[j] != '.' && template[j] != now) {
                break;
            }
            try[j] = now;
            ++j;
        }
        if (template[j] == '\0') {
            cnt++;
            try = not_broken;
        }
    }
    if (cnt != 1) {
        printf("#\n");
    } else {
        printf("%s", broken);
    }
    return 0;
}

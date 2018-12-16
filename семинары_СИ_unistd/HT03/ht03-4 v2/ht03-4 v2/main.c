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
#include <math.h>
enum
{
    MULT = 1103515245,
    INC = 12345,
    MOD = 0xa0000000,
    MOD2 = 0x7fffffff,
    NUMBER_OF_LETTERS = 62,
    NUMBERS = 10,
    BIG_LETTERS = 26,
    MAX_LEN = 32
};
int getnext(int elem) {
    return (int) (((elem * (long long) MULT) + INC) & MOD2);
}

char getletter(int value, const char *letters) {
    double tmp = value / (MOD * 1.0);
    int shift = tmp * NUMBER_OF_LETTERS;
    return letters[shift];
}
int getbackletter(char letter, int add, char *letters) {
    for (int i = 0; i < NUMBER_OF_LETTERS; ++i){
        if (letters[i] == letter){
            letter = i;
            i = NUMBER_OF_LETTERS;
        }
    }
    letter += add;
    if (letter == NUMBER_OF_LETTERS) {
        return MOD2;
    }
    double tmp = letter / (NUMBER_OF_LETTERS * 1.0);
    tmp = ceil(tmp * MOD);
    return (int) tmp;
}
int getbackletter2(char letter, char *letters, int *backletters) {
    for (int i = 0; i < NUMBER_OF_LETTERS; ++i){
        if (letters[i] == letter){
            letter = i;
            i = NUMBER_OF_LETTERS;
        }
    }
    return backletters[letter];
}

int main(void) {
    char letters[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
        '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
        'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
        'v', 'w', 'x', 'y', 'z'};
    char template[MAX_LEN + 1] = {};
    char broken[MAX_LEN + 1] = {};
    char not_broken[MAX_LEN + 1] = {};
    char *try = broken;
    scanf("%32s", template);
    if (template[0] == '.') {
        printf("#\n");
        return 0;
    }
    int begin = getbackletter(template[0], 0, letters);
    int end = getbackletter(template[0], 1, letters);
    printf("%c\n", getletter(end, letters));
    int cnt = 0;
    for (int i = begin; cnt < 2 && i < end; ++i) {
        begin = i;
        int j = 0;
        while (template[j] != '\0') {
            char now = getletter(begin, letters);
            begin = getnext(begin);
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
    printf("%d", cnt);
    if (cnt != 1) {
        printf("#\n");
    } else {
        printf("%s", broken);
    }
    return 0;
}

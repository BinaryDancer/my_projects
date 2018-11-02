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
    MOD =  0x80000000,
    MOD2 = 0x7fffffff,
    NUMBER_OF_LETTERS = 62,
    NUMBERS = 10,
    BIG_LETTERS = 26,
    MAX_LEN = 32
};
int getnext(int elem) {
    return ((elem * (long long) MULT) + INC) & MOD2;
}

char getletter(int value, const char *letters) {
    double tmp = ((double) value) / MOD;
    int shift = tmp * NUMBER_OF_LETTERS;
    return letters[shift];
}
int getbackletter(char letter, char *letters) {
    for (int i = 0; i < NUMBER_OF_LETTERS; ++i){
        if (letters[i] == letter){
            letter = i;
            break;
        }
    }
    double tmp = letter / (NUMBER_OF_LETTERS * 1.0);
    tmp = ceil(tmp * MOD);
    return (int) tmp;
}
int main(int argc, const char * argv[]) {
    char letters[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
            '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
            'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
            'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
            'v', 'w', 'x', 'y', 'z' };
    FILE *f = fopen("backletters.txt", "w");
    fprintf(f, "int backletters[] = {");
    for (int i = 0; i < NUMBER_OF_LETTERS; ++i){
        fprintf(f, " %d,", getbackletter(letters[i], letters));
    }
    fclose(f);
    return 0;
}

//
//  main.cpp
//  BigInt
//
//  Created by Мамаев Павел on 02/11/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
using namespace std;
class BigInt {
    char *number;
    char sign;
    size_t length;
    size_t size;
    friend std::ostream& operator<<(std::ostream& out, const BigInt& val);
public:
    BigInt(int64_t elem = 0) {
        size = 20;
        number = (char*) malloc(size * sizeof(*number));
        sign = 1;
        if (elem < 0) {
            sign = -1;
            elem *= -1;
        }
        length = 0;
        if (elem == 0){
            length++;
        }
        while (elem) {
            number[length++] = elem % 10;
            elem /= 10;
        }
    }
    ~BigInt() {
        free(number);
    }
    BigInt operator+(const BigInt &B) {
        BigInt res;
        if (sign == B.sign) {
            res.length = std::max(length, B.length);
            if (res.length >= res.size) {
                res.size = length * 2;
                res.number = (char*) realloc(res.number, res.size * sizeof(*(res.number)));
                size_t pos = 0;
                char add = 0;
                while (pos < length && pos < B.length) {
                    res.number[pos] = number[pos] + B.number[pos] + add;
                    add = res.number[pos] / 10;
                    res.number[pos] -= add * 10;
                    pos++;
                }
                char *mas = number;
                if (length < B.length){
                    mas = B.number;
                }
                for (size_t i = pos; i < res.length; ++i) {
                    res.number[i] = mas[i] + add;
                    add = res.number[i] / 10;
                    res.number[i] -= add * 10;
                }
                if (add) {
                    res.number[res.length++] = add;
                }
            } else {
                
            }
        }
        return res;
    }
    void operator=(const BigInt &B){
        length = B.length;
        sign = B.sign;
        size = B.size;
        number = (char*)malloc(size * sizeof(char));
        for (size_t i = 0; i < length; ++i) {
            number[i] = B.number[i];
        }
    }
};
std::ostream& operator<<(std::ostream& out, const BigInt& val) {
    if (val.length) {
        out << val.number[val.length - 1] * val.sign;
    }
    for (size_t i = val.length - 1; i > 0; --i) {
        out << (int) val.number[i - 1];
    }
    return out;
}
int main(int argc, const char * argv[]) {
    BigInt A(100);
    BigInt B(200);
    cout << A << endl;
    cout << B << endl;
    BigInt C = A+B;
    cout << C << endl;
    return 0;
}

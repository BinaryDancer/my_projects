//
//  main.cpp
//  class-matrix
//
//  Created by Мамаев Павел on 25/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <iostream>

#include "Matrix.h"
int main() {
    size_t r, c;
    std::cin >> r >> c;
    Matrix m(r, c);
    int count = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            m[i][j] = count++;
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

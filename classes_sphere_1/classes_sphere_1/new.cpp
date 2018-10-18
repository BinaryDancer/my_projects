//
//  new.cpp
//  classes_sphere_1
//
//  Created by Мамаев Павел on 18/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
struct A
{
    double x;
};

struct B
: public A
{
    double y;
};

struct C
: public B
{
    double z;
};

class Shape
{
    int x;
    int y;
};

class Circle : public Shape
{
    int radius;
};
int main(int argc, const char * argv[]) {
    
    std::cout << sizeof(A) << std::endl; // 8
    std::cout << sizeof(B) << std::endl; // 16
    std::cout << sizeof(C) << std::endl; // 24
    
    std::cout << offsetof(C, x) << std::endl; // 0
    std::cout << offsetof(C, y) << std::endl; // 8
    std::cout << offsetof(C, z) << std::endl; // 16
    /*
    C* c = new C();
    c->x; // Ок
    c->y; // Ок
    c->z; // Ок
    
    B* b = (B*) c;
    b->x; // Ок
    b->y; // Ок
    b->z; // Ошибка компиляции
    
    A* a = (A*) c;
    a->x; // Ок
    a->y; // Ошибка компиляции
    a->z; // Ошибка компиляции
    */
    
    return 0;
}

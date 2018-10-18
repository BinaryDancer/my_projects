//
//  main.cpp
//  classes_sphere_1
//
//  Created by Мамаев Павел on 18/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
/*
void User_setAge([User* const this], Year value) // можем менять User но не можем менять *
{
    [this->]age = value;
}
 */
class User
{
    using Year = uint32_t;
    Year age;
public:
    void setAge(Year value)
    {
        age = value;
    }
    
    bool canBuyAlcohol() const // значит не меняются поля класса и внутри тоже константные методы
    {
        return age >= 21;
    }
};
class Log
{
public:
    void write(const std::string& text);
};

class UserDb
{
    mutable Log log;
public:
    const User& getReadOnlyUser(
                                const std::string& name) const
    {
        log.write("...");
        return db.find(name);
    }
};
int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    return 0;
}

//
//  main.cpp
//  class_struct
//
//  Created by Мамаев Павел on 13/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

struct info {
    string name;
    string sec_name;
    int years;
    info(string f = "", string s = "", int y = 0) {
        name = f;
        sec_name = s;
        years = y;
    }
};
class list {
private:
    info data;
    list *next;
public:
    list(info d, list *n = NULL) {
        data = d;
        next = n;
    }
    list* insert(list *temp) {
        temp->next = this;
        return temp;
    }
    list* erase() {
        if (this != NULL) {
            list *new_head = this->next;
            delete this;
            return new_head;
        }
        return this;
    }
    ~list(){
        
    }
};

int main(int argc, const char * argv[]) {
    list *a = new list;
    a(info("st", "st", 0), NULL);
    string name, sec_name;
    int y;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        list *tmp = new list;
        a->next = tmp;
    }
    cout << "Hello, World!\n";
    return 0;
}

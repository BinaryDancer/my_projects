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
    string get_name() {
        return name;
    }
    string get_sname() {
        return sec_name;
    }
    void put_name(string &nname) {
        name = nname;
    }
    
};
class list {
public:
    list (info d = info(), list *n = NULL) {
        data = d;
        next = n;
    }
    list* insert(list *temp) {
        temp->next = this;
        return temp;
    }
    string get_name() {
        return data.get_name();
    }
    void put_names(string &s) {
        data.put_name(s);
    }
    list* get_tonext() {
        return next;
    }
    ~list() {
    }
private:
    info data;
    list *next;
};

int main(int argc, const char *argv[]) {
    list *a = new list(info("st", "st", 0), NULL);
    string name, sec_name;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        list *tmp = new list();
        a = a->insert(tmp);
        string temp = "";
        for (int j = 0; j <= i; ++j){
            temp = temp + "*";
        }
        a->put_names(temp);
    }
    for (int i = 0; i < n; ++i) {
        cout << i << " " << a->get_name() << endl;
        list* ne = a->get_tonext();
        delete a;
        a = ne;
    }
    cout << a->get_name() << endl;
    delete a;
    return 0;
}

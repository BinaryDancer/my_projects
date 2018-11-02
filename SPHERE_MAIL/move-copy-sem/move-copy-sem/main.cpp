//
//  main.cpp
//  move-copy-sem
//
//  Created by Мамаев Павел on 02/11/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
class String
{
    size_t size_;
    char* data_;
public:
    ~String()
    {
        delete[] data_;
    }
    String(char *s = nullptr){
        if (s == nullptr){
            data_ = s;
            size_ = 0;
        } else {
            data_ = strdup(s);
            size_ = strlen(data_);
        }
    }
    // String b1;
    // String b2 = b1;
    String(const String& copied)
    : data_(new char[copied.size_])
    , size_(copied.size_)
    {
        std::copy(copied.data_, copied.data_ + size_, data_);
    }
    
    
    // String b1;
    // String b2;
    // b2 = b1;
    String& operator=(const String& copied)
    {
        if (this == &copied)
            return *this;
        char* ptr = new char[copied.size_];
        delete[] data_;
        data_ = ptr;
        size_ = copied.size_;
        std::copy(copied.data_, copied.data_ + size_, data_);
        return *this;
    }
};
int main(int argc, const char * argv[]) {
    String b1;
    b1 = b1;
    
    std::vector<String> words;
    const char *a = "abra";
    words.push_back(String());
    words.push_back(String(const_cast<char *>(a)));
    int to = 0;
    int from = 1;
    words[to] = words[from];
    return 0;
}

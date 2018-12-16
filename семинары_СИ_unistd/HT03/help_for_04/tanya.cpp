#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Array{
    int *m_;
    size_t size_;
public:
    Array(size_t s) : size_(s) {
        m_ = (int*) calloc(size_, sizeof(int));
    }
    int& operator[] (int i){
        return m_[i];
    }
    void operator += (int add){
        for (int i = 0; i < size_; ++i){
            m_[i] += add;
        }
    }
    int sum(){
        int ss = 0;
        for (int i = 0; i < size_; ++i){
            ss += m_[i];
        }
        return ss;
    }
    ~Array() {
        free(m_);
    }
};

int main() {
    int n_mas;
    cin >> n_mas;
    Array *mas = new Array(n_mas);
    for (int i = 0; i < n_mas; ++i) {
        cin >> (*mas)[i];
    }
    cout << mas->sum();
    delete mas;

    int n;
    cin >> n;
    Array m(n);
    for (int i = 0; i < n; ++i) {
        cin >> m[i];
    }
    m += 5;
    int sum = m.sum();
    cout << sum << endl;
    return 0;
}
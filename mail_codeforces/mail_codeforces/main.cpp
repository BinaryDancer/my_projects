//
//  main.cpp
//  mail_codeforces
//
//  Created by Мамаев Павел on 18/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <set>

int binpow(int a, int p, int mod){
    if (p == 0) {
        if (a == 0)
            return 0;
        return 1;
    }
    if (p % 2){
        return (a * binpow(a, p - 1, mod)) % mod;
    }
    int b = binpow(a, p / 2, mod);
    return (b * b) % mod;
}
using namespace std;
int main(int argc, const char * argv[]) {
    int n, m, c;
    cin >> n >> m >> c;
    int a[n];
    int b[m];
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    for (int j = 0; j < m; ++j){
        cin >> b[j];
    }
    int res = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            int tmp = (a[i] * b[j] * binpow(c, i*i*j*j*j, 490019)) % 490019;
            res = (res + tmp) % 490019;
        }
        
    }
    cout << res;
    return 0;
}

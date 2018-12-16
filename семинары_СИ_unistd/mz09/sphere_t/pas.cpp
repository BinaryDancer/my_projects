#include <iostream>
#include <vector>
#include <math.h>
#include <map>
using namespace std;

const int NMAX = 525000;

vector <int> a(NMAX);
vector <int> t(4 * NMAX);

void build (int v, int tl, int tr)
{
    if (tl == tr)
        t[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

void update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        t[v]   = val;
        return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        update(v * 2, tl, tm, pos, val);
    else
        update(v * 2 + 1, tm + 1, tr, pos, val);
    t[v] = t[v * 2] + t[v * 2 + 1];
}

int get(int v, int tl, int tr, int l, int r) {
    int ans, ans1, ans2;
    ans1   = ans2   = 0;
    if (tl == l && tr == r) {
        ans = t[v];
        return ans;
    }
    //
    int tm = (tl + tr) / 2;
    if (l <= tm)
        ans1 = get (v * 2, tl, tm, l, min(r, tm));
    if (r > tm)
        ans2 = get (v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    ans = ans1 + ans2;
    return ans;
};
int binpow(int a, int n){
    if (n == 0)
        return 1;
    if (n % 2)
        return binpow(a, n-1) * a;
    int b = binpow(a, n/2);
    return b * b;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int step = int(log(n) / log(2)) + 1;
    int kol = binpow(2, step);
    build (1, 0, kol-1);
    for (int i = 0; i < m; i++) {
        int mov, ff, ss;
        scanf("%d%d%d", &mov, &ff, &ss);
        if (mov == 2) {
            update(1, 0, kol-1, ff, ss);
            a[ff] = ss;
        } else {
            int ans = get(1, 0, kol-1, ff, ss);
            printf("%d\n", ans);
        }
    }
    return 0;
}

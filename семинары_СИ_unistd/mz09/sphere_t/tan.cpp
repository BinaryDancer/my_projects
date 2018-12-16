#include <iostream>
#include <stdio.h>
#include <stdlib.h>
enum
{
    C = 524288
};
long long tree_data[C << 1];
/*void create()
{
    for (int i = 0; i < c * 2; ++i) {
        tree_data[i] = 0;
    }
}*/
void propagate(int ind, long long val)
{
    ind += C;
    tree_data[ind] = val;
    for (ind >>= 1; ind > 0; ind >>= 1) {
        tree_data[ind] = tree_data[ind << 1] + tree_data[(ind << 1) + 1];
    }
}
long long sum_of_subarray(int ind, int l, int r, int a, int b)
{
    if (b < l || a > r) {
        return  0;
    }
    if (a <= l && b >= r) {
        return tree_data[ind];
    }
    return sum_of_subarray(ind << 1, l, (l + r) >> 1, a, b) + sum_of_subarray((ind << 1) + 1, ((l + r) >> 1) + 1, r, a, b);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    //create;
    long long a;
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a);
        tree_data[i + C] = a;
    }
    for (int i = C - 1; i >= 0; --i) {
        tree_data[i] = tree_data[i << 1] + tree_data[(i << 1) + 1];
    }
    for (int i = 0; i < m; ++i) {
        int req; // request
        scanf("%d", &req);
        long long arg1, arg2;
        scanf("%lld%lld", &arg1, &arg2);
        if (req == 2) {
            propagate(arg1, arg2);
        } else if (req == 1) {
            printf("%lld\n", sum_of_subarray(1, 0, C - 1, arg1, arg2));
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
int mod;

/*
添加任意模数多项式使用
*/

i64 power(i64 base, i64 n) {
    base %= mod;
    i64 res = 1;
    while (n) {
        if (n & 1)
            (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}

void PolyInv(int deg, vector<Int>& f, vector<Int>& g) {
    if (deg == 1) {
        g[0] = power(f[0].get(), mod - 2);
        return;
    }
    PolyInv((deg + 1) >> 1, f, g);
    int lim = 1;
    while (lim <= (deg << 1))
        lim <<= 1;
    vector<Int> c(lim), d(lim);
    for (int i = 0; i < deg; i++)
        c[i] = f[i].get(), d[i] = g[i].get();
    init(lim);
    ntt(c, 1);
    ntt(d, 1);
    for (int i = 0; i < lim; ++i)
        c[i] = c[i] * d[i];
    ntt(c, -1);
    for (int i = 0; i < lim; ++i)
        c[i] = mod - c[i].get();
    ntt(c, 1);
    for (int i = 0; i < lim; ++i)
        c[i] = c[i] * d[i];
    ntt(c, -1);
    for (int i = (deg + 1) >> 1; i < deg; ++i)
        g[i] = c[i].get();
}

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct BIT2D {
    vector<vector<i64>> t1, t2, t3, t4;
    int n, m;
    BIT2D(int n_, int m_)
        : n(n_), m(m_) {
        t1 = vector<vector<i64>>(n + 1, vector<i64>(m + 1));
        t2 = t3 = t4 = t1;
    }
    void add(i64 x, i64 y, i64 z) {
        for (int X = x; X <= n; X += X & -X)
            for (int Y = y; Y <= m; Y += Y & -Y) {
                t1[X][Y] += z;
                t2[X][Y] += z * x;
                t3[X][Y] += z * y;
                t4[X][Y] += z * x * y;
            }
    }
    void range_add(i64 xa, i64 ya, i64 xb, i64 yb, i64 z) {
        add(xa, ya, z);
        add(xa, yb + 1, -z);
        add(xb + 1, ya, -z);
        add(xb + 1, yb + 1, z);
    }
    i64 ask(i64 x, i64 y) {
        i64 res = 0;
        for (int i = x; i; i -= i & -i)
            for (int j = y; j; j -= j & -j)
                res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] - (x + 1) * t3[i][j] + t4[i][j];
        return res;
    }
    i64 range_ask(i64 xa, i64 ya, i64 xb, i64 yb) {
        return ask(xb, yb) - ask(xb, ya - 1) - ask(xa - 1, yb) + ask(xa - 1, ya - 1);
    }
};
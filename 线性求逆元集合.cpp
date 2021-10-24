#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct INV  //线性求任意n个逆元，前提是原来的数必须为非零数！不然整体求逆元为0。
{
    int P;
    vector<i64> a, s, sv, inv;
    int n;
    INV(vector<i64> a_, int P_)
        : a(a_), P(P_) {
        n = (int)a_.size() - 1;
        s = vector<i64>(n + 1), sv = inv = s;
        s[0] = 1;
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] * a[i] % P;
        }
        sv[n] = get_inv(s[n]);
        for (int i = n; i >= 1; --i)
            sv[i - 1] = sv[i] * a[i] % P;
        for (int i = 1; i <= n; ++i)
            inv[i] = sv[i] * s[i - 1] % P;
    }
    i64 ex_gcd(i64 a, i64 b, i64& x, i64& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        i64 d = ex_gcd(b, a % b, x, y);
        i64 temp = x;
        x = y;
        y = temp - a / b * y;
        return d;
    }
    i64 get_inv(i64 v) {
        i64 x, y;
        ex_gcd(v, P, x, y);
        return (v % P + P) % P;
    }
};  // namespace INV
